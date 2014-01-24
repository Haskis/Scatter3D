#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    xRangeLeft(-50),
    xRangeRight(50),
    yRangeTop(-50),
    yRangeBottom(50),
    zRangeNear(-25),
    zRangeFar(50),
    frameSize(5),
    recTable(NULL)
{
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    xMousePos=event->x();
    yMousePos=event->y();
    rotatingState=true;
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    rotatingState=false;

}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    if(rotatingState){
         int dx = event->x()-xMousePos;
         int dy = event->y()-yMousePos;

         if (event->buttons() & Qt::RightButton) {
             xRot=xRot + dy*5;
             yRot=yRot + dx*5;
         } else if (event->buttons() & Qt::LeftButton) {
             xRot=xRot + dy*5;
             zRot=zRot + dx*5;
         yMousePos=event->y();
         xMousePos=event->x();
         this->update();
        }
    }
}
//[End] Rotation with moouse


//[Begin] Painting

void GLWidget::paintGL()
{
    //Czyszczenie tła
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //Macierz modelu załadowanie
    glMatrixMode(GL_MODELVIEW);

    //Macierz modelu załadowanie jednostkowej macierzy

    glLoadIdentity();


    //Obszar renderingu
    int side = qMin(width(), height());
    glViewport((width() - side) / 2, (height() - side) / 2, side, side);


    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);
    //glTranslatef(0,0,15);
    glColor3f(255,0,0);
    glBegin(GL_LINES);
        glVertex3f(-25,0,0);
        glVertex3f(25,0,0);
    glEnd();

    //glLoadIdentity();

    glColor3f(0,255,0);
    glBegin(GL_LINES);
        glVertex3f(0,-25,0);
        glVertex3f(0,25,0);
    glEnd();

    //glLoadIdentity();

    glColor3f(0,0,255);
    glBegin(GL_LINES);
        glVertex3f(0,0,-25);
        glVertex3f(0,0,25);
    glEnd();

    glColor3f(0,0,0.45);

      float forth[]= {0.9999948  ,  0.0025866  ,  0.0019076,   -0.1097966 ,
      -0.0025894   , 0.9999956 ,   0.0014247 ,  -2.8240167 ,
      -0.0019039   ,-0.0014296,    0.9999972  , 21.8448458 ,
      -0.0000000   , 0.0000000    ,0.0000000   , 1.0000000 ,};
    float tab[]={1,0,0,0,
                 0,1,0,0,
                 0,0,1,0,
                 0,0,0,1};



    if(recTable!=NULL)
        paintRect(recTable);

        //glutSolidSphere(2,10,10);



    glFlush();

    glMatrixMode( GL_PROJECTION );

    // macierz rzutowania = macierz jednostkowa
    glLoadIdentity();

    qDebug()<<"xrange"<<xRangeLeft;

    glOrtho(xRangeLeft,xRangeRight,yRangeTop,yRangeBottom,zRangeNear,zRangeFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

void GLWidget::initializeGL()
{
    glEnable( GL_DEPTH_TEST );
    //glEnable( GL_LIGHTING );
   // glEnable( GL_LIGHT0 );
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}
void GLWidget::xChangeRangeLeft(QString newRange){

    qDebug()<<newRange;
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
       xRangeLeft=temp;
    this->updateGL();this->update();
    //emit paintEvent(this->pa);

}

void GLWidget::xChangeRangeRight(QString newRange){
    qDebug()<<"Here";
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
        xRangeRight=temp;
    this->updateGL();this->update();


}
void GLWidget::yChangeRangeTop(QString newRange){
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
        yRangeTop=temp;
    updateGL();this->update();
}
void GLWidget::yChangeRangeBottom(QString newRange){
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
        yRangeBottom=temp;
    updateGL();this->update();
}
void GLWidget::zChangeRangeNear(QString newRange){
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
        zRangeNear=temp;
    updateGL();this->update();
}
void GLWidget::zChangeRangeFar(QString newRange){
    bool result= false;
    int temp=newRange.toInt(&result);
    if(result)
        zRangeFar=temp;
    updateGL();this->update();
}
void GLWidget::paintRect(float *tab, int N){

    glLoadIdentity();
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);


    glm::mat4 mat=glm::make_mat4(tab);
    mat=glm::transpose(mat);

    glMultMatrixf(glm::value_ptr(mat));

    glColor3f(255,255,0);
    glBegin(GL_POLYGON);
        glVertex3f(0,-1*frameSize,-1*frameSize);
        glVertex3f(0,-1*frameSize,frameSize);

        glVertex3f(0,-1*frameSize,frameSize);
        glVertex3f(0,frameSize,frameSize);

        glVertex3f(0,frameSize,frameSize);
        glVertex3f(0,frameSize,-1*frameSize);

        glVertex3f(0,frameSize,-1*frameSize);
        glVertex3f(0,-1*frameSize,-1*frameSize);

    glEnd();

}
void GLWidget::changeFrameSize(double newFrameSize){
    if(newFrameSize>0)
    frameSize=newFrameSize;
    updateGL();
}
