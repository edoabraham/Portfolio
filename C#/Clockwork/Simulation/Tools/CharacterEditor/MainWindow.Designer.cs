namespace CharacterEditor {
	partial class MainWindow {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.MenuFile = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuNew = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuOpen = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuSave = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuSaveAs = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuExit = new System.Windows.Forms.ToolStripMenuItem();
			this.PropertiesGrid = new System.Windows.Forms.PropertyGrid();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuFile});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(507, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// MenuFile
			// 
			this.MenuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuNew,
            this.MenuOpen,
            this.MenuSave,
            this.MenuSaveAs,
            this.MenuExit});
			this.MenuFile.Name = "MenuFile";
			this.MenuFile.Size = new System.Drawing.Size(37, 20);
			this.MenuFile.Text = "File";
			this.MenuFile.Click += new System.EventHandler(this.MenuFile_Click);
			// 
			// MenuNew
			// 
			this.MenuNew.Name = "MenuNew";
			this.MenuNew.Size = new System.Drawing.Size(152, 22);
			this.MenuNew.Text = "New";
			this.MenuNew.Click += new System.EventHandler(this.MenuNew_Click);
			// 
			// MenuOpen
			// 
			this.MenuOpen.Name = "MenuOpen";
			this.MenuOpen.Size = new System.Drawing.Size(152, 22);
			this.MenuOpen.Text = "Open...";
			this.MenuOpen.Click += new System.EventHandler(this.MenuOpen_Click);
			// 
			// MenuSave
			// 
			this.MenuSave.Name = "MenuSave";
			this.MenuSave.Size = new System.Drawing.Size(152, 22);
			this.MenuSave.Text = "Save";
			this.MenuSave.Click += new System.EventHandler(this.MenuSave_Click);
			// 
			// MenuSaveAs
			// 
			this.MenuSaveAs.Name = "MenuSaveAs";
			this.MenuSaveAs.Size = new System.Drawing.Size(152, 22);
			this.MenuSaveAs.Text = "Save As...";
			this.MenuSaveAs.Click += new System.EventHandler(this.MenuSaveAs_Click);
			// 
			// MenuExit
			// 
			this.MenuExit.Name = "MenuExit";
			this.MenuExit.Size = new System.Drawing.Size(152, 22);
			this.MenuExit.Text = "Exit";
			this.MenuExit.Click += new System.EventHandler(this.MenuExit_Click);
			// 
			// PropertiesGrid
			// 
			this.PropertiesGrid.Location = new System.Drawing.Point(0, 27);
			this.PropertiesGrid.Name = "PropertiesGrid";
			this.PropertiesGrid.PropertySort = System.Windows.Forms.PropertySort.NoSort;
			this.PropertiesGrid.Size = new System.Drawing.Size(507, 673);
			this.PropertiesGrid.TabIndex = 1;
			this.PropertiesGrid.ToolbarVisible = false;
			this.PropertiesGrid.PropertyValueChanged += new System.Windows.Forms.
				PropertyValueChangedEventHandler(PropertyGrid_PropertyValueChanged);
			// 
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(507, 698);
			this.Controls.Add(this.PropertiesGrid);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "MainWindow";
			this.Text = "Character Editor";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem MenuFile;
		private System.Windows.Forms.ToolStripMenuItem MenuNew;
		private System.Windows.Forms.ToolStripMenuItem MenuOpen;
		private System.Windows.Forms.ToolStripMenuItem MenuSave;
		private System.Windows.Forms.ToolStripMenuItem MenuSaveAs;
		private System.Windows.Forms.ToolStripMenuItem MenuExit;
		private System.Windows.Forms.PropertyGrid PropertiesGrid;
	}
}

