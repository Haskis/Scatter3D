#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glu.h>
#include <GL/glut.h>


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void paintRect(float *tab, int N=16);
    float *recTable;
signals:

public slots:

    void xChangeRangeLeft(QString newRange);
    void xChangeRangeRight(QString newRange);
    void yChangeRangeTop(QString newRange);
    void yChangeRangeBottom(QString newRange);
    void zChangeRangeNear(QString newRange);
    void zChangeRangeFar(QString newRange);

    void changeFrameSize(double newFrameSize);


protected:

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event );
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:

    int xRangeLeft;
    int xRangeRight;
    int yRangeTop;
    int yRangeBottom;
    int zRangeNear;
    int zRangeFar;

    bool rotatingState;
    int xMousePos;
    int yMousePos;
    int xRot;
    int yRot;
    int zRot;

    double frameSize;
};

#endif // GLWIDGET_H
