#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db4makesi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    db4Makesi *db;
};

#endif // MAINWINDOW_H
