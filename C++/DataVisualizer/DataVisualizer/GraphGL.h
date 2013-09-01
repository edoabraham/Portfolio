// GraphGL.h - GraphGL template class implementation.
// Written By Jesse Z. Zhong
#ifndef __Graph_OpenGL_H__
#define __Graph_OpenGL_H__
#include "stdafx.h"
#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
#include <math.h>
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif
using namespace std;

// Dictates the amount, in degrees, that the camera can
// be rotated around a target; alternatively, it is the
// amount at which the world rotates before the camera
const int RotationIncrement = 16;

// Allows for plots to be rendered in a 3D space
// using OpenGL, within a QWidget window
class GraphGL : public QGLWidget {
    Q_OBJECT
    
public:
    // Constructor
    GraphGL(QWidget *parent = 0)
        : QGLWidget(QGLFormat(QGL::StencilBuffer), parent) {
        
			this->XRotation_ = 0;
			this->YRotation_ = 0;
			this->ZRotation_ = 0;
            
			this->PointColor_ = QColor::fromRgb(255, 255, 255);
			this->BGColor_ = QColor::fromRgb(0, 0, 0);
            
			this->CurrentIndex_ = 0;
    }
    ~GraphGL() {
        
    }
    
    QSize MinimumSizeHint() const {
        return QSize(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    QSize SizeHint() const {
        return QSize(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    
    // Makes reservations on the capacity of the lists.
    void Reserve(int size) {
		if(size < 0)
			throw "GraphGL::Reserve(int size) : Reservation size cannot fall below 0";
		this->X_.reserve(size);
		this->Y_.reserve(size);
		this->Z_.reserve(size);
		this->Colors_.reserve(size);
    }
    
	// Method used to load in one set of points.
	void LoadPoints(const vector<float>& x, const vector<float>& y,
					const vector<float>& z, const vector<QColor> colors) {
        
		unsigned int xSize = x.size();
        
		// Checks if they are identical in size first.
		if((xSize == y.size()) && (xSize == z.size())
			&& (xSize == colors.size())) {
			this->X_.push_back(x);
			this->Y_.push_back(y);
			this->Z_.push_back(z);
			this->Colors_.push_back(colors);
		}
	}
    
	// Changes the index for a set of points to be drawn.
	void Refresh(int index) {
		assert((this->X_.size() == this->Y_.size()) 
			&& (this->X_.size() == this->Z_.size()));
        
		if(!this->X_.empty() && (index >= 0) 
			&& ((unsigned)index < this->X_.size()))
				this->CurrentIndex_ = index;
        
		this->updateGL();
	}
    
public slots:
	// Methods for changing the angle of
	// the camera with respect to the origin.
	void SetXRotation(int angle) {
		this->NormalizeAngle(angle);
		if(angle != this->XRotation_) {
			this->XRotation_ = angle;
			emit this->XRotationChanged(angle);
			this->updateGL();
		}
	}
	void SetYRotation(int angle) {
		this->NormalizeAngle(angle);
		if(angle != this->YRotation_) {
			YRotation_ = angle;
			emit YRotationChanged(angle);
			updateGL();
		}
	}
	void SetZRotation(int angle) {
		this->NormalizeAngle(angle);
		if(angle != this->ZRotation_) {
			this->ZRotation_ = angle;
			emit this->ZRotationChanged(angle);
			this->updateGL();
		}
	}
    
signals:
	// Detects changes to the rotation
	void XRotationChanged(int angle);
	void YRotationChanged(int angle);
	void ZRotationChanged(int angle);
    
protected:
	// Initializes OpenGL.
	void initializeGL() {
		this->qglClearColor(BGColor_);
        
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_MULTISAMPLE);
		static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        
		// Enables vertexes to be drawn with different colors.
		glEnable(GL_COLOR_MATERIAL);
        
		// Blending Options
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
    
	// In charge of rendering the scene per frame.
	void paintGL() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(XRotation_ / RotationIncrement, 1.0, 0.0, 0.0);
		glRotatef(YRotation_ / RotationIncrement, 0.0, 1.0, 0.0);
		glRotatef(ZRotation_ / RotationIncrement, 0.0, 0.0, 1.0);
        
		this->DrawPoints(CurrentIndex_);
	}
    
	// Resizes the viewport.
	void resizeGL(int width, int height) {
		glViewport(0, 0, width, height);
        
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float vheight = width / height;
		glFrustum(-0.005f * vheight,
					+0.005f * vheight,
					-0.005f,
					+0.005f,
					+1.0f,
					+15.0f);
		glMatrixMode(GL_MODELVIEW);
	}
    
	// Draws a set of points using the provided index.
	void DrawPoints(int index) {
		if(!X_.empty() && (index >= 0) && ((unsigned)index < X_.size())) {
			for(int i = 0, j = X_[index].size(); i < j; i++) {
				DrawPoint(X_[index][i], Y_[index][i], Z_[index][i], Colors_[index][i]);
			}
		}
	}

	// Rotation angles.
	int XRotation_;
	int YRotation_;
	int ZRotation_;
    
	QPoint LastPoint_;
	QColor BGColor_;
	QColor PointColor_;
    
	int CurrentIndex_;
    
	// Points lists.
	vector<vector<float> > X_;
	vector<vector<float> > Y_;
	vector<vector<float> > Z_;
	vector<vector<QColor> > Colors_;
    
    // Reference to the list of points.
    
    
private:
	void NormalizeAngle(int& angle) {
		while (angle < 0)
			angle += 360 * RotationIncrement;
		while (angle > (360 * RotationIncrement))
			angle -= 360 * RotationIncrement;
	}
    
	// Draws a single point in a given color
	void DrawPoint(const float& x, const float& y,
					const float& z, const QColor& color) {
		qglColor(color);
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
	}
};



#endif
