/// QCustomPlotEX.h - QCustomPlot Class Extension Implementation
/// Written By Jesse Z. Zhong
#ifndef __QCustomPlotEX_h__
#define __QCustomPlotEX_h__
#pragma region Includes
#include "stdafx.h"
#include <QRubberBand>
#pragma endregion
#pragma region Defaults
// Default curve and plot color.
const QColor DEFAULT_COLOR = Qt::darkCyan;

// Size of the scatter plot dots.
const float SCATTER_DOT_SIZE = 0.1f;

// Width of a bold pen.
const float BOLD_PEN_WIDTH = 1.5f;

// The scale rate per scroll wheel move.
const double SCALE_RATE = 0.01;

// The pixel rate at which a plot can be shifted.
const double SHIFT_RATE = 1.0;

// Define to allow bold on selection.
#define BOLD_ON_SELECT
#pragma endregion
#pragma region Plot Data
// Structure for storing data for individual curves.
class PlotData {
public:
	// Constructor
	PlotData() {
		this->X = QVector<double>();
		this->Y = QVector<double>();
		this->Color = DEFAULT_COLOR;
		this->xOffset_ = 0.0;
		this->yOffset_ = 0.0;
		this->xLower_ = 0.0;
		this->xUpper_ = 0.0;
		this->yLower_ = 0.0;
		this->yUpper_ = 0.0;
		this->Selected_ = false;
	}

	// Data points
	QVector<double> X;
	QVector<double> Y;

	// Color of the plot
	QColor Color;
#pragma region X & Y Offset Accessors
	// Offset getters.
	inline double GetXOffset() const { return this->xOffset_; }
	inline double GetYOffset() const { return this->yOffset_; }

	// Offset setters.
	inline void SetXYOffset(double x, double y) {

		// Iterate through all points and adjust the values.
		double differenceX = x - this->xOffset_;
		double differenceY = y - this->yOffset_;
		if(this->X.size() == this->Y.size()) {
			for(int i = 0, j = this->X.size(); i < j; i++) {
				this->X[i] += differenceX;
				this->Y[i] += differenceY;
			}
		}

		// Set the internal values.
		this->xOffset_ = x;
		this->yOffset_ = y;
	}
	inline void SetXOffset(double val) {

		// Iterate through all points and adjust the values.
		double difference = val - this->xOffset_;
		for(int i = 0, j = this->X.size(); i < j; i++)
			this->X[i] += difference;

		// Set the internal value.
		this->xOffset_ = val;
	}
	inline void SetYOffset(double val) {

		// Iterate through all points and adjust the values.
		double difference = val - this->yOffset_;
		for(int i = 0, j = this->Y.size(); i < j; i++)
			this->Y[i] += difference;

		// Set the internal value.
		this->yOffset_ = val;
	}

	// Scales the y axis by a certain rate.
	inline void ScaleY(double rate) {

		// Iterate through all points and adjust the values.
		for(int i = 0, j = this->Y.size(); i < j; i++)
			Y[i] *= rate;

		// Update the max and min values.
		this->yLower_ *= rate;
		this->yUpper_ *= rate;
	}

	// Range getters. Values are adjusted with offset.
	inline double GetXLower() const { return this->xLower_ + this->xOffset_; }
	inline double GetXUpper() const { return this->xUpper_ + this->xOffset_; }
	inline double GetYLower() const { return this->yLower_ + this->yOffset_; }
	inline double GetYUpper() const { return this->yUpper_ + this->yOffset_; }

	// Range setters.
	inline void SetXLower(double val) { this->xLower_ = val; }
	inline void SetXUpper(double val) { this->xUpper_ = val; }
	inline void SetYLower(double val) { this->yLower_ = val; }
	inline void SetYUpper(double val) { this->yUpper_ = val; }

	// Indicates if the plot is selected.
	inline bool GetSelected() const { return this->Selected_; }
	inline void SetSelected(bool selected) { this->Selected_ = selected; }
#pragma endregion
private:
#pragma region Members
	double xOffset_;
	double yOffset_;
	double xLower_;
	double xUpper_;
	double yLower_;
	double yUpper_;
	bool Selected_;
#pragma endregion
};
#pragma endregion
// Extension of the QCustomPlot class that allows an
// implementation of the class with different event handlers.
class QCustomPlotEX : public QCustomPlot {
public:
#pragma region Instance
	// Constructor
	QCustomPlotEX(QWidget* parent) : QCustomPlot(parent) {

		// Initialize graphing data.
		this->Data_ = new list<PlotData*>();
		this->XLower_ = 0;
		this->XUpper_ = 0;
		this->YLower_ = 0;
		this->YUpper_ = 0;
		this->RescaleAxis_ = false;
		this->IsScatterPlot_ = false;
		this->PlottableList_ = map<QCPAbstractPlottable*, PlotData*>();

		// Initialize event handling members.
		this->Origin_ = QPoint();
		this->FullXLower_ = 0;
		this->FullXUpper_ = 0;
		this->FullYLower_ = 0;
		this->FullYUpper_ = 0;
		this->CtrlLeftClick_ = false;
		this->IsPlotGrabbed_ = false;
		this->SelectionBox_ = new QRubberBand(QRubberBand::Rectangle, this);
		this->SelectedPlot_ = NULL;
		this->SelectedPlotData_ = NULL;
		this->DefaultPenWidth_ = QPen().widthF();
		this->IsSelectBoldfaced_ = false;

		// Set focus level for handling keyboard input.
		this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	}

	// Destructor
	~QCustomPlotEX() {
		// Delete the data for plots and curves.
		for(auto i = this->Data_->begin(), 
			j = this->Data_->end(); i != j; i++) {
				delete (*i);
				*i = NULL;
		}
		this->Data_->clear();
		delete this->Data_;
		this->Data_ = NULL;

		// Delete the curves and plots.
		// NOTE: Allow QCustomPlot to handle plottable deletion.
		// NOTE: The value is assumed to already
		// be deleted at this point. Refer to above.
// 		for(auto i = this->PlottableList_.begin(), 
// 			j = this->PlottableList_.end(); i != j; i++) {
// 				if((*i).first != NULL) {
// 					delete (*i).first;
// 				}
// 		}
		this->PlottableList_.clear();

		// Delete the selection box.
		if(this->SelectionBox_ != NULL) {
			delete this->SelectionBox_;
			this->SelectionBox_ = NULL;
		}
	}
#pragma endregion
#pragma region Accessors
	// Sets the full x axis range that can be returned to at any time.
	void SetXAxis(double lower, double upper) {
		this->xAxis->setRange(lower, upper);
		this->FullXLower_ = lower;
		this->FullXUpper_ = upper;
	}

	// Sets the full y axis range that can be returned to at any time.
	void SetYAxis(double lower, double upper) {
		this->yAxis->setRange(lower, upper);
		this->FullYLower_ = lower;
		this->FullYUpper_ = upper;
	}

	// Sets the labels for the x and y axis.
	void SetXLabel(string label) { this->XAxisLabel_ = label; }
	void SetYLabel(string label) { this->YAxisLabel_ = label; }

	// Returns the pointer to the plot data.
	list<PlotData*>* GetData() { return this->Data_; }

	// Set or get the ability for the graph to
	// resize itself along with changes in data.
	void SetRescaleAxis(bool automaticallyResizes) { this->RescaleAxis_ = automaticallyResizes; }

	// Set if a plot will be boldfaced when selected.
	void SetBoldfacedSelect(bool isBold) { this->IsSelectBoldfaced_ = isBold; }

	// Axis range accessors.
	double GetXLower() const { return this->XLower_; }
	double GetXUpper() const { return this->XUpper_; }
	double GetYLower() const { return this->YLower_; }
	double GetYUpper() const { return this->YUpper_; }
	void SetXLower(double val) { this->XLower_ = val; }
	void SetXUpper(double val) { this->XUpper_ = val; }
	void SetYLower(double val) { this->YLower_ = val; }
	void SetYUpper(double val) { this->YUpper_ = val; }

	// Axis full range accessors.
	double GetFullXLower() const { return this->FullXLower_; }
	double GetFullXUpper() const { return this->FullXUpper_; }
	double GetFullYLower() const { return this->FullYLower_; }
	double GetFullYUpper() const { return this->FullYUpper_; }
	void SetFullXLower(double val) { this->FullXLower_ = val; }
	void SetFullXUpper(double val) { this->FullXUpper_ = val; }
	void SetFullYLower(double val) { this->FullYLower_ = val; }
	void SetFullYUpper(double val) { this->FullYUpper_ = val; }
#pragma endregion
#pragma region Draw Methods
	// Clears and redraws the graph.
	void Refresh() {

		// Clears old plots and curves.
		this->clearPlottables();
		this->clearGraphs();
		this->clearItems();
		this->PlottableList_.clear();

		// Sets the user interaction level.
		this->setInteraction(QCustomPlot::iSelectPlottables);

		// Add plots to the graph.
		this->AddPlots();

		// Set label names into the graph.
		this->xAxis->setLabel(this->XAxisLabel_.c_str());
		this->yAxis->setLabel(this->YAxisLabel_.c_str());

		// Set the graphs drawable ranges.
		this->xAxis->setRange(this->XLower_, this->XUpper_);
		this->yAxis->setRange(this->YLower_, this->YUpper_);

		// Set other graph settings.
		if(this->RescaleAxis_)
			this->rescaleAxes();
		
		// Redraw the graph.
		this->replot();
	}

	// Safely removes a plot from the graph.
	void Remove(PlotData* plotData) {

		// Ensure that the selected plot data
		// is nulled if it references the same pointer.
		if(this->SelectedPlotData_ == plotData)
			this->SelectedPlotData_ = NULL;

		// Remove the data from the list.
		this->Data_->remove(plotData);
	}

	// Resets the view port.
	void ResetView() {

		// Reset the viewable range to the original.
		this->xAxis->setRange(this->XLower_ = this->FullXLower_,
			this->XUpper_ = this->FullXUpper_);
		this->yAxis->setRange(this->YLower_ = this->FullYLower_,
			this->YUpper_ = this->FullYUpper_);

		// Redraw the plot.
		// NOTE: Replot is called instead of reloading all of the data.
		this->replot();
	}
#pragma endregion
protected:
#pragma region Data and Drawing
	// Adds a new graph item to the graph list.
	void AddPlots() {

		// Iterate through list to add plots.
		for(auto i = this->Data_->begin(), 
			j = this->Data_->end(); i != j; i++) {

				// Create an abstract plot used for 
				// storing and adding new plots and curves.
				QCPAbstractPlottable* tempPlottable;

				// Check if the graph type is a scatter plot.
				if(this->IsScatterPlot_) {

					// Create a new scatter plot.
					QCPGraph *ScatterGraph = new QCPGraph(this->xAxis, 
						this->yAxis);

					// Add the new plot as a new entry in the graph.
					this->addPlottable(ScatterGraph);
					ScatterGraph->setData((*i)->X, (*i)->Y);

					// Adjust the colors of the new plot.
					QPen drawPen = QPen((*i)->Color);
					drawPen.setWidthF(((*i)->GetSelected()) ? BOLD_PEN_WIDTH : this->DefaultPenWidth_);
					ScatterGraph->setPen(drawPen);
					ScatterGraph->setScatterStyle(QCP::ssDisc);
					ScatterGraph->setScatterSize(SCATTER_DOT_SIZE);
					ScatterGraph->setLineStyle(QCPGraph::lsNone);

					// Reference the new plot to be 
					// stored in the list of graphs later.
					tempPlottable = ScatterGraph;

				} else {

					// Create a new curve.
					QCPCurve *CurveGraph = new QCPCurve(this->xAxis, 
						this->yAxis);

					// Add the new curve as a new entry in the graph.
					this->addPlottable(CurveGraph);
					CurveGraph->setData((*i)->X, (*i)->Y);

					// Adjust the colors of the new curve.
					QPen drawPen = QPen((*i)->Color);
					drawPen.setWidthF(((*i)->GetSelected()) ? BOLD_PEN_WIDTH : this->DefaultPenWidth_);
					CurveGraph->setPen(drawPen);

					// Reference the new curve to be
					// stored in the list of graphs later.
					tempPlottable = CurveGraph;
				}

				// Add new curve or plot to the list of plots.
				this->PlottableList_.insert(pair<QCPAbstractPlottable*, 
					PlotData*>(tempPlottable, (*i)));
		}
	}

	// List of curves and plots in this graph.
	map<QCPAbstractPlottable*, PlotData*> PlottableList_;

	// Data point collections for multiple plots and curves.
	list<PlotData*>* Data_;

	// Flag for indicating if the graph can 
	// resize with the change in data points.
	bool RescaleAxis_;

	// Changes the style of plot between curve and scatter. [TODO: Add Accessors]
	bool IsScatterPlot_;

	// Upper and lower bounds for X and Y axises.
	// NOTE: This value is used in the redrawing of the viewport and graph.
	double XLower_;
	double XUpper_;
	double YLower_;
	double YUpper_;

	// Labels for X and Y Axises.
	string XAxisLabel_;
	string YAxisLabel_;
#pragma endregion
#pragma region Mouse Action Events
	// Override the mouse press event to incorporate extra behavior.
	void mousePressEvent(QMouseEvent *event) {

		// Check if the button pressed is the left mouse button.
		if(event->button() == Qt::MouseButton::LeftButton) {

			// Check if there is a selected plot or not.
			if(this->SelectedPlotData_ != NULL) {

				// Change the selection state of the plot.
				if(this->IsSelectBoldfaced_)
					this->SelectedPlotData_->SetSelected(false);

				// Return the selected plot to null.
				this->SelectedPlotData_ = NULL;
			}

			// Check if a plot is selected.
			if (this->SelectedPlot_ = plottableAt(event->pos(), false)) {

				// Localize plot data.
				if(this->PlottableList_.find(this->SelectedPlot_)
					!= this->PlottableList_.end()) {
						this->SelectedPlotData_ = this->PlottableList_[this->SelectedPlot_];

						// Change the selection state of the plot.
						if(this->IsSelectBoldfaced_)
							this->SelectedPlotData_->SetSelected(true);

						// Clear the selected plot.
						// NOTE: Plot will become irrelevant on redraw.
						this->SelectedPlot_ = NULL;
				}

				// Set the position of the click.
				this->Origin_ = event->pos();
				this->IsPlotGrabbed_ = true;

				// Redraw the plots.
				if(this->IsSelectBoldfaced_)
					this->Refresh();
			} else {

				// Pull the starting position of the mouse.
				this->Origin_ = event->pos();

				// Change the dimensions of the selection box.
				if(Util::CheckBoundaries(this->Origin_, this->BoundingArea())) {
					this->SelectionBox_->setGeometry(QRect(this->Origin_, QSize()));
					this->SelectionBox_->show();
				}

				// Change the state.
				this->CtrlLeftClick_ = true;
			}

			// Set the mouse dragging flag to true.
			this->mDragging = true;
		}

		// Check if right mouse button was pressed.
		if(event->button() == Qt::MouseButton::RightButton) {

			this->ResetView();
		}

		// Call base event.
		QWidget::mousePressEvent(event);
	}

	// Override the original mouse event to handle a different behavior.
	void mouseMoveEvent(QMouseEvent *event) {

		// Emit the mouse move event.
		emit mouseMove(event);

		// Check if the mouse is clicked and dragging.
		if(this->mDragging) {

			// Check if the control key was pressed.
			if(this->CtrlLeftClick_) {

				// Localize the position.
				QPoint currPos = event->pos();

				// Localize the bounding area of the plot.
				QRect boundingArea = this->BoundingArea();

				// Update the dimensions of the selection box.
				this->SelectionBox_->setGeometry(QRect(this->Origin_,
					Util::CheckPoint(currPos, boundingArea)).normalized());

			} else {

				// Check if a plot is currently selected.
				if(this->IsPlotGrabbed_ && this->SelectedPlotData_) {

					// Localize the position of the mouse.
					QPoint mp = event->pos();

					// Calculate the offsets.
					double xOffset = this->xAxis->pixelToCoord(mp.x()) 
						- this->xAxis->pixelToCoord(this->Origin_.x());
					double yOffset = this->yAxis->pixelToCoord(mp.y()) 
						- this->yAxis->pixelToCoord(this->Origin_.y());

					// Offset the data.
					this->SelectedPlotData_->SetXYOffset(this->SelectedPlotData_->GetXOffset() 
						+ xOffset, this->SelectedPlotData_->GetYOffset() + yOffset);

					// Set the new lower and upper bounds.
					this->AdjustRange();

					// Redraw the plots.
					this->Refresh();
				}

				// Save the current position of the mouse.
				this->Origin_ = event->pos();
			}
		}
		
		// Call base widget event handler.
		QWidget::mouseMoveEvent(event);
	}

	// Override the mouse release event to incorporate extra behavior.
	void mouseReleaseEvent(QMouseEvent* event) {

		// Check if the button released was the left mouse button.
		if(event->button() == Qt::MouseButton::LeftButton) {

			// Check if the control key was pressed.
			if(this->CtrlLeftClick_) {

				// Localize the geometry of the selection box.
				QRect selectArea = this->SelectionBox_->geometry();

				// Set the view range for the x axis.
				this->xAxis->setRange(this->XLower_ = this->xAxis->pixelToCoord(selectArea.x()),
					this->XUpper_ = this->xAxis->pixelToCoord(selectArea.x() + selectArea.width()));

				// Set the view range for the y axis.
				this->yAxis->setRange(this->YLower_ = this->yAxis->pixelToCoord(selectArea.y()),
					this->YUpper_ = this->yAxis->pixelToCoord(selectArea.y() + selectArea.height()));

				// Redraw the plot.
				// NOTE: Replot is called instead of reloading all of the data.
				this->replot();

				// Stop drawing the selection box.
				this->SelectionBox_->hide();

				// Clear the state.
				this->CtrlLeftClick_ = false;
			} 

			// Set the selectable state to false.
			this->IsPlotGrabbed_ = false;

			// Set the mouse dragging flag to false.
			this->mDragging = false;
		}

		// Call base event handler.
		QWidget::mouseReleaseEvent(event);
	}

	// Override the scroll wheel event to incorporate y axis scaling.
	void wheelEvent(QWheelEvent *event) {
		emit mouseWheel(event);

		// Check if a plot has been selected.
		if(this->SelectedPlotData_ != NULL) {

			// Localize wheel value.
			double stepSize = event->delta();
			double scaleRate = 1 + ((stepSize > 0) ? SCALE_RATE : -SCALE_RATE);

			// Alter the values.
			this->SelectedPlotData_->ScaleY(scaleRate);

			// Set the new lower and upper bounds.
			this->AdjustRange();

			// Redraw the plots.
			this->Refresh();
		}

		// Call base event handler.
		QWidget::wheelEvent(event);
	}
#pragma endregion
#pragma region Keyboard Events
	// Override the key press event to handle special behavior.
	void keyPressEvent(QKeyEvent* event) {
		
		// Check a plot is selected.
		if(this->SelectedPlotData_) {

			// Calculate the adjusted shift rate.
			int xShift(0), yShift(0);

			// Shifts a graph left using the left key.
			if(event->key() == Qt::Key::Key_Left)
				xShift += -1;

			// Shifts a graph right using the right key.
			if(event->key() == Qt::Key::Key_Right)
				xShift += 1;

			// Shifts a graph up using the up key.
			if(event->key() == Qt::Key::Key_Up)
				yShift += 1;
			
			// Shifts a graph down using the down key.
			if(event->key() == Qt::Key::Key_Down)
				yShift += -1;

			// Offset the plot data.
			this->SelectedPlotData_->SetXYOffset(this->SelectedPlotData_->GetXOffset() 
				+ SHIFT_RATE * xShift, this->SelectedPlotData_->GetYOffset() + SHIFT_RATE * yShift);

			// Set the new lower and upper bounds.
			this->AdjustRange();

			// Redraw the plots.
			this->Refresh();
		}

		// Call base event handler.
		QWidget::keyPressEvent(event);
	}

	// Override the key release event to handle special behavior.
	void keyReleaseEvent(QKeyEvent* event) {

		// Call base event handler.
		QWidget::keyReleaseEvent(event);
	}
#pragma endregion
#pragma region Event Members
	// Sets in place the new upper and lower bounds.
	void AdjustRange() {

		// Declare intermediate variables.
		// NOTE: The initialization values are 0.
		// This means no min should be above 0 and no
		// max should be below 0. i.e. There is a purpose.
		double xLower(0), xUpper(0), yLower(0), yUpper(0);

		// Iterate through and rejudge maximums and minimums.
		for(auto i = this->Data_->begin(), 
			j = this->Data_->end(); i != j; i++) {

				// Localize for consistency purposes.
				double iXLower = (*i)->GetXLower();
				double iXUpper = (*i)->GetXUpper();
				double iYLower = (*i)->GetYLower();
				double iYUpper = (*i)->GetYUpper();

				// Perform comparisons.
				xLower = (xLower > iXLower) ? iXLower : xLower;
				xUpper = (xUpper < iXUpper) ? iXUpper : xUpper;
				yLower = (yLower > iYLower) ? iYLower : yLower;
				yUpper = (yUpper < iYUpper) ? iYUpper : yUpper;
		}

		// Reassign the maximums and minimums.
		this->FullXLower_ = xLower;
		this->FullXUpper_ = xUpper;
		this->FullYLower_ = yLower;
		this->FullYUpper_ = yUpper;
	}

	// Returns the bounding area of plot view area.
	QRect BoundingArea() const {

		// Create a bounding area out of the graph margins.
		QRect plotGeo = this->geometry();
		return QRect(this->marginLeft(), this->marginTop(), 
			(plotGeo.width()/* - this->marginLeft() - this->marginRight()*/), 
			(plotGeo.height() - this->marginTop() - this->marginBottom()));
	}

	// Used for visualizing a mouse selection area.
	QRubberBand* SelectionBox_;

	// The starting point of a mouse selection.
	QPoint Origin_;

	// Stores the full viewable range on the x axis.
	double FullXUpper_;
	double FullXLower_;

	// Stores the full viewable range on the y axis.
	double FullYUpper_;
	double FullYLower_;

	// Record the state initiated by ctrl + left click.
	bool CtrlLeftClick_;

	// Pointer to a previously selected plot.
	QCPAbstractPlottable* SelectedPlot_;

	// Pointer to the plot data of a selected plot.
	PlotData* SelectedPlotData_;

	// Indicates that a plot is currently being selected.
	bool IsPlotGrabbed_;

	// Stores the default pen width.
	float DefaultPenWidth_;

	// Indicates if selected plots should be drawn with boldface.
	bool IsSelectBoldfaced_;
#pragma endregion
};

#endif // End : __QCustomPlotEX_h__