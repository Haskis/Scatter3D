#ifndef SCATTERWINDOW_H
#define SCATTERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLayout>
#include <QPushButton>
#include <QGLWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <glwidget.h>
#include <glm/glm.hpp>
#include <QDoubleSpinBox>
#include <QFile>
#include <QDebug>
class ScatterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ScatterWindow(QWidget *parent = 0);



signals:

private slots:
    void connectUiSignalsToSlots();

    void changeFrameIndex(double newIndexx);
    void loadDataButtonClicked();
public slots:

private:

    bool readDataFromFile(QString fileName);
    QLineEdit **viewParameters;
    QLabel **viewParametersDescription;
    QHBoxLayout **layoutsSeparateParameters;
    QGridLayout *layoutParameters;
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightBar;

    QDoubleSpinBox *frameSizeSpinBox;
    QLabel *frameSizeLabel;
    QDoubleSpinBox *frameIndexSpinBox;
    QLabel *frameIndexLabel;

    QLineEdit *dataFileUrl;
    QPushButton *buttonLoadData;

    int frameIndex;
    float *dataRect;
    QList<QList<float> >myPoints;

public:
    GLWidget *myGLWidget;
protected:

};
#endif // SCATTERWINDOW_H
