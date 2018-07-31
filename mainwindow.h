#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QString"

#include <string>                                                           // Kniznica pre string
#include <iostream>                                                         // Kniznica pre IO operacie
#include <fstream>                                                          // Kniznica pre pracu s subormi
#include <cstring>
#include <cstdlib>
#include <sstream>

#include "help.h"

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
    void on_databaza_clicked();

    void on_titulky_clicked();

    void on_start_clicked();

    void on_exit_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString d_file,s_file,o_file;
    std::ofstream ouFile;
    std::ifstream inFile;
    char znaky[500][4];
    int d_array_size;


};

#endif // MAINWINDOW_H
