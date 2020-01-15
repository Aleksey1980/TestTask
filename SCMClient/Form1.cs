using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using SCManagerLib;

namespace SCMClient
{
    public partial class Form1 : Form
    {
        class ServiceNotifier : IServiceNotify
        {
            void IServiceNotify.StateChanged(int newState)
            {
                Owner.Invoke(new Action(()=>Owner.UpdateServiceControls()));
            }

            public ServiceNotifier(Form1 owner)
            {
                Owner = owner;
            }
            public Form1 Owner { get; }
        }

        class ServiceItem
        {
            public ServiceItem(string name, string dispName)
            {
                ServiceName = name;
                DisplayName = dispName;
            }
            public string ServiceName {get; }
            public string DisplayName { get;  }
            public override string ToString() => $"{DisplayName} [{ServiceName}]";
        }

        private IServiceControlManager m_manager;
        private bool m_connected = false;
        private ServiceNotifier m_notifier;
        private IService m_service = null;

        public Form1()
        {
            InitializeComponent();
            m_notifier = new ServiceNotifier(this);
            m_manager = new CoServiceControlManager();
            ListServices.Items.Clear();
            UpdateConnectButtons();
            UpdateServiceInfo();
            UpdateServiceControls();
        }

        private void UpdateConnectButtons()
        {
            BtnConnect.Enabled = !m_connected;
            BtnDisconnect.Enabled = m_connected;
        }

        public void UpdateServiceControls()
        {
            if (m_service == null)
            {
                BtnStart.Enabled = false;
                BtnStop.Enabled = false;
            }
            else
            {
                m_service.GetCurrentState(out int st);
                ServiceState state = (ServiceState)st;
                BtnStart.Enabled = state == ServiceState.Stopped;
                BtnStop.Enabled = state == ServiceState.Running;
            }
        }

        private void UpdateServiceInfo()
        {
            if (null == m_service)
            {
                LblServiceType.Text = "Service type: none";
                LblStartType.Text = "Service start type: none";
                LblBinaryPath.Text = "Binary image path: none";
                LblStartName.Text = "Service start name: none";
            }
            else
            {
                m_service.GetConfig(out int pt, out int ps, out string binPath, out string startName);
                ServiceType servcType = (ServiceType)pt;
                ServiceStartType startType = (ServiceStartType)ps;
                LblServiceType.Text = $"Service type: {servcType}";
                LblStartType.Text = $"Service start type: {startType}";
                LblBinaryPath.Text = $"Binary image path: {binPath}";
                LblStartName.Text = $"Service start name: {startName}";
            }
        }

        private void OpenSelectedService(ServiceItem item)
        {
            try
            {
                if (null != m_service)
                {
                    m_service.SetNotifyObject(null);
                    Marshal.ReleaseComObject(m_service);
                    m_service = null;
                }
                if (null != item)
                {
                    m_manager.GetService(item.ServiceName, out m_service);
                    m_service.SetNotifyObject(m_notifier);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                UpdateServiceInfo();
            }
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                OpenSelectedService(null);
                ListServices.Items.Clear();
                if (sender == BtnConnect)
                {
                    m_manager.Connect(string.IsNullOrEmpty(BoxCompName.Text) ? null : BoxCompName.Text);
                    m_manager.GetServices(out IEnumService services);
                    while (true)
                    {
                        services.Next(out string name, out string display);
                        if (string.IsNullOrEmpty(name) || string.IsNullOrEmpty(display))
                            break;
                        ListServices.Items.Add(new ServiceItem(name, display));
                    }
                    if (ListServices.Items.Count > 0)
                        ListServices.SetSelected(0, true);
                    m_connected = true;
                }
                else
                {
                    m_manager.Disconnect();
                    m_connected = false;
                    UpdateServiceControls();
                }
                UpdateServiceInfo();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message, Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                UpdateConnectButtons();
                UpdateServiceInfo();
                UpdateServiceControls();
                ListServices.Focus();
            }
        }

        private void ListServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            ServiceItem item = (ServiceItem)ListServices.SelectedItem;
            OpenSelectedService(item);
            UpdateServiceControls();
            UpdateServiceControls();
        }

        private void BtnStart_Click(object sender, EventArgs e)
        {
            try
            {
                m_service?.Start();
            }
            finally
            {
                ListServices.Focus();
            }
        }

        private void BtnStop_Click(object sender, EventArgs e)
        {
            try
            {
                m_service?.Stop();
            }
            finally
            {
                ListServices.Focus();
            }
        }
    }
}
