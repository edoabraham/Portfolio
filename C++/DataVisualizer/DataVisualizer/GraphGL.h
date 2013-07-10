/// GraphGL.h - GraphGL Template Class Implementation
/// Written By Jesse Z. Zhong
#ifndef __GRAPH_GL_H__
#define __GRAPH_GL_H__
#include "stdafx.h"
#include <QWidget>
#include <QGLWidget>
#include <QtOpenGL>
#include <math.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

using namespace std;

/// Dictates the amount, in degrees, that the camera can
/// be rotated around a target; alternatively, it is the
/// amount at which the world rotates before the camera
const int ROTATION_INCREMENT = 16;

/// Allows for plots to be rendered in a 3D space
/// using OpenGL, within a QWidget window
class GraphGL : public QGLWidget {
    
    Q_OBJECT
    
public:
    /// Constructor
    /// Initializes with a possible parent widget
    GraphGL(QWidget *parent = 0)
        : QGLWidget(QGLFormat(QGL::StencilBuffer), parent) {
        
            XRotation_ = 0;
            YRotation_ = 0;
            ZRotation_ = 0;
            
            PointColor_ = QColor::fromRgb(255, 255, 255);
            BGColor_ = QColor::fromRgb(0, 0, 0);
            
            CurrentIndex_ = 0;
    }
    ~GraphGL() {
        
    }
    
    QSize MinimumSizeHint() const {
        return QSize(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    QSize SizeHint() const {
        return QSize(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    
    /// Makes reservations on the capacity of the lists
    void Reserve(int size) {
        if(size < 0)
            throw "GraphGL::Reserve(int size) : Reservation size cannot fall below 0";
        X_.reserve(size);
        Y_.reserve(size);
        Z_.reserve(size);
        Colors_.reserve(size);
    }
    
    /// Method used to load in one set of points
    void LoadPoints(const vector<float>& x, const vector<float>& y,
                    const vector<float>& z, const vector<QColor> colors) {
        
        unsigned int xSize = x.size();
        
        // Checks if they are identical in size first
        if((xSize == y.size()) && (xSize == z.size())
           && (xSize == colors.size())) {
            X_.push_back(x);
            Y_.push_back(y);
            Z_.push_back(z);
            Colors_.push_back(colors);
        }
    }
    
    /// Changes the index for a set of points to be drawn
    void Refresh(int index) {
        assert((X_.size() == Y_.size()) && (X_.size() == Z_.size()));
        
        if(!X_.empty() && (index >= 0) && ((unsigned)index < X_.size()))
            CurrentIndex_ = index;
        
        updateGL();
    }
    
public slots:
    /// Methods for changing the angle of
    /// the camera with respect to the origin
    void SetXRotation(int angle) {
        NormalizeAngle(angle);
        if(angle != XRotation_) {
            XRotation_ = angle;
            emit XRotationChanged(angle);
            updateGL();
        }
    }
    void SetYRotation(int angle) {
        NormalizeAngle(angle);
        if(angle != YRotation_) {
            YRotation_ = angle;
            emit YRotationChanged(angle);
            updateGL();
        }
    }
    void SetZRotation(int angle) {
        NormalizeAngle(angle);
        if(angle != ZRotation_) {
            ZRotation_ = angle;
            emit ZRotationChanged(angle);
            updateGL();
        }
    }
    
signals:
    /// Detects changes to the rotation
    void XRotationChanged(int angle);
    void YRotationChanged(int angle);
    void ZRotationChanged(int angle);
    
protected:
    /// Initializes OpenGL
    void initializeGL() {
        qglClearColor(BGColor_);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_MULTISAMPLE);
        static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        
        // Enables vertices to be drawn with different colors
        glEnable(GL_COLOR_MATERIAL);
        
        // Blending Options
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    /// In charge of rendering the scene per frame
    void paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -10.0);
        glRotatef(XRotation_ / ROTATION_INCREMENT, 1.0, 0.0, 0.0);
        glRotatef(YRotation_ / ROTATION_INCREMENT, 0.0, 1.0, 0.0);
        glRotatef(ZRotation_ / ROTATION_INCREMENT, 0.0, 0.0, 1.0);
        
        DrawPoints(CurrentIndex_);
    }
    
    /// Resizes the viewport
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
    
    /// Draws a set of points using the provided index
    void DrawPoints(int index) {
        if(!X_.empty() && (index >= 0) && ((unsigned)index < X_.size())) {
            for(int i = 0, j = X_[index].size(); i < j; i++) {
                DrawPoint(X_[index][i], Y_[index][i], Z_[index][i], Colors_[index][i]);
            }
        }
    }

    /// Rotation angles
    int XRotation_;
    int YRotation_;
    int ZRotation_;
    
    QPoint LastPoint_;
    QColor BGColor_;
    QColor PointColor_;
    
    int CurrentIndex_;
    
    /// Points lists
    vector<vector<float> > X_;
    vector<vector<float> > Y_;
    vector<vector<float> > Z_;
    vector<vector<QColor> > Colors_;
    
    /// Reference to the list of points
    
    
private:
    void NormalizeAngle(int& angle) {
        while (angle < 0)
            angle += 360 * ROTATION_INCREMENT;
        while (angle > (360 * ROTATION_INCREMENT))
            angle -= 360 * ROTATION_INCREMENT;
    }
    
    /// Draws a single point in a given color
    void DrawPoint(const float& x, const float& y,
                   const float& z, const QColor& color) {
        qglColor(color);
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();
    }
};



#endif
