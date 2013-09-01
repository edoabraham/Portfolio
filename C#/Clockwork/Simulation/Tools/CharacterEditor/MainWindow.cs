/// MainWindow.cs - MainWindow Form Class Implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Artemis;
using Artemis.Interface;
using GameServer;
using Utilities;
using System.IO;

/// Character Editor
namespace CharacterEditor {

	/// This form and application reads and
	/// writes XML files that store character data.
	public partial class MainWindow : Form {

		/// Default file dialog path
		private const string DefaultDirectory = "C:\\";

		/// File dialog file type filter
		private const string FileFilter = "XML Files (*.xml)|*.xml|All files (*.*)|*.*";

		/// Default file filter index
		private const int DefaultFileIndex = 1;

		/// Constructor
		public MainWindow() {
			InitializeComponent();

			this.Character_ = new Character();
			this.FileDirectory_ = "";
			this.FilePath_ = "";
			this.FileName_ = "";
			this.FileChanged_ = false;

			this.RefreshPropGrid();
		}

		/// Wrapper class for the character class
		/// so that it can be used in property grid.
		private class CharacterProperties {

			/// Constructor
			public CharacterProperties(Character character) {
				this.Character_ = character;
			}

			/// ID
			[CategoryAttribute("Character Data")]
			public ECharacter ID {
				get { return this.Character_.ID; }
				set { this.Character_.ID = value; }
			}

			/// Name
			[CategoryAttribute("Character Data")]
			public string Name {
				get { return this.Character_.Name; }
				set { this.Character_.Name = value; }
			}

			/// Character elemental type
			[CategoryAttribute("Character Data")]
			[TypeConverter(typeof(ExpandableObjectConverter))]
			public Elemental Elemental {
				get { return this.Character_.Elemental; }
				set { this.Character_.Elemental = value; }
			}

			/// Statistics data
			[CategoryAttribute("Character Data")]
			[TypeConverter(typeof(ExpandableObjectConverter))]
			public Statistics Statistics {
				get { return this.Character_.Statistics; }
				set { this.Character_.Statistics = value; }
			}

			/// Array of character spells
			[CategoryAttribute("Character Data")]
			public ESpell[] Spells {
				get { return this.Character_.SpellList; }
				set { this.Character_.SpellList = value; }
			}

			private Character Character_;
		}

		/// Used to refresh the properties grid with new information.
		private void RefreshPropGrid() {
			this.PropertiesGrid.SelectedObject = new CharacterProperties(this.Character_);
			this.PropertiesGrid.ExpandAllGridItems();
			this.PropertiesGrid.PropertySort = PropertySort.NoSort;
		}

		/// Instance of character data
		/// used for storing and writing.
		private Character Character_;

		/// Directory of the currently open file.
		private string FileDirectory_;
		private string FilePath_;
		private string FileName_;

		/// Sets the directory, path, and file name with an open file dialog.
		private void OpenFile() {

			try {
				// Create new instance of open file dialog.
				OpenFileDialog openFileDialog = new OpenFileDialog();
				openFileDialog.Filter = FileFilter;
				openFileDialog.FilterIndex = DefaultFileIndex;
				openFileDialog.RestoreDirectory = true;

				// Prompt user in open file dialog and wait for OK.
				if (openFileDialog.ShowDialog() == DialogResult.OK) {

					// Store the file path, file name, and file directory.
					this.FilePath_ = openFileDialog.FileName;
					this.FileDirectory_ = new FileInfo(this.FilePath_).Directory.Name;
					this.FileName_ = new FileInfo(this.FilePath_).Name;
				}
			} catch (Exception exception) {
				MessageBox.Show(exception.Message);
			}
		}

		/// Sets the directory, path, and file name with a save file dialog.
		private void SaveFile() {

			try {
				// Create new instance of save file dialog.
				SaveFileDialog saveFileDialog = new SaveFileDialog();
				saveFileDialog.Filter = FileFilter;
				saveFileDialog.FilterIndex = DefaultFileIndex;
				saveFileDialog.RestoreDirectory = true;

				// Store the file path, file name, and file directory.
				if (saveFileDialog.ShowDialog() == DialogResult.OK) {

					// Store the file path, file name, and file directory.
					this.FilePath_ = saveFileDialog.FileName;
					this.FileDirectory_ = new FileInfo(this.FilePath_).Directory.Name;
					this.FileName_ = new FileInfo(this.FilePath_).Name;
				}
			} catch (Exception exception) {
				MessageBox.Show(exception.Message);
			}
		}

		/// Detects changes to the property grid and records it.
		private bool FileChanged_;
		private void PropertyGrid_PropertyValueChanged(Object sender, 
			PropertyValueChangedEventArgs e) {

				this.FileChanged_ = true;
		}

		/// Handle what happens when File is clicked.
		private void MenuFile_Click(object sender, EventArgs e) {

			// If the directory isn't set, deactivate Save
			this.MenuSave.Enabled = (this.FilePath_ == "") ? false : true;
		}

		/// Clear and re-initialize character and clear forms.
		private void MenuNew_Click(object sender, EventArgs e) {

			if (this.FileChanged_) {
				DialogResult result = MessageBox.Show("Changes have been made to this file.\nWould you like to save?",
					"Save", MessageBoxButtons.YesNoCancel);
				switch (result) {
					case DialogResult.Yes: {
							// Test if file exists
							if (File.Exists(this.FilePath_)) {

								// Overwrite existing
								Serializer.ToXML(this.Character_, this.FilePath_);

							} else {

								// Run as if Save As...
								// Open file dialog to set user defined directory.
								this.SaveFile();

								// Write new file with the path.
								Serializer.ToXML(this.Character_, this.FilePath_);
							}
						}
						break;
					case DialogResult.No:
						break;
					case DialogResult.Cancel:
						return;
					default:
						return;
				}
			}

			// Clear character
			this.Character_ = new Character();
			this.RefreshPropGrid();

			// Reset file change flag
			this.FileChanged_ = false;

			// Reset the paths
			this.FilePath_ = "";
			this.FileDirectory_ = "";
			this.FileName_ = "";
		}

		/// Writes to an already opened file.
		private void MenuSave_Click(object sender, EventArgs e) {

			try {
				// Test if file exists
				if (File.Exists(this.FilePath_)) {

					// Overwrite existing
					Serializer.ToXML(this.Character_, this.FilePath_);

				} else {

					// Run as if Save As...
					// Open file dialog to set user defined directory.
					this.SaveFile();

					// Write new file with the path.
					Serializer.ToXML(this.Character_, this.FilePath_);
				}

				// Reset the file changed flag.
				this.FileChanged_ = false;

			} catch (Exception exception) {
				MessageBox.Show(exception.Message);
			}
		}

		/// Attempts to save a new copy of the character data.
		private void MenuSaveAs_Click(object sender, EventArgs e) {

			try {
				// Open file dialog to set user defined directory.
				this.SaveFile();

				// Write new file with the path.
				Serializer.ToXML(this.Character_, this.FilePath_);

				// Reset the file changed flag.
				this.FileChanged_ = false;

			} catch(Exception exception) {
				MessageBox.Show(exception.Message);
			}
		}

		/// Attempts to open a character data file.
		private void MenuOpen_Click(object sender, EventArgs e) {

			try {
				if (this.FileChanged_) {
					DialogResult result = MessageBox.Show("Changes have been made to this file.\nWould you like to save?",
						"Save", MessageBoxButtons.YesNoCancel);
					switch (result) {
						case DialogResult.Yes: {
								// Test if file exists
								if (File.Exists(this.FilePath_)) {

									// Overwrite existing
									Serializer.ToXML(this.Character_, this.FilePath_);

								} else {

									// Run as if Save As...
									// Open file dialog to set user defined directory.
									this.SaveFile();

									// Write new file with the path.
									Serializer.ToXML(this.Character_, this.FilePath_);
								}
							}
							break;
						case DialogResult.No:
							// Just continue on
							break;
						case DialogResult.Cancel:
							// Break out completely
							return;
						default:
							return;
					}
				}

				// Open file dialog to set the user defined path.
				this.OpenFile();

				if (this.FilePath_ != "") {
					// Attempt to read and parse the file.
					this.Character_ = Serializer.FromXML<Character>(this.FilePath_);

					// Assign a new character property since original character
					// reference was broken when it was replaced by a new copy.
					this.RefreshPropGrid();

					// Reset the file changed flag.
					this.FileChanged_ = false;
				}

			} catch (Exception exception) {
				MessageBox.Show(exception.Message);
			}
		}

		/// Catch the exit event and prompt user in case they haven't saved yet.
		protected override void OnFormClosing(FormClosingEventArgs e) {

			if (this.FileChanged_) {
				DialogResult result = MessageBox.Show("Changes have been made to this file.\nWould you like to save?",
					"Save", MessageBoxButtons.YesNoCancel);
				switch (result) {
					case DialogResult.Yes: {
							// Test if file exists
							if (File.Exists(this.FilePath_)) {

								// Overwrite existing
								Serializer.ToXML(this.Character_, this.FilePath_);

							} else {

								// Run as if Save As...
								// Open file dialog to set user defined directory.
								this.SaveFile();

								// Write new file with the path.
								Serializer.ToXML(this.Character_, this.FilePath_);
							}
						}
						e.Cancel = true;
						break;
					case DialogResult.No:
						e.Cancel = false;
						break;
					case DialogResult.Cancel:
						e.Cancel = true;
						return;
					default:
						e.Cancel = true;
						return;
				}
			}
		}

		/// Attempt to exit the program.
		private void MenuExit_Click(object sender, EventArgs e) {

			this.Close();
		}
	}
}
