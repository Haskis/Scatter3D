#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    myScatterWindow = new ScatterWindow();
    this->setCentralWidget(myScatterWindow);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

}

MainWindow::~MainWindow()
{
    delete ui;;
}
