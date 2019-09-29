#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <cstdio>
#include <iostream>
#include <vector>
#include "sonogram_structure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    void ProcessFile(FILE* fileIN);
    int FindFirstMarker(char* c, long x, char [], FILE *fileIn);
    std::vector<sonogram_structure> sonogram_data_to_render;

    friend class SonogramData; //allows  SonogramData class to access this private variable

};



class SonogramData
{
public:
    std::vector<sonogram_structure> get_data_to_render(MainWindow idempotent);
private:

    int length; //length of sonogram data
    double firstTimeStamp;
    double firstAngle;
};









#endif // MAINWINDOW_H
