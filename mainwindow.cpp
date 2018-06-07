#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    db=new db4Makesi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->textEdit->clear();
    if(arg1==QString(""))
        return;
    qDebug()<<arg1;
    QStringList tmp=db->search(arg1);
    for(int i=0;i<tmp.count();i++)
    {
        ui->textEdit->append(tmp.at(i));
    }
}
