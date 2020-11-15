#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(750,600);
    mychart=new myChart();
    mychart->leftTopPoint=QPoint(50,50);
    mychart->initData();
    ui->label->move(50,400);
    ui->label_2->move(50,430);
    ui->label_3->move(50,460);
    ui->lineEdit->move(110,400);
    ui->lineEdit_2->move(110,430);
    ui->lineEdit_3->move(110,460);
    ui->pushButton->move(230,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    mychart->drawChart(painter);
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().trimmed().isEmpty()){
        mychart->maxData=800;
    }else{
        mychart->maxData=ui->lineEdit->text().trimmed().toDouble();
    }
    if(ui->lineEdit_2->text().trimmed().isEmpty()){
        mychart->minData=200;
    }else{
        mychart->minData=ui->lineEdit_2->text().trimmed().toDouble();
    }
    if(ui->lineEdit_3->text().trimmed().isEmpty()){
        mychart->numData=1000;
    }else{
        mychart->numData=ui->lineEdit_3->text().trimmed().toInt();
    }

    mychart->initData();
    this->repaint();
}
