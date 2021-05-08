#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "distinctcolorgenerator.h"

#include <QtDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto colors = DistinctColorGenerator::genUniqueColors(20);
    for(uint i = 0; i < colors.size(); ++i) {
        auto label = new QLabel();
        ui->verticalLayout->addWidget(label);
        auto color =  QString("QLabel{background-color: rgb(%1, %2, %3);}")
                 .arg(colors[i][0]).arg(colors[i][1]).arg(colors[i][2]);
        label->setStyleSheet(color);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

