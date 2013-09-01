namespace GameServer {
	partial class EntitiesList {
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
			this.TabControl = new System.Windows.Forms.TabControl();
			this.PlayerTabPage = new System.Windows.Forms.TabPage();
			this.PlayerListView = new System.Windows.Forms.ListView();
			this.TypeHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.NameHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.ValueHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.PlayerListTree = new System.Windows.Forms.TreeView();
			this.NPCTabPage = new System.Windows.Forms.TabPage();
			this.NPCListView = new System.Windows.Forms.ListView();
			this.NPCListTree = new System.Windows.Forms.TreeView();
			this.SpellTabPage = new System.Windows.Forms.TabPage();
			this.SpellListView = new System.Windows.Forms.ListView();
			this.SpellListTree = new System.Windows.Forms.TreeView();
			this.MenuStrip = new System.Windows.Forms.MenuStrip();
			this.MenuFile = new System.Windows.Forms.ToolStripMenuItem();
			this.MenuSaveAs = new System.Windows.Forms.ToolStripMenuItem();
			this.TabControl.SuspendLayout();
			this.PlayerTabPage.SuspendLayout();
			this.NPCTabPage.SuspendLayout();
			this.SpellTabPage.SuspendLayout();
			this.MenuStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// TabControl
			// 
			this.TabControl.Controls.Add(this.PlayerTabPage);
			this.TabControl.Controls.Add(this.NPCTabPage);
			this.TabControl.Controls.Add(this.SpellTabPage);
			this.TabControl.Location = new System.Drawing.Point(12, 35);
			this.TabControl.Name = "TabControl";
			this.TabControl.SelectedIndex = 0;
			this.TabControl.Size = new System.Drawing.Size(528, 440);
			this.TabControl.TabIndex = 2;
			// 
			// PlayerTabPage
			// 
			this.PlayerTabPage.Controls.Add(this.PlayerListView);
			this.PlayerTabPage.Controls.Add(this.PlayerListTree);
			this.PlayerTabPage.Location = new System.Drawing.Point(4, 22);
			this.PlayerTabPage.Name = "PlayerTabPage";
			this.PlayerTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.PlayerTabPage.Size = new System.Drawing.Size(520, 414);
			this.PlayerTabPage.TabIndex = 0;
			this.PlayerTabPage.Text = "Players";
			this.PlayerTabPage.UseVisualStyleBackColor = true;
			// 
			// PlayerListView
			// 
			this.PlayerListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.TypeHeader,
            this.NameHeader,
            this.ValueHeader});
			this.PlayerListView.Cursor = System.Windows.Forms.Cursors.Arrow;
			this.PlayerListView.Location = new System.Drawing.Point(162, 0);
			this.PlayerListView.MultiSelect = false;
			this.PlayerListView.Name = "PlayerListView";
			this.PlayerListView.Size = new System.Drawing.Size(358, 414);
			this.PlayerListView.TabIndex = 1;
			this.PlayerListView.UseCompatibleStateImageBehavior = false;
			this.PlayerListView.View = System.Windows.Forms.View.Details;
			// 
			// TypeHeader
			// 
			this.TypeHeader.Text = "Type";
			this.TypeHeader.Width = 106;
			// 
			// NameHeader
			// 
			this.NameHeader.Text = "Name";
			this.NameHeader.Width = 127;
			// 
			// ValueHeader
			// 
			this.ValueHeader.Text = "Value";
			this.ValueHeader.Width = 121;
			// 
			// PlayerListTree
			// 
			this.PlayerListTree.Location = new System.Drawing.Point(0, 0);
			this.PlayerListTree.Name = "PlayerListTree";
			this.PlayerListTree.Size = new System.Drawing.Size(156, 414);
			this.PlayerListTree.TabIndex = 0;
			this.PlayerListTree.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.PlayerListTree_NodeMouseClick);
			// 
			// NPCTabPage
			// 
			this.NPCTabPage.Controls.Add(this.NPCListView);
			this.NPCTabPage.Controls.Add(this.NPCListTree);
			this.NPCTabPage.Location = new System.Drawing.Point(4, 22);
			this.NPCTabPage.Name = "NPCTabPage";
			this.NPCTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.NPCTabPage.Size = new System.Drawing.Size(520, 414);
			this.NPCTabPage.TabIndex = 0;
			this.NPCTabPage.Text = "NPC";
			this.NPCTabPage.UseVisualStyleBackColor = true;
			// 
			// NPCListView
			// 
			this.NPCListView.Location = new System.Drawing.Point(162, 0);
			this.NPCListView.Name = "NPCListView";
			this.NPCListView.Size = new System.Drawing.Size(358, 414);
			this.NPCListView.TabIndex = 1;
			this.NPCListView.UseCompatibleStateImageBehavior = false;
			// 
			// NPCListTree
			// 
			this.NPCListTree.Location = new System.Drawing.Point(0, 0);
			this.NPCListTree.Name = "NPCListTree";
			this.NPCListTree.Size = new System.Drawing.Size(156, 414);
			this.NPCListTree.TabIndex = 0;
			// 
			// SpellTabPage
			// 
			this.SpellTabPage.Controls.Add(this.SpellListView);
			this.SpellTabPage.Controls.Add(this.SpellListTree);
			this.SpellTabPage.Location = new System.Drawing.Point(4, 22);
			this.SpellTabPage.Name = "SpellTabPage";
			this.SpellTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.SpellTabPage.Size = new System.Drawing.Size(520, 414);
			this.SpellTabPage.TabIndex = 0;
			this.SpellTabPage.Text = "Spell";
			this.SpellTabPage.UseVisualStyleBackColor = true;
			// 
			// SpellListView
			// 
			this.SpellListView.Location = new System.Drawing.Point(162, 0);
			this.SpellListView.Name = "SpellListView";
			this.SpellListView.Size = new System.Drawing.Size(358, 414);
			this.SpellListView.TabIndex = 1;
			this.SpellListView.UseCompatibleStateImageBehavior = false;
			// 
			// SpellListTree
			// 
			this.SpellListTree.Location = new System.Drawing.Point(0, 0);
			this.SpellListTree.Name = "SpellListTree";
			this.SpellListTree.Size = new System.Drawing.Size(156, 414);
			this.SpellListTree.TabIndex = 0;
			// 
			// MenuStrip
			// 
			this.MenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuFile});
			this.MenuStrip.Location = new System.Drawing.Point(0, 0);
			this.MenuStrip.Name = "MenuStrip";
			this.MenuStrip.Size = new System.Drawing.Size(552, 24);
			this.MenuStrip.TabIndex = 3;
			this.MenuStrip.Text = "menuStrip1";
			// 
			// MenuFile
			// 
			this.MenuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuSaveAs});
			this.MenuFile.Name = "MenuFile";
			this.MenuFile.Size = new System.Drawing.Size(37, 20);
			this.MenuFile.Text = "File";
			// 
			// MenuSaveAs
			// 
			this.MenuSaveAs.Name = "MenuSaveAs";
			this.MenuSaveAs.Size = new System.Drawing.Size(121, 22);
			this.MenuSaveAs.Text = "Save As..";
			// 
			// EntitiesList
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(552, 516);
			this.Controls.Add(this.TabControl);
			this.Controls.Add(this.MenuStrip);
			this.MainMenuStrip = this.MenuStrip;
			this.Name = "EntitiesList";
			this.Text = "Entity List";
			this.Load += new System.EventHandler(this.EntitiesList_Load);
			this.TabControl.ResumeLayout(false);
			this.PlayerTabPage.ResumeLayout(false);
			this.NPCTabPage.ResumeLayout(false);
			this.SpellTabPage.ResumeLayout(false);
			this.MenuStrip.ResumeLayout(false);
			this.MenuStrip.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip MenuStrip;
		private System.Windows.Forms.ToolStripMenuItem MenuFile;
		private System.Windows.Forms.ToolStripMenuItem MenuSaveAs;
		private System.Windows.Forms.TabControl TabControl;
		private System.Windows.Forms.TabPage PlayerTabPage;
		private System.Windows.Forms.TabPage NPCTabPage;
		private System.Windows.Forms.TabPage SpellTabPage;
		
		private System.Windows.Forms.ListView PlayerListView;
		private System.Windows.Forms.TreeView PlayerListTree;
		private System.Windows.Forms.ListView NPCListView;
		private System.Windows.Forms.TreeView NPCListTree;
		private System.Windows.Forms.ListView SpellListView;
		private System.Windows.Forms.TreeView SpellListTree;
		private System.Windows.Forms.ColumnHeader TypeHeader;
		private System.Windows.Forms.ColumnHeader NameHeader;
		private System.Windows.Forms.ColumnHeader ValueHeader;

	}
}