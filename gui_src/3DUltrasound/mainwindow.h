#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
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
   // void file_open_triggered();

    void open_file_triggered();

    void on_open_file_triggered();

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
    //Consider this section of the Class to eb the "API" for rendering


    //Returns the raw vector of sonogram data.
    //Each entry contains the struct sonogram_sturcture (see sonogram_structure.h)
    std::vector<sonogram_structure> get_data_to_render();

    //Returns all the encoder angles in a vector
    std::vector<double> get_angles();

    //Returns all the intensity values in a vector of vectors
    std::vector<std::vector<int>> get_intensities();

    //More to come...



    //Mechanics :

    void set_data_to_render(std::vector<sonogram_structure>);
    SonogramData();
    ~SonogramData();



private:
    std::vector<sonogram_structure> data_to_render;
    int length; //length of sonogram data
    double firstTimeStamp;
    double firstAngle;
};









#endif // MAINWINDOW_H
