// QCPAxisEX.h - QCPAxis Class Extension
// Written By Jesse Z. Zhong
#ifndef __QCPAxisEX_h__
#define __QCPAxisEX_h__
#pragma region Includes
#include "stdafx.h"
#include <QScrollBar>
using namespace std;
#pragma endregion
#pragma region Constants
// Sets the starting state of the scroll bar.
// NOTE: False is hidden; True is show.
const bool DefaultScrollState = false;

// The height of the scroll bar.
const int ScrollBarHeight = 20;
#pragma endregion
// Extends the axis class to accommodate scrolling on zoom.
class QCPAxisEX : public QCPAxis {
public:
	// Constructor
	QCPAxisEX(QCustomPlot* parentPlot,
		QCPAxis::AxisType type) : QCPAxis(parentPlot, type) {
			this->ScrollBar_ = new QScrollBar(parentPlot);
			this->ScrollBar_->setEnabled(DefaultScrollState);
			this->ScrollBar_->setHidden(!DefaultScrollState);
			this->IsZoomed_ = DefaultScrollState;
	}

	// Sets if the viewport is zoomed or not.
	void SetIsZoomed(bool isZoomed) { this->IsZoomed_ = isZoomed; }

	// Returns the reference to the scroll bar.
	QScrollBar* GetScrollBar() { return this->ScrollBar_; }
protected:
	// Overload the draw method to incorporate scroll bars.
	void draw(QCPPainter* painter) {

		// Sets the origin and the orientation of the axis.
		QPoint origin;
		if (mAxisType == atLeft)
			origin = mAxisRect.bottomLeft();
		else if (mAxisType == atRight)
			origin = mAxisRect.bottomRight();
		else if (mAxisType == atTop)
			origin = mAxisRect.topLeft();
		else if (mAxisType == atBottom)
			origin = mAxisRect.bottomLeft();

		// Sets the origin values.
		double xCor = 0, yCor = 0;
		switch (mAxisType) {
		case atTop: yCor = -1; break;
		case atRight: xCor = 1; break;
		default: break;
		}

		// Localizing the max and min tick values.
		int margin = 0;
		int lowTick = mLowestVisibleTick;
		int highTick = mHighestVisibleTick;
		double t;

		// Declare variables for storing line drawing endpoints.
		QPointF lineStart, lineEnd;

		// Draws the base line of the axis depending on its orientation.
		painter->setPen(getBasePen());
		if (orientation() == Qt::Horizontal)
			painter->drawLine(QLineF(lineStart = origin + QPointF(xCor, yCor), 
			lineEnd = origin + QPointF(mAxisRect.width() + xCor, yCor)));
		else
			painter->drawLine(QLineF(lineStart = origin + QPointF(xCor, yCor), 
			lineEnd = origin + QPointF(xCor, - mAxisRect.height() + yCor)));

		// Enable the scroll bar if zoomed.
		// NOTE: Scroll bar is only allowed for bottom x axis.
		if(this->IsZoomed_ && (mAxisType == atBottom)) {

			// Set the orientation of the scroll bar to horizontal.
			this->ScrollBar_->setOrientation(Qt::Orientation::Horizontal);

			// Calculate the position and dimensions of the scroll bar.
			QRect geom = QRect(lineStart.x(), lineStart.y() + 1, 
				lineEnd.x() - lineStart.x(), ScrollBarHeight);

			// Assign the new geometry to the scroll bar.
			this->ScrollBar_->setGeometry(geom);

			// Enable and display the scroll bar.
			this->ScrollBar_->setEnabled(true);
			this->ScrollBar_->show();

			// Reset the margin for drawing other items.
			margin = ScrollBarHeight + 1;
		} else {
			// Disable the scroll bar.
			this->ScrollBar_->setEnabled(false);
			this->ScrollBar_->hide();
		}

		// Draw the ticks along the base line.
		if (mTicks) {
			painter->setPen(getTickPen());
			// direction of ticks ("inward" is right for left axis and left for right axis)
			int tickDir = (mAxisType == atBottom || mAxisType == atRight) ? -1 : 1;
			if (orientation() == Qt::Horizontal) {
				for (int i = lowTick; i <= highTick; ++i) {
					t = coordToPixel(mTickVector.at(i)); // x
					painter->drawLine(QLineF(t + xCor, origin.y() - mTickLengthOut * tickDir + yCor,
						t + xCor, origin.y() + mTickLengthIn * tickDir + yCor));
				}
			} else {
				for (int i = lowTick; i <= highTick; ++i) {
					t = coordToPixel(mTickVector.at(i)); // y
					painter->drawLine(QLineF(origin.x() - mTickLengthOut * tickDir + xCor, 
						t + yCor, origin.x() + mTickLengthIn * tickDir + xCor, t + yCor));
				}
			}
		}

		// Draw sub ticks in between the major ticks.
		if (mTicks && mSubTickCount > 0) {
			painter->setPen(getSubTickPen());
			// direction of ticks ("inward" is right for left axis and left for right axis)
			int tickDir = (mAxisType == atBottom || mAxisType == atRight) ? -1 : 1;
			if (orientation() == Qt::Horizontal) {
				for (int i = 0; i<mSubTickVector.size(); i++) { // no need to check bounds because sub ticks are always only created inside current mRange
					t = coordToPixel(mSubTickVector.at(i));
					painter->drawLine(QLineF(t + xCor, origin.y() - mSubTickLengthOut * tickDir + yCor,
						t + xCor, origin.y() + mSubTickLengthIn * tickDir + yCor));
				}
			} else {
				for (int i = 0; i < mSubTickVector.size(); i++) {
					t = coordToPixel(mSubTickVector.at(i));
					painter->drawLine(QLineF(origin.x() - mSubTickLengthOut * tickDir + xCor, t + yCor, 
						origin.x() + mSubTickLengthIn * tickDir + xCor, t + yCor));
				}
			}
		}
		margin += qMax(0, qMax(mTickLengthOut, mSubTickLengthOut));

		// Draw the labels for the major ticks.
		QSize tickLabelsSize(0, 0); // size of largest tick label, for offset calculation of axis label
		if (mTickLabels) {
			margin += mTickLabelPadding;
			painter->setFont(getTickLabelFont());
			painter->setPen(QPen(getTickLabelColor()));
			for (int i=lowTick; i <= highTick; ++i) {
				t = coordToPixel(mTickVector.at(i));
				drawTickLabel(painter, t, margin, mTickVectorLabels.at(i), &tickLabelsSize);
			}
		}
		if (orientation() == Qt::Horizontal)
			margin += tickLabelsSize.height();
		else
			margin += tickLabelsSize.width();

		// Draw the axis labels.
		QRect labelBounds;
		if (!mLabel.isEmpty()) {
			margin += mLabelPadding;
			painter->setFont(getLabelFont());
			painter->setPen(QPen(getLabelColor()));
			labelBounds = painter->fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip, mLabel);
			if (mAxisType == atLeft) {
				QTransform oldTransform = painter->transform();
				painter->translate((origin.x() - margin - labelBounds.height()), origin.y());
				painter->rotate(-90);
				painter->drawText(0, 0, mAxisRect.height(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel);
				painter->setTransform(oldTransform);
			} else if (mAxisType == atRight) {
				QTransform oldTransform = painter->transform();
				painter->translate((origin.x() + margin + labelBounds.height()), origin.y()-mAxisRect.height());
				painter->rotate(90);
				painter->drawText(0, 0, mAxisRect.height(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel);
				painter->setTransform(oldTransform);
			} else if (mAxisType == atTop)
				painter->drawText(origin.x(), origin.y() - margin - labelBounds.height(), mAxisRect.width(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel);
			else if (mAxisType == atBottom)
				painter->drawText(origin.x(), origin.y() + margin, mAxisRect.width(), labelBounds.height(), Qt::TextDontClip | Qt::AlignCenter, mLabel);
		}

		// Set the selection boxes.
		int selAxisOutSize = qMax(qMax(mTickLengthOut, mSubTickLengthOut), mParentPlot->selectionTolerance());
		int selAxisInSize = mParentPlot->selectionTolerance();
		int selTickLabelSize = (orientation() == Qt::Horizontal ? tickLabelsSize.height() : tickLabelsSize.width());
		int selTickLabelOffset = qMax(mTickLengthOut, mSubTickLengthOut) + mTickLabelPadding;
		int selLabelSize = labelBounds.height();
		int selLabelOffset = selTickLabelOffset + selTickLabelSize + mLabelPadding;
		if (mAxisType == atLeft) {
			mAxisSelectionBox.setCoords(mAxisRect.left() - selAxisOutSize, mAxisRect.top(), mAxisRect.left() + selAxisInSize, mAxisRect.bottom());
			mTickLabelsSelectionBox.setCoords(mAxisRect.left() - selTickLabelOffset - selTickLabelSize, mAxisRect.top(), mAxisRect.left() - selTickLabelOffset, mAxisRect.bottom());
			mLabelSelectionBox.setCoords(mAxisRect.left() - selLabelOffset-selLabelSize, mAxisRect.top(), mAxisRect.left() - selLabelOffset, mAxisRect.bottom());
		} else if (mAxisType == atRight) {
			mAxisSelectionBox.setCoords(mAxisRect.right() - selAxisInSize, mAxisRect.top(), mAxisRect.right() + selAxisOutSize, mAxisRect.bottom());
			mTickLabelsSelectionBox.setCoords(mAxisRect.right() + selTickLabelOffset + selTickLabelSize, mAxisRect.top(), mAxisRect.right() + selTickLabelOffset, mAxisRect.bottom());
			mLabelSelectionBox.setCoords(mAxisRect.right() + selLabelOffset + selLabelSize, mAxisRect.top(), mAxisRect.right() + selLabelOffset, mAxisRect.bottom());
		} else if (mAxisType == atTop) {
			mAxisSelectionBox.setCoords(mAxisRect.left(), mAxisRect.top() - selAxisOutSize, mAxisRect.right(), mAxisRect.top() + selAxisInSize);
			mTickLabelsSelectionBox.setCoords(mAxisRect.left(), mAxisRect.top() - selTickLabelOffset - selTickLabelSize, mAxisRect.right(), mAxisRect.top() - selTickLabelOffset);
			mLabelSelectionBox.setCoords(mAxisRect.left(), mAxisRect.top()-selLabelOffset-selLabelSize, mAxisRect.right(), mAxisRect.top() - selLabelOffset);
		} else if (mAxisType == atBottom) {
			mAxisSelectionBox.setCoords(mAxisRect.left(), mAxisRect.bottom() - selAxisInSize, mAxisRect.right(), mAxisRect.bottom() + selAxisOutSize);
			mTickLabelsSelectionBox.setCoords(mAxisRect.left(), mAxisRect.bottom()+selTickLabelOffset+selTickLabelSize, mAxisRect.right(), mAxisRect.bottom() + selTickLabelOffset);
			mLabelSelectionBox.setCoords(mAxisRect.left(), mAxisRect.bottom() + selLabelOffset + selLabelSize, mAxisRect.right(), mAxisRect.bottom() + selLabelOffset);
		}
	}

	// Overload the calculate margin method to include scroll bar size.
	int calculateMargin() const {
		if(this->IsZoomed_ && (mAxisType == atBottom))
			return QCPAxis::calculateMargin() + ScrollBarHeight + 1;
		return QCPAxis::calculateMargin();
	}

private:
	// The scroll bar for shifting the viewport when zoomed.
	QScrollBar* ScrollBar_;

	// Indicates if the view port is zoomed or not.
	bool IsZoomed_;
};

#endif // End : __QCPAxisEX_h__