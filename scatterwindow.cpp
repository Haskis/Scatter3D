#include "scatterwindow.h"
ScatterWindow::ScatterWindow(QWidget *parent) :
    QWidget(parent),
    dataRect(new float[16])

{

    //[Begin] UI
    viewParameters = new QLineEdit *[6]();
    viewParametersDescription = new QLabel *[6]();
    layoutsSeparateParameters = new QHBoxLayout *[6]();

    frameSizeSpinBox = new QDoubleSpinBox;
    frameSizeSpinBox->setValue(5);
    frameSizeLabel = new QLabel;
    frameSizeLabel->setText("Frame Size");

    frameIndexSpinBox = new QDoubleSpinBox;
    frameIndexSpinBox->setValue(1);
    frameIndexSpinBox->setMaximum(2000);
    frameIndexLabel= new QLabel;
    frameIndexLabel->setText("Frame Index");

    dataFileUrl = new QLineEdit();
    buttonLoadData = new QPushButton();

    myGLWidget = new GLWidget();
    myGLWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    myGLWidget->show();

    for(int i=0;i<6;i++){
        viewParameters[i]=new QLineEdit();
        viewParametersDescription[i]=new QLabel();
        layoutsSeparateParameters[i]=new QHBoxLayout();
        viewParameters[i]->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    }

    layoutParameters = new QGridLayout();

    viewParametersDescription[0]->setText("xLeft");
    viewParameters[0]->setText("-50");
    viewParametersDescription[1]->setText("xRight");
    viewParameters[1]->setText("50");
    viewParametersDescription[2]->setText("yTop");
    viewParameters[2]->setText("-50");
    viewParametersDescription[3]->setText("yBottom");
    viewParameters[3]->setText("50");
    viewParametersDescription[4]->setText("zNear");
    viewParameters[4]->setText("-15");
    viewParametersDescription[5]->setText("zFar");
    viewParameters[5]->setText("50");

    for(int i=0;i<6;i++){
        layoutParameters->addWidget(viewParametersDescription[i],i,1);
        layoutParameters->addWidget(viewParameters[i],i,2);
    }
    layoutParameters->addWidget(frameSizeLabel,6,0);
    layoutParameters->addWidget(frameSizeSpinBox,6,1);
    layoutParameters->addWidget(frameIndexLabel,7,0);
    layoutParameters->addWidget(frameIndexSpinBox,7,1);

    mainLayout = new QHBoxLayout();
    rightBar = new QVBoxLayout();
    rightBar->addLayout(layoutParameters);

    mainLayout->addWidget(myGLWidget);
    mainLayout->addLayout(rightBar);
    rightBar->addWidget(dataFileUrl);
    rightBar->addWidget(buttonLoadData);
    setLayout(mainLayout);
    connectUiSignalsToSlots();
}
void ScatterWindow::connectUiSignalsToSlots(){

    connect(this->viewParameters[0],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(xChangeRangeLeft(QString)));
    connect(this->viewParameters[1],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(xChangeRangeRight(QString)));
    connect(this->viewParameters[2],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(yChangeRangeTop(QString)));
    connect(this->viewParameters[3],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(yChangeRangeBottom(QString)));
    connect(this->viewParameters[4],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(zChangeRangeNear(QString)));
    connect(this->viewParameters[5],SIGNAL(textChanged(QString)),this->myGLWidget,SLOT(zChangeRangeFar(QString)));

    connect(this->frameSizeSpinBox,SIGNAL(valueChanged(double)),this->myGLWidget,SLOT(changeFrameSize(double)));
    connect(this->buttonLoadData,SIGNAL(clicked()),this,SLOT(loadDataButtonClicked()));
    connect(this->frameIndexSpinBox,SIGNAL(valueChanged(double)),this,SLOT(changeFrameIndex(double)));
}

void ScatterWindow::changeFrameIndex(double newIndexx){
    qDebug()<<"Size"<<myPoints.size();
    int newIndex = newIndexx;
    if(newIndex>=0 && newIndex<myPoints.size()){

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++){
                dataRect[j+4*i]=myPoints.at(newIndex).at(j+4*i);
            }

        myGLWidget->recTable=dataRect;
        myGLWidget->updateGL();
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++){
                qDebug()<<dataRect[j+4*i];
            }

    }

}

bool ScatterWindow::readDataFromFile(QString fileName){

    QFile inputFile(fileName);
    if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    while(!inputFile.atEnd())
    {
        QList<float> Point;
        for(int i=0; i<4; i++){
            if(inputFile.atEnd())
                break;

            QString line = inputFile.readLine();
            QStringList lineList = line.split(" ");

            float x = 0.0;
            float y = 0.0;
            float z = 0.0;
            float k = 0.0;

            if(lineList.size() == 4){
                x = lineList.at(0).toFloat();
                y = lineList.at(1).toFloat();
                z = lineList.at(2).toFloat();
                k = lineList.at(3).toFloat();
            }
            else{
                qDebug()<<"Bad format (Try (x y z k))";
                return false;
            }

            Point.push_back(x);
            Point.push_back(y);
            Point.push_back(z);
            Point.push_back(k);
            qDebug()<<x<<y<<z<<k<<endl;
            if(i==3){
                myPoints.push_back(Point);
            }
        }
    }
}

void ScatterWindow::loadDataButtonClicked(){
    myGLWidget->recTable=NULL;
    myPoints.clear();
    readDataFromFile(this->dataFileUrl->text());
}
