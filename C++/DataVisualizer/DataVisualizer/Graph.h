/// Graph.h - Graph Template Class Implementation
/// Written By Jesse Z. Zhong
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "stdafx.h"
#include "ProjectSettings.h"
#include "SnapshotData.h"
#include "RPK.h"

using namespace std;

// Default Color
const QColor DEFAULT_COLOR = Qt::darkCyan;

// Default Geometry
const QRect DEFAULT_GEOMETRY = QRect(0, 0, 400, 400);

// Default Color
extern const QColor DEFAULT_COLOR;

// Default Geometry
extern const QRect DEFAULT_GEOMETRY;

// Size of the Scatter Plot Dots
const float SCATTER_DOT_SIZE = 0.1f;

// Handles the Basic Requirements for Reading Data
// and Drawing them to Graphs
template<typename T>
class Graph {
public:
    // Default Constructor
    Graph(QWidget* parent) {
        Graph_ = new QCustomPlot(parent);
        
        Geometry_ = DEFAULT_GEOMETRY;
        
        NumberOfGraphs_ = 0;
        CurrentGraph_ = 0;
        XLower_ = 0;
        XUpper_ = 0;
        YLower_ = 0;
        YUpper_ = 0;
        
        resizeGraph_ = true;
        
        scatterPlot_ = false;
    }

	// Destructor
    ~Graph() {
        delete Graph_;
        
        GraphList_.clear();
    }

	// Sets All the Plots Into the Graph and Returns the Graph
    QCustomPlot* InitializeGraph(
            const QRect& rect,
            string xAxisLabel, string yAxisLabel) {
        
		// Set Geometry
		Geometry_ = rect;
        
		// Set Fields
		XAxisLabel_ = xAxisLabel;
		YAxisLabel_ = yAxisLabel;
        
		// Call Refresh to Create Plots and Graph
		RefreshGraph();
		
		// Return the Graphs
		return Graph_;
    }

	// Returns the Graph
    QCustomPlot* GetGraph() {
        RefreshGraph();
        return Graph_;
    }
	
	// Method Used for Storing Snapshot Data
    void StorePoints(T& data) {
        
        // Process Data to Points
        ProcessPoints(data);
    }

	// Sets the Plot Color of a Certain Plot
    void SetPlotColor(QColor color, int index) {
        if((!ColorList_.empty()) && (index >= 0) &&
           ((unsigned)index < ColorList_.size())) {
            ColorList_[index] = color;
            RefreshGraph();
        }
    }

	// Adjust the Size and Position of the Graph
    void SetGeometry(const QRect& rect) {
        Geometry_ = rect;
        RefreshGraph();
    }
    void SetGeometry(int x, int y, int width, int height) {
        Geometry_ = QRect(x, y, width, height);
        RefreshGraph();
    }
    
    // If True, the Graphs will Automatically Resize
    // themselves for Each New Plot
    void SetAutomaticResize(bool automaticallyResizes) {
        resizeGraph_ = automaticallyResizes;
    }
    
    // Sets Up and Refreshes the Graph
    void RefreshGraph() {
        RefreshGraph(CurrentGraph_);
    }
    void RefreshGraph(int index) {
        
        // Clear Old Plots First
        //Graph_->clearData();
        Graph_->clearPlottables();
        Graph_->clearGraphs();
        Graph_->clearItems();
        
        // Sets Color List
        if(ColorList_.empty() &&
           ((unsigned)NumberOfGraphs_ != ColorList_.size()))
            ColorList_.resize(NumberOfGraphs_, DEFAULT_COLOR);
        
        // Set the User Interactive Level
        Graph_->setInteraction(QCustomPlot::iSelectPlottables);
        
        // Add Plots
        for(int i = 0; i < NumberOfGraphs_; i++)
            AddPlot(index, i);
        
        // Set Label Names
        Graph_->xAxis->setLabel(XAxisLabel_.c_str());
        Graph_->yAxis->setLabel(YAxisLabel_.c_str());
        
        // Set Graphing Range
        Graph_->xAxis->setRange(XLower_, XUpper_);
        Graph_->yAxis->setRange(YLower_, YUpper_);
        
        // Graph Settings
        Graph_->setRangeDrag(Qt::Horizontal | Qt::Vertical);
        Graph_->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        Graph_->setGeometry(Geometry_);
        Graph_->setupFullAxesBox();
        if(resizeGraph_)
            Graph_->rescaleAxes();
        
        Graph_->replot();
        
        // Update Graph Number
        CurrentGraph_ = index;
    }

protected:
    // Abstract Method for Interpreting Data
    virtual void ProcessPoints(T& data) = 0;

	// Adds a New Plot to Graph
    void AddPlot(int index, int graphNumber) {
        
		if(CheckBounds(index) &&
           (!xPoints_[index].empty()) && (!yPoints_[index].empty()) &&
           (xPoints_[index].size() > (unsigned)graphNumber) &&
           (yPoints_[index].size() > (unsigned)graphNumber)) {
            
            // Temporary Plottable
            QCPAbstractPlottable* tempPlottable;
            
            if(scatterPlot_) {
                QCPGraph *ScatterGraph = new QCPGraph(Graph_->xAxis, Graph_->yAxis);
                
                // Create New Graph Entry and Set Data
                Graph_->addPlottable(ScatterGraph);
                ScatterGraph->setData(xPoints_[index][graphNumber],
                                      yPoints_[index][graphNumber]);
                
                // Color Settings
                ScatterGraph->setPen(QPen(ColorList_[graphNumber]));
                ScatterGraph->setScatterStyle(QCP::ssDisc);
                ScatterGraph->setScatterSize(SCATTER_DOT_SIZE);
                ScatterGraph->setLineStyle(QCPGraph::lsNone);
                
                // Add Plottable to Graph List
                //tempArray.push_back(ScatterGraph);
                tempPlottable = ScatterGraph;
            
            } else {
                QCPCurve *CurveGraph = new QCPCurve(Graph_->xAxis, Graph_->yAxis);
                
                // Create New Graph Entry and Set Data
                Graph_->addPlottable(CurveGraph);
                CurveGraph->setData(xPoints_[index][graphNumber],
                                    yPoints_[index][graphNumber]);
                
                // Color Settings
                CurveGraph->setPen(QPen(ColorList_[graphNumber]));
                
                // Add Plottable to Graph List
                //tempArray.push_back(CurveGraph);
                tempPlottable = CurveGraph;
            }
            
            // Check if Graph Element Exists
            if((!GraphList_.empty()) && ((int)GraphList_.size() > index)) {
                
                // Check that there is Allocated Space for Multiple Plots or Not
                if((!GraphList_[index].empty()) && ((int)GraphList_[index].size() > graphNumber)) {
                    GraphList_[index][graphNumber] = tempPlottable;
                } else {
                    // Create a Temporary Array and Store
                    vector<QCPAbstractPlottable*> tempArray;
                    tempArray.push_back(tempPlottable);
                    
                    // Push into Graph List
                    GraphList_.push_back(tempArray);
                }
            } else {
                // Create a Temporary Array and Store
                vector<QCPAbstractPlottable*> tempArray;
                tempArray.push_back(tempPlottable);
                
                // Push into Graph List
                GraphList_.push_back(tempArray);
            }
		}
    }
    
    // Check if Index is within the Max
    // the Number of Data Points Stored
    bool CheckBounds(int index) const {
        if((index < 0) || (index >= (int)xPoints_.size()) || (index >= (int)yPoints_.size())) {
            throw "Index exceeded bounds in Graph.";
            return false;
        }
        return true;
    }
    
    // Point Collections
    vector<vector<QVector<double> > > xPoints_;
    vector<vector<QVector<double> > > yPoints_;
    
    // Graph Pointers
    vector<vector<QCPAbstractPlottable*> > GraphList_;

	// A Single Plot-able Graph
	QCustomPlot* Graph_;

	// List of Line Colors
	vector<QColor> ColorList_;

	// Number of Graphs
	int NumberOfGraphs_;
    
    // Current Graph Number
    int CurrentGraph_;

	// Label for X and Y Axises
	string XAxisLabel_;
	string YAxisLabel_;

	// Range Bounds for X and Y Axises
	double XLower_;
	double XUpper_;
	double YLower_;
	double YUpper_;

	// Position and Dimensions QRect
	QRect Geometry_;
    
    // Resize Graphs Flag
    bool resizeGraph_;
    
    // Toggle Scatter Plot
    bool scatterPlot_;
};

#endif
