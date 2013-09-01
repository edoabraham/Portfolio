// MainUI.cpp - Main UI Class Implementation.
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
#include "mainui.h"
#include <QFileDialog>
#include <QColorDialog>
#include "DataASCII.h"
#include "DataCDF.h"
#pragma endregion
#pragma region Constants
#pragma region Files
// File extension for net cdf files.
const char* CDFExtension = ".cdf";

// File extension for backed up net cdf files.
const string BackupExtension = ".cdf.bak";

// Name of the folder used to store backed up files.
const QString BackupFolder = "/Backup";
#pragma endregion
#pragma region Sample List
// Column index for the sample IDs in the table.
const int SampleIDColIndex = 0;

// Column index for the file names in the table.
const int SampleFileColIndex = SampleIDColIndex + 1;
#pragma endregion
#pragma region Status Bar
// Base color of the program's status bar.
// Color: Light blue; same as Visual Studio 2012.
const QColor StatusBarBaseColor = QColor(0, 122, 204);

// Text color for the program's status bar.
// Color: White.
const QColor StatusBarTextColor = QColor(255, 255, 255);
#pragma endregion
#pragma region Registry Items
// Registry key for the directory of the last opened file.
const QString FileOpenDirectory = "File Open Directory";

// Registry key for the plot selection boldface option.
const QString SelectionBoldface = "Selection Boldface";

// Registry key for the list of recently opened files.
const QString RecentFiles = "Recently Opened Files";
#pragma endregion
#pragma endregion
#pragma region Private Slots
#pragma region Data and Plots
// Opens file dialog, waits for the user to choose
// a file, loads it through a DataASCII, registers
// the reader in the list, and proceeds to draw graphs.
void MainUI::LoadNewData() {

	// Attempt to grab the previous file path from the registry.
	QString fileName, path;
	if(this->ProgramSettings_->contains(FileOpenDirectory))
		path = this->ProgramSettings_->value(FileOpenDirectory).toString();

	// Open a file dialog and prompt the user for a file directory.
	//auto fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"), "", tr("Signal Files (*.dat.asc)"));
	auto fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"), path, tr("Signal Files (*.cdf)"));

	// Iterate through the list of file names.
	for(int i = 0, j = fileNames.size(); i < j; i++) {

		// Set the new file path.
		if(!fileName.isNull())
			this->ProgramSettings_->setValue(FileOpenDirectory, QFileInfo(fileName).path());

		// Localize a file name.
		fileName = fileNames[i];
		fileName = fileName.replace('\\', "/");
		

		// Load the data of the file.
		this->LoadNewData(fileName);

		// Add the new loaded file to the recent files list.
		this->SetCurrentFile(fileName);
	}
}

// Loads the data for a single file.
void MainUI::LoadNewData(const QString& fileName) {

	// Check if there was a file path read.
	if(fileName != "") {

		// Create a new DataFile for reading the file.
		DataCDF* datFile = new DataCDF();
		Util::Print("New DataFile created. Attempting to parse file...");

		// Begin reading and parsing the file.
		datFile->Read(fileName.toStdString());
		Util::Print("Read file: " + fileName.toStdString());
		this->WriteStatusMsg("Opening " + fileName);

		// Check if the file was correctly read or not.
		if(!datFile->GetFileStored())
			throw "Failed to read the file.";

		// Check if an entry with the same ID already exists.
		if(this->DataFiles_.find(QString(datFile->GetFileName().c_str())) 
			== this->DataFiles_.end()) {

				// Add new data to the graph.
				auto plotData = this->UI_.SignalGraph->AddPlot(*datFile);
				this->UI_.SignalGraph->SetXLabel(datFile->GetXAxisTitle());
				this->UI_.SignalGraph->SetYLabel(datFile->GetYAxisTitle());
				this->UI_.SignalGraph->Refresh();
				Util::Print("Data was loaded into the graph.");

				// Store the new reader into the reader list.
				this->DataFiles_.insert(pair<QString, pair<DataFile*, PlotData*>>
					(QString(datFile->GetFileName().c_str()), pair<DataFile*, PlotData*>(datFile, plotData)));
				Util::Print("New DataFile was stored into the reader list.\n");

				// Add new entry the signal list dialog.
				int row = 0;
				this->SignalList_.TableWidget->insertRow(row = this->SignalList_.TableWidget->rowCount());

				// Set the sample ID. Make sure to check that there are columns.
				if(this->SignalList_.TableWidget->columnCount() > SampleIDColIndex) {

					// Create a new table cell.
					QTableWidgetItem* tableItem = new QTableWidgetItem(datFile->GetSampleID().c_str());

					// Change its flag so it's not editable.
					tableItem->setFlags(tableItem->flags() ^ Qt::ItemIsEditable);

					// Change the text color of the sample ID.
					tableItem->setTextColor(plotData->Color);

					// Add the new cell to the appropriate location on the table.
					this->SignalList_.TableWidget->setItem(row, SampleIDColIndex, tableItem);
				}

				// Set the file name. Make sure to check that there are enough columns.
				if(this->SignalList_.TableWidget->columnCount() > SampleFileColIndex) {

					// Create a new table cell.
					QTableWidgetItem* tableItem = new QTableWidgetItem(datFile->GetFileName().c_str());

					// Change its flag so it's not editable.
					tableItem->setFlags(tableItem->flags() ^ Qt::ItemIsEditable);

					// Add the new cell to the appropriate location on the table.
					this->SignalList_.TableWidget->setItem(row, SampleFileColIndex, tableItem);

					// Add the table item to the list of table elements.
					this->TableElements_.insert(pair<QString, QTableWidgetItem*>
						(QString(datFile->GetFileName().c_str()), tableItem));
				}

				// Resize the columns so that they take on the length of the longest item.
				this->SignalList_.TableWidget->resizeColumnsToContents();

				// Add new entry to the configure dialog.
				this->ConfigureUI_.SampleCBox->addItem(QString(datFile->GetFileName().c_str()));

				// Display that the signal data was added.
				this->WriteStatusMsg("Data successfully loaded.");
		} else {

			// Display that the signal already exists.
			Util::Print(datFile->GetFileName() + " already exists.\n");
			this->WriteStatusMsg("Error: Data already exists.");
		}
	}
}

// Removes a specific signal's data set and redraws graph.
void MainUI::RemoveData(QTableWidgetItem* item) {

	// Check the table's integrity.
	int numOfColumns = this->SignalList_.TableWidget->columnCount();
	if((SampleFileColIndex < numOfColumns) && (SampleIDColIndex < numOfColumns)) {

		// Localize the text of the list item view.
		QString key = item->text();
		Util::Print("Attempting to remove data for \"" + key.toStdString() + "\" from the program...");
		this->WriteStatusMsg("Attempting to remove data for " + key);

		// Search for the entry first.
		if(this->DataFiles_.find(key) != this->DataFiles_.end()) {
			Util::Print("Item \"" + key.toStdString() + "\" was found in the readers' list.");

			// Localize map entry.
			auto entry = this->DataFiles_[key];

			// Remove the reader from the graph.
			this->UI_.SignalGraph->RemovePlot(entry.second);
			delete entry.first;
			Util::Print("Item was successfully removed from the graph.");

			// Remove the entry from the signals list.
			this->DataFiles_.erase(key);
			Util::Print("Removed the item from the listings.\n");
			this->WriteStatusMsg("Data successfully removed.");
		}

		// Remove the key from the list item view.
		this->SignalList_.TableWidget->removeRow(item->row());

		// Remove the key from the configuration box.
		this->ConfigureUI_.SampleCBox->removeItem(this->
			ConfigureUI_.SampleCBox->findText(key));

		// Remove the entry from the list of table elements.
		this->TableElements_.erase(key);

		// Check if signal's list view is empty.
		if(this->SignalList_.TableWidget->rowCount() < 1) {

			// Disable the signal box buttons, Remove and Configure.
			this->DisableSignalButtons();
		}
	}
}
void MainUI::RemoveData() {

	// Localize list of selected indices.
	auto items = this->SignalList_.TableWidget->selectedItems();
	for(int i = 0, j = items.size(); i < j; i++) {

		// Check if the item is the correct column.
		if(items.at(i)->column() == SampleFileColIndex)
			this->RemoveData(items.at(i));
	}
}

// Saves all the data back to their original files. [CDF Only]
void MainUI::SaveData() {

	// Iterate through the map of stored data files.
	for(auto i = this->DataFiles_.begin(), 
		j = this->DataFiles_.end(); i != j; i++) {

			// Localize the data file.
			auto dataFile = i->second.first;

			// Check if it is in fact a CDF file.
			if(dataFile->GetType() == DataFile::CDF) {
				
				// Cast DataCDF to the data file.
				auto dataCDF = (DataCDF*)dataFile;

				// Localize the file name as a QString.
				QString fileName = QString(dataCDF->GetFileName().c_str());

				// Search for the last slash.
				int slashIndex = fileName.lastIndexOf('/');

				// If there's slash found, it is assumed that the file
				// path isn't valid to begin with and no save is made.
				if(slashIndex >= 0) {

					// Get the backup path of the file.
					QDir path(fileName.left(slashIndex) + BackupFolder);

					// Create the folder if it doesn't exist.
					if(!path.exists())
						path.mkpath(".");
				
					// Create the file name for a file backup.
					// Add backup folder, timestamp, and new extension to the file name.
					string backupName = ((fileName

						// Insert the backup folder name.
						.insert(slashIndex, BackupFolder))

						// Insert the date and time.
						.replace(CDFExtension, QDateTime::currentDateTime()
						.toString(" ddd MMM d, yyyy hh-mm-ss"))).toStdString() 
					
						// Added the backup extension.
						+ BackupExtension;

					// Back up the original file.
					dataCDF->FileBackup(backupName);
					Util::Print("File backup made to " + backupName + ".\n");

					// Grab the plot data for the changes.
					auto plotData = i->second.second;

					// Attempt to write the new data to the file.
					dataCDF->Write(plotData->X.toStdVector(), plotData->Y.toStdVector());
					Util::Print("Data for file " + dataCDF->GetFileName() + " was successfully saved.");
				} else {
					// Throw exception if file name is invalid.
					throw "Cannot save file; Invalid file name.";
				}
			}
	}
}
#pragma endregion
#pragma region Signal List UI
// Displays the signal list box.
void MainUI::ShowSignals() {
	this->SignalBox_->show();
}

// Enables signal list box buttons Remove 
// and Configure when a list item is selected.
void MainUI::EnableSignalButtons() {
	this->SignalList_.RemoveButton->setEnabled(true);
	this->SignalList_.ConfigureButton->setEnabled(true);
}

// Disables signal list box buttons Remove
// and Configure when a list item is deselected.
void MainUI::DisableSignalButtons() {
	this->SignalList_.RemoveButton->setEnabled(false);
	this->SignalList_.ConfigureButton->setEnabled(false);
}
#pragma endregion
#pragma region Configuration UI
// Displays the signal configuration window after
// loading the signal specific changes into the form.
void MainUI::ShowConfiguration() {

	// Displays the box.
	this->ConfigureBox_->show();

	// Change the currently selected in signal list to
	// that in the combo box in the configuration box.
	this->ConfigureUI_.SampleCBox->setCurrentIndex(this->SignalList_.TableWidget->currentRow());

	// Update the widgets in the configuration box.
	this->UpdateConfigDisplay(this->SignalList_.TableWidget->currentItem()->text());
}

// Updates the information displayed in the
// configuration form according to a specific key.
void MainUI::UpdateConfigDisplay(const QString& key) {

	// Look up the data with the matching key.
	if(this->DataFiles_.find(key) != this->DataFiles_.end()) {

		// Localize plot data.
		auto plotData = (this->DataFiles_[key]).second;

		// Change the current list boxes with the offset values.
		this->ConfigureUI_.XAxisBox->setText(QString().setNum(plotData->GetXOffset()));
		this->ConfigureUI_.YAxisBox->setText(QString().setNum(plotData->GetYOffset()));

		// Change the color of the line edit box for displaying color.
		QPalette palette = this->ConfigureUI_.ColorDisplay->palette();
		palette.setColor(QPalette::Base, plotData->Color);
		this->ConfigureUI_.ColorDisplay->setPalette(palette);
		Util::Print("Data in the config box updated for " + key.toStdString());
	}
}

// Updates a specific signal data with the
// values in the fields of the configuration box.
void MainUI::UpdateSignalConfig() {

	// Get the key of the currently selected signal.
	auto key = this->ConfigureUI_.SampleCBox->currentText();

	// Look up the data with the matching key.
	string keyStr = key.toStdString();
	if(this->DataFiles_.find(key) != this->DataFiles_.end()) {

		// Localize plot data.
		auto plotData = (this->DataFiles_[key]).second;

		// Set the color of the graph with the color in the config box.
		plotData->Color = this->ConfigureUI_.ColorDisplay->palette().base().color();

		// Check the integrity of the table.
		if(this->SignalList_.TableWidget->columnCount() > SampleIDColIndex) {

			// Search for the element with the same key.
			auto item = this->TableElements_.begin();
			if((item = this->TableElements_.find(key)) != this->TableElements_.end()) {

				// Change the sample ID's color.
				item->second->setTextColor(plotData->Color);
			}
		}

		// Change the current list boxes with the offset values.
		plotData->SetXOffset(this->ConfigureUI_.XAxisBox->text().toDouble());
		plotData->SetYOffset(this->ConfigureUI_.YAxisBox->text().toDouble());
		Util::Print("Graph and data was updated for " + key.toStdString());
		this->UI_.SignalGraph->Refresh();
	}
}

// Prompts user with a color dialog that
// will change the color display color.
void MainUI::ChangeSignalColor() {

	// Grab the color from the color dialog.
	QColor color = QColorDialog::getColor(Qt::black, this, "Curve Color",  QColorDialog::DontUseNativeDialog);
	if(color.isValid()) {

		// Change the signal plot's color.
		QPalette palette = this->ConfigureUI_.ColorDisplay->palette();
		palette.setColor(QPalette::Base, color);
		this->ConfigureUI_.ColorDisplay->setPalette(palette);
	}
}
#pragma endregion
#pragma region Preference UI
// Displays the user app preference window.
void MainUI::ShowPreferences() {

	// Activate and show the form.
	this->PreferenceBox_->show();

	// Get the registered settings for selection boldface, if they exist.
	bool selectionBoldface = false;
	if(this->ProgramSettings_->contains(SelectionBoldface))
		selectionBoldface = this->ProgramSettings_->value(SelectionBoldface, selectionBoldface).toBool();

	// Update the check box for boldface plot selection.
	this->PreferenceUI_.BoldfaceCheck->setChecked(selectionBoldface);
}

// Registers the checked state of bold selection
// and changes all of the plots to have the same state.
void MainUI::PrefSelectBoldChanged(int state) {

	// Check if the state is checked.
	bool isChecked = false;
	if(state == Qt::Checked) 
		isChecked = true;

	// Write the status to the registry.
	this->ProgramSettings_->setValue(SelectionBoldface, isChecked);

	// Change the graph to reflect the same state.
	this->UI_.SignalGraph->GetGraph()->SetBoldfacedSelect(isChecked);

	// Refresh the graph.
	this->UI_.SignalGraph->Refresh();
}
#pragma endregion
#pragma region Recent Files Action
// Loads the list of recently opened files from the registry.
void MainUI::LoadRecentFilesList() {

	// Add UI actions to the menu.
	for(int i = 0; i < MaxRecentList; i++) {
		this->RecentFilesActions_[i] = new QAction(this->UI_.menuRecent);
		this->RecentFilesActions_[i]->setVisible(false);
		this->UI_.menuRecent->addAction(this->RecentFilesActions_[i]);
		connect(this->RecentFilesActions_[i], SIGNAL(triggered()), 
			this, SLOT(OpenRecentFile()));
	}

	// Update the list of files in the recent list.
	this->UpdateRecentFilesList();
}

// Updates the list of items featured in the recently
// opened list and update the items stored in the registry.
void MainUI::UpdateRecentFilesList() {

	// Localize the list of recent file names.
	QStringList fileNames = this->ProgramSettings_->value(RecentFiles).toStringList();

	// Get the number of file names.
	int numFileNames = min(fileNames.size(), MaxRecentList);

	// Iterate through the list of file names and list them in the menu.
	for(int i = 0; i < numFileNames; i++) {
		QString text = fileNames[i];
		this->RecentFilesActions_[i]->setText(QString().setNum(i) + " " + text);
		this->RecentFilesActions_[i]->setData(text);
		this->RecentFilesActions_[i]->setVisible(true);
	}

	// Ensure the remaining actions are not visible.
	for(int j = numFileNames; j < MaxRecentList; j++)
		this->RecentFilesActions_[j]->setVisible(false);
}

// Adds a file name to the recently opened list.
void MainUI::SetCurrentFile(const QString& fileName) {

	// Localize the list of recent file names.
	QStringList fileNames = this->ProgramSettings_->value(RecentFiles).toStringList();

	// Remove any duplicates from the file name list.
	fileNames.removeAll(fileName);

	// Add the file name back to the top of the string list.
	fileNames.prepend(fileName);

	// Remove any file names that exceed the max number of entries.
	while(fileNames.size() > MaxRecentList)
		fileNames.removeLast();

	// Save the new file name list to the registry.
	this->ProgramSettings_->setValue(RecentFiles, fileNames);

	// Update the recent actions.
	this->UpdateRecentFilesList();
}

// Opens a file from the recently opened files list.
void MainUI::OpenRecentFile() {

	// Localize the action that called this slot.
	QAction* action = qobject_cast<QAction*>(sender());
	if(action)
		this->LoadNewData(action->data().toString());
}
#pragma endregion
#pragma endregion
#pragma region Helper
// Manages the connection of signals and slots.
void MainUI::ConnectWidgets() {
	connect(this->UI_.actionOpen, SIGNAL(triggered()), this, SLOT(LoadNewData()));
	connect(this->UI_.actionSave, SIGNAL(triggered()), this, SLOT(SaveData()));
	connect(this->UI_.SignalsAction, SIGNAL(triggered()), this, SLOT(ShowSignals()));
	connect(this->UI_.PreferencesAction, SIGNAL(triggered()), this, SLOT(ShowPreferences()));
	connect(this->SignalList_.AddButton, SIGNAL(clicked()), this, SLOT(LoadNewData()));
	connect(this->SignalList_.RemoveButton, SIGNAL(clicked()), this, SLOT(RemoveData()));
	connect(this->SignalList_.ConfigureButton, SIGNAL(clicked()), this, SLOT(ShowConfiguration()));
	connect(this->SignalList_.TableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(EnableSignalButtons()));
	connect(this->SignalList_.TableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(ShowConfiguration()));
	connect(this->ConfigureUI_.SampleCBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(UpdateConfigDisplay(QString)));
	connect(this->ConfigureUI_.OkayButton, SIGNAL(clicked()), this, SLOT(UpdateSignalConfig()));
	connect(this->ConfigureUI_.ColorButton, SIGNAL(clicked()), this, SLOT(ChangeSignalColor()));
	connect(this->PreferenceUI_.BoldfaceCheck, SIGNAL(stateChanged(int)), this, SLOT(PrefSelectBoldChanged(int)));
}

// Sets up the status bar for usage.
void MainUI::SetupStatusBar() {

	// Set the background/base color of the status bar.
	this->UI_.statusBar->setStyleSheet(
		"background: " + StatusBarBaseColor.name()
		
		// Set the text color of the status bar.
		+";\ncolor: " + StatusBarTextColor.name());

	// Initialize the status label.
	this->StatusMsg = new QLabel(this);

	// Assign the label to the status bar.
	this->UI_.statusBar->addPermanentWidget(this->StatusMsg, 1);

	// Set the alignment of the status label.
	this->StatusMsg->setAlignment(Qt::AlignLeft);

	// Write a "Ready" message to the status bar.
	this->WriteStatusMsg("Ready");
}

// Clears a status message and writes a new one.
void MainUI::WriteStatusMsg(const QString& message) {
	this->StatusMsg->setText(message);
	this->UI_.statusBar->show();
}
#pragma endregion