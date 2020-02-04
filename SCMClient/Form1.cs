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
    public partial class MainForm : Form
    {
        class ServiceNotifier : IServiceNotify
        {
            void IServiceNotify.StateChanged(int newState, int acceptControl)
            {
                Owner.Invoke(new Action<ServiceState, ServiceAcceptingControl>(
                    delegate (ServiceState state, ServiceAcceptingControl control)
                    {
                        Owner.BtnStart.Enabled = state == ServiceState.Stopped;
                        Owner.BtnStop.Enabled = state == ServiceState.Running;
                        Owner.BtnPause.Enabled = state == ServiceState.Running && (control & ServiceAcceptingControl.PauseContinue) == ServiceAcceptingControl.PauseContinue;
                        Owner.BtnContinue.Enabled = state == ServiceState.Paused && (control & ServiceAcceptingControl.PauseContinue) == ServiceAcceptingControl.PauseContinue;
                        Owner.LblCurrentState.Text = $"Current state: {state}";
                    }),
                    (ServiceState)newState, (ServiceAcceptingControl)acceptControl
                    );
            }

            public ServiceNotifier(MainForm owner)
            {
                Owner = owner;
            }
            public MainForm Owner { get; }
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

        public MainForm()
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

        private void UpdateServiceControls()
        {
            if (m_service == null)
            {
                BtnStart.Enabled = false;
                BtnStop.Enabled = false;
                BtnPause.Enabled = false;
                BtnContinue.Enabled = false;
            }
            else
            {
                m_service.GetCurrentState(out int st, out int ctrl);
                ServiceAcceptingControl acceptControl = (ServiceAcceptingControl)ctrl;
                ServiceState state = (ServiceState)st;
                BtnStart.Enabled = state == ServiceState.Stopped;
                BtnStop.Enabled = state == ServiceState.Running;
                BtnPause.Enabled = state == ServiceState.Running && (acceptControl & ServiceAcceptingControl.PauseContinue) == ServiceAcceptingControl.PauseContinue;
                BtnContinue.Enabled = state == ServiceState.Paused && (acceptControl & ServiceAcceptingControl.PauseContinue) == ServiceAcceptingControl.PauseContinue;
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
                LblCurrentState.Text = "Current state: none";
            }
            else
            {
                m_service.GetConfig(out int pt, out int ps, out string binPath, out string startName);
                m_service.GetCurrentState(out int iState, out int iCtrl);
                ServiceType servcType = (ServiceType)pt;
                ServiceStartType startType = (ServiceStartType)ps;
                ServiceState state = (ServiceState)iState;
                LblServiceType.Text = $"Service type: {servcType}";
                LblStartType.Text = $"Service start type: {startType}";
                LblBinaryPath.Text = $"Binary image path: {binPath}";
                LblStartName.Text = $"Service start name: {startName}";
                LblCurrentState.Text = $"Current state: {state}";
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
                ShowError($"Unable open service {item.ServiceName}.", e.Message);
            }
            finally
            {
                UpdateServiceInfo();
            }
        }

        private void ShowError(string operation, string message)
        {
            StringBuilder builder = new StringBuilder();
            builder.AppendLine(operation);
            builder.Append(message);
            MessageBox.Show(builder.ToString(), Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                ShowError($"Unable to connect SCM on computer {BoxCompName.Text}.", exc.Message);
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
            UpdateServiceInfo();
            UpdateServiceControls();
        }

        private void BtnStart_Click(object sender, EventArgs e)
        {
            try
            {
                m_service?.Start();
            }

            catch (Exception exc)
            {
                ShowError("Unable to start service.", exc.Message);
            }
            finally
            {
                UpdateServiceControls();
                ListServices.Focus();
            }
        }

        private void BtnStop_Click(object sender, EventArgs e)
        {
            try
            {
                m_service?.Stop();
            }
            catch (Exception exc)
            {
                ShowError("Unable to stop service.", exc.Message);
            }
            finally
            {
                UpdateServiceControls();
                ListServices.Focus();
            }
        }

        private void BtnPause_Click(object sender, EventArgs e)
        {
            try
            {
                m_service.Pause();
            }
            catch (Exception exc)
            {
                ShowError("Unable to pause service.", exc.Message);
            }
            finally
            {
                UpdateServiceControls();
                ListServices.Focus();
            }
        }

        private void BtnContinue_Click(object sender, EventArgs e)
        {
            try
            {
                m_service.Continue();
            }
            catch (Exception exc)
            {
                ShowError("Unable to continue service.", exc.Message);
            }
            finally
            {
                UpdateServiceControls();
                ListServices.Focus();
            }
        }
    }
}
