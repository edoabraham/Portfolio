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
const char* CDFExtension = ".cdf";
const string BackupExtension = ".cdf.bak";
const QString BackupFolder = "/Backup";
const int SampleIDColIndex = 0;
const int SampleFileColIndex = SampleIDColIndex + 1;
#pragma endregion
#pragma region Registry Items
// Registry key for the directory of the last opened file.
const QString FileOpenDirectory = "File Open Directory";

// Registry key for the plot selection boldface option.
const QString SelectionBoldface = "Selection Boldface";

// Registry key for the list of recently opened files.
const QString RecentFiles = "Recently Opened Files";

// The maximum number of items that can
// be stored in the recently opened listened.
const int MaxRecentList = 10;
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
		Util::Print("File open: " + fileName.toStdString());

		// Check if there was a file path read.
		if(fileName != "") {

			// Create a new DataFile for reading the file.
			DataCDF* datFile = new DataCDF();
			Util::Print("New DataFile created. Attempting to parse file...");

			// Begin reading and parsing the file.
			datFile->Read(fileName.toStdString());
			Util::Print("Read file: " + fileName.toStdString());

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
			} else {

				// TODO: Display a dialog message indicating a match.
				Util::Print(datFile->GetFileName() + " already exists.\n");
			}
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
#pragma region Recent Files Action
// Loads the list of recently opened files from the registry.
void MainUI::LoadRecentFilesList() {
	// Localize the list of recent file names.
	QStringList fileNames = this->ProgramSettings_->value(RecentFiles).toStringList();

	// Get the number of file names.
	int numFileNames = qMin(fileNames.size(), MaxRecentList);

	// Iterate through the list of file names and list them in the menu.
	for(int i = 0; i < numFileNames; i++) {
		QString text = fileNames[i];

	}
}
#pragma endregion
#pragma endregion
#pragma region Helper
// Manages the connection of signals and slots.
void MainUI::ConnectWidgets() {
	connect(this->UI_.actionOpen, SIGNAL(triggered()), this, SLOT(LoadNewData()));
	connect(this->UI_.actionSave, SIGNAL(triggered()), this, SLOT(SaveData()));
	connect(this->UI_.SignalsAction, SIGNAL(triggered()), this, SLOT(ShowSignals()));
	connect(this->SignalList_.AddButton, SIGNAL(clicked()), this, SLOT(LoadNewData()));
	connect(this->SignalList_.RemoveButton, SIGNAL(clicked()), this, SLOT(RemoveData()));
	connect(this->SignalList_.ConfigureButton, SIGNAL(clicked()), this, SLOT(ShowConfiguration()));
	connect(this->SignalList_.TableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(EnableSignalButtons()));
	connect(this->SignalList_.TableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(ShowConfiguration()));
	connect(this->ConfigureUI_.SampleCBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(UpdateConfigDisplay(QString)));
	connect(this->ConfigureUI_.OkayButton, SIGNAL(clicked()), this, SLOT(UpdateSignalConfig()));
	connect(this->ConfigureUI_.ColorButton, SIGNAL(clicked()), this, SLOT(ChangeSignalColor()));
}
#pragma endregion