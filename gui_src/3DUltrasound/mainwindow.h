#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopServices>
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

//slots are specials functions that deal with events
//in Qt lingo, events like a mouse click, or scroll, are called "signals"
//Every signal has a corresponding slot (function)
private slots:

    void on_open_file_triggered();

    void on_actionGithub_triggered();

    void on_actionContact_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<sonogram_raw>  ProcessFile(FILE* fileIN);
    int FindFirstMarker(char* c, long x, char [], FILE *fileIn);
    std::vector<sonogram_raw> sonogram_data_to_render;

    friend class SonogramData; //allows  SonogramData class to access this private variable

};



class SonogramData
{
public:
    //Consider this section of the Class to be the "API" for rendering


    //Returns the raw vector of sonogram data.
    //Each entry contains the struct sonogram_sturcture (see sonogram_structure.h)
    std::vector<sonogram_structure> get_data_to_render();

    //Returns all the encoder angles in a vector
    std::vector<double> get_angles();

    //Gets a single encoder angle at a specified position
    double get_angle(unsigned int pos);


    std::vector<int> get_single_intensities(unsigned int pos);

    //Returns all the intensity values in a vector of vectors
    std::vector<std::vector<int>> get_all_intensities();


    bool get_check_sum(unsigned int pos);
    std::vector<bool> get_check_sums();

    //More to come...

    //Mechanics :

    void set_data_to_render(std::vector<sonogram_structure>);
    void set_raw_data(std::vector<sonogram_raw>);
    void convertRawToStructure(std::vector<sonogram_raw> raw_data);
    std::vector<sonogram_raw> getRawData();
    SonogramData();
    ~SonogramData();

private:
    std::vector<sonogram_raw> raw_data;
    std::vector<sonogram_structure> data_to_render;
    int length; //length of sonogram data
    double firstTimeStamp;
    double firstAngle;
};









#endif // MAINWINDOW_H
