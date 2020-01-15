namespace SCMClient
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.BtnConnect = new System.Windows.Forms.Button();
            this.ListServices = new System.Windows.Forms.ListBox();
            this.BtnDisconnect = new System.Windows.Forms.Button();
            this.BoxCompName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BtnStop = new System.Windows.Forms.Button();
            this.BtnStart = new System.Windows.Forms.Button();
            this.LblServiceType = new System.Windows.Forms.Label();
            this.LblStartType = new System.Windows.Forms.Label();
            this.LblBinaryPath = new System.Windows.Forms.Label();
            this.LblStartName = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // BtnConnect
            // 
            this.BtnConnect.Location = new System.Drawing.Point(622, 10);
            this.BtnConnect.Name = "BtnConnect";
            this.BtnConnect.Size = new System.Drawing.Size(75, 23);
            this.BtnConnect.TabIndex = 0;
            this.BtnConnect.Text = "Connect";
            this.BtnConnect.UseVisualStyleBackColor = true;
            this.BtnConnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // ListServices
            // 
            this.ListServices.FormattingEnabled = true;
            this.ListServices.Location = new System.Drawing.Point(12, 64);
            this.ListServices.Name = "ListServices";
            this.ListServices.Size = new System.Drawing.Size(766, 368);
            this.ListServices.TabIndex = 1;
            this.ListServices.SelectedIndexChanged += new System.EventHandler(this.ListServices_SelectedIndexChanged);
            // 
            // BtnDisconnect
            // 
            this.BtnDisconnect.Location = new System.Drawing.Point(703, 9);
            this.BtnDisconnect.Name = "BtnDisconnect";
            this.BtnDisconnect.Size = new System.Drawing.Size(75, 23);
            this.BtnDisconnect.TabIndex = 2;
            this.BtnDisconnect.Text = "Disconnect";
            this.BtnDisconnect.UseVisualStyleBackColor = true;
            this.BtnDisconnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // BoxCompName
            // 
            this.BoxCompName.Location = new System.Drawing.Point(80, 12);
            this.BoxCompName.Name = "BoxCompName";
            this.BoxCompName.Size = new System.Drawing.Size(536, 20);
            this.BoxCompName.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Computer:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Installed services:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.LblStartName);
            this.groupBox1.Controls.Add(this.LblBinaryPath);
            this.groupBox1.Controls.Add(this.LblStartType);
            this.groupBox1.Controls.Add(this.LblServiceType);
            this.groupBox1.Controls.Add(this.BtnStop);
            this.groupBox1.Controls.Add(this.BtnStart);
            this.groupBox1.Location = new System.Drawing.Point(12, 448);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(766, 159);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Selected service";
            // 
            // BtnStop
            // 
            this.BtnStop.Location = new System.Drawing.Point(668, 118);
            this.BtnStop.Name = "BtnStop";
            this.BtnStop.Size = new System.Drawing.Size(75, 23);
            this.BtnStop.TabIndex = 1;
            this.BtnStop.Text = "Stop";
            this.BtnStop.UseVisualStyleBackColor = true;
            this.BtnStop.Click += new System.EventHandler(this.BtnStop_Click);
            // 
            // BtnStart
            // 
            this.BtnStart.Location = new System.Drawing.Point(587, 118);
            this.BtnStart.Name = "BtnStart";
            this.BtnStart.Size = new System.Drawing.Size(75, 23);
            this.BtnStart.TabIndex = 0;
            this.BtnStart.Text = "Start";
            this.BtnStart.UseVisualStyleBackColor = true;
            this.BtnStart.Click += new System.EventHandler(this.BtnStart_Click);
            // 
            // LblServiceType
            // 
            this.LblServiceType.AutoSize = true;
            this.LblServiceType.Location = new System.Drawing.Point(25, 27);
            this.LblServiceType.Name = "LblServiceType";
            this.LblServiceType.Size = new System.Drawing.Size(35, 13);
            this.LblServiceType.TabIndex = 2;
            this.LblServiceType.Text = "label3";
            // 
            // LblStartType
            // 
            this.LblStartType.AutoSize = true;
            this.LblStartType.Location = new System.Drawing.Point(277, 27);
            this.LblStartType.Name = "LblStartType";
            this.LblStartType.Size = new System.Drawing.Size(35, 13);
            this.LblStartType.TabIndex = 3;
            this.LblStartType.Text = "label3";
            // 
            // LblBinaryPath
            // 
            this.LblBinaryPath.AutoSize = true;
            this.LblBinaryPath.Location = new System.Drawing.Point(25, 57);
            this.LblBinaryPath.Name = "LblBinaryPath";
            this.LblBinaryPath.Size = new System.Drawing.Size(35, 13);
            this.LblBinaryPath.TabIndex = 4;
            this.LblBinaryPath.Text = "label3";
            // 
            // LblStartName
            // 
            this.LblStartName.AutoSize = true;
            this.LblStartName.Location = new System.Drawing.Point(25, 86);
            this.LblStartName.Name = "LblStartName";
            this.LblStartName.Size = new System.Drawing.Size(35, 13);
            this.LblStartName.TabIndex = 5;
            this.LblStartName.Text = "label3";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(786, 631);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BoxCompName);
            this.Controls.Add(this.BtnDisconnect);
            this.Controls.Add(this.ListServices);
            this.Controls.Add(this.BtnConnect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BtnConnect;
        private System.Windows.Forms.ListBox ListServices;
        private System.Windows.Forms.Button BtnDisconnect;
        private System.Windows.Forms.TextBox BoxCompName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button BtnStop;
        private System.Windows.Forms.Button BtnStart;
        private System.Windows.Forms.Label LblServiceType;
        private System.Windows.Forms.Label LblStartType;
        private System.Windows.Forms.Label LblBinaryPath;
        private System.Windows.Forms.Label LblStartName;
    }
}

