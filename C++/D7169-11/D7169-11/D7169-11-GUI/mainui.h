// MainUI.h - Main UI Class Implementation.
// Written By Jesse Z. Zhong
#ifndef MAINUI_H
#define MAINUI_H
#pragma region Includes
#include <QMainWindow>
#include <QSettings>
#include "MainUIClassEX.h"
#include "SignalListEX.h"
#include "ConfigureUIEX.h"
using namespace std;
#pragma endregion
#pragma region Window Titles
const string ApplicationName = "D7169-11";
const string OrganizationName = "Quantum Potential Corporation";
const string SignalTitle = "Signals";
const string ConfigTitle = "Configurations";
#pragma endregion
// The implementation of the main form.
class MainUI : public QMainWindow {
	Q_OBJECT
public:
#pragma region Instance
	// Constructor
	MainUI(QWidget* parent = NULL)
		: QMainWindow(parent) {
			// Program data storage containers.
			this->DataFiles_ = map<QString, pair<DataFile*, PlotData*>>();
			this->TableElements_ = map<QString, QTableWidgetItem*>();
			this->ProgramSettings_ = new QSettings(QString(OrganizationName.c_str()), 
				ApplicationName.c_str(), this);

			// Initialize the main form.
			this->UI_.setupUi(this);
			this->UI_.Init(this);
			this->setWindowTitle(tr(ApplicationName.c_str()));

			// Initialize the signal box.
			this->SignalBox_ = new QDialog(this);
			this->SignalList_.setupUi(this->SignalBox_);
			this->SignalList_.Init(this->SignalBox_);
			this->SignalBox_->setWindowTitle(tr(SignalTitle.c_str()));

			// Initialize the configure box.
			this->ConfigureBox_ = new QDialog(this);
			this->ConfigureUI_.setupUi(this->ConfigureBox_);
			this->ConfigureUI_.Init(this->ConfigureBox_);
			this->ConfigureBox_->setWindowTitle(tr(ConfigTitle.c_str()));

			// Make signal and slot connects
			// for the program's widgets.
			this->ConnectWidgets();
	}

	// Destructor
	~MainUI() {
		// Delete the configuration box.
		delete this->ConfigureBox_;

		// Delete the signal dialog box.
		delete this->SignalBox_;

		// Clear the reader list.
		for(auto i = this->DataFiles_.begin(),
			j = this->DataFiles_.end(); i != j; i++) {
				auto item = i->second;
				if(item.first) {
					delete item.first;
					item.first = NULL;
				}
 				// Let QCustomPlot handle 
				// the deletion of plot data.
		}
		this->DataFiles_.clear();
	}
#pragma endregion
signals:
#pragma region Signals

#pragma endregion
private slots:
#pragma region Private Slots
	// Opens file dialog, waits for the user to choose
	// a file, loads it through a DataFile, registers
	// the reader in the list, and proceeds to draw graphs.
	void LoadNewData();

	// Removes a specific signal's data set and redraws graph.
	void RemoveData(QTableWidgetItem* item);
	void RemoveData();

	// Saves all the data back to their original files. [CDF Only]
	void SaveData();

	// Displays the signal list box.
	void ShowSignals();

	// Enables signal list box buttons Remove 
	// and Configure when a list item is selected.
	void EnableSignalButtons();

	// Disables signal list box buttons Remove
	// and Configure when a list item is deselected.
	// NOTE: This is not used as a slot at the moment. When
	// a QListWidget is selected, it saves the last selection.
	void DisableSignalButtons();

	// Displays the signal configuration window after
	// loading the signal specific changes into the form.
	void ShowConfiguration();

	// Updates the information displayed in the
	// configuration form according to a specific key.
	void UpdateConfigDisplay(const QString& key);

	// Updates a specific signal data with the
	// values in the fields of the configuration box.
	void UpdateSignalConfig();

	// Prompts user with a color dialog that
	// will change the color display color.
	void ChangeSignalColor();

	// Loads the list of recently opened files from the registry.
	void LoadRecentFilesList();

	// Updates the list of items featured in the recently
	// opened list and update the items stored in the registry.
	void UpdateRecentFilesList();
#pragma endregion
private:
#pragma region Helper Methods
	// Manages the connection of signals and slots.
	void ConnectWidgets();
#pragma endregion
#pragma region Program Forms
	// The main ui form window for this program.
	Ui::MainUIClassEX UI_;

	// Form used for listing all loaded signals.
	Ui::SignalListEX SignalList_;
	QDialog* SignalBox_;

	// Form used for configuring individual signals.
	Ui::ConfigureUIEX ConfigureUI_;
	QDialog* ConfigureBox_;
#pragma endregion
#pragma region Data Storage
	// List of readers used to read and store data.
	map<QString, pair<DataFile*, PlotData*>> DataFiles_;

	// Maps a sample ID to its corresponding element in the signal list.
	map<QString, QTableWidgetItem*> TableElements_;

	// Reads and writes the system settings for the program.
	QSettings* ProgramSettings_;
#pragma endregion
};

#endif // MAINUI_H
