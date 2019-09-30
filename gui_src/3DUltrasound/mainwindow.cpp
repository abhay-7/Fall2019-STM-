#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <cstdio>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define TEX_HEIGHT 700
#define TEX_WIDTH 700

#define ARRAY_LEN 512

#define ENCODER_RES 4096
#define NUM_DATA_POINTS 500
#define MARKER_LEN 10
#define OVERHEAD_LEN 12


//define constant for length of rays
#define RAY_LEN 500


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

SonogramData::SonogramData()
{

}
SonogramData::~SonogramData()
{
}


std::vector<sonogram_structure> SonogramData::get_data_to_render()
{
    return this->data_to_render;
}

void SonogramData::set_data_to_render(std::vector<sonogram_structure> data)
{
    this->data_to_render = data;
}


//Places all the ecnoder angles in a single list
std::vector<double> SonogramData::get_angles()
{
   std::vector<double> angles;
   for(unsigned int i = 0; i < this->data_to_render.size(); i++) //unsignd int stops a compiler warning
   {
       angles.push_back(this->data_to_render[i].encoder_angle);
   }

   return angles;
}


//Places all the intensity values into a list of vectors of ints
std::vector<std::vector<int>> SonogramData::get_intensities()
{
   std::vector<std::vector<int>> intensities;

   for(unsigned int i = 0; i < this->data_to_render.size(); i++) //unsignd int stops a compiler warning
   {
       std::vector<int> char_to_int;
       for (int j = 0; j < 513; j++)
       {
           char_to_int.push_back(this->data_to_render[i].sonogram_intensities[j]);
       }

       intensities.push_back(char_to_int);
   }

   return intensities;
}


//Most of this is just a re-implemantation of Fuming's code (Summer 2019 on the Github)
void MainWindow::ProcessFile(FILE* fileIn)
{

}

void MainWindow::on_open_file_triggered()
{
    FILE *fileIn;

    //Open dialog to read in the file
    QString filename = QFileDialog::getOpenFileName(this, tr("Open the file"), "/~/Desktop", tr("*.txt")); //Update this for out custom file extension (whatever that will be)

    //Concert from Qt's nonsense to a normal FILE* setup
    QByteArray ba = filename.toLocal8Bit();
    const char *sonogram_data = ba.data();
    fileIn = fopen(sonogram_data, "rb");

    //SIGNAL PROCESSING CODE WILL GO HERE:

    //ProcessSignal(fileIn)

    //Put the FILE* into an easily parsable data structure
   // ProcessFile(fileIn);

    //SongramData is a Data strucute that should make the rendering team's life a bit easier...
    SonogramData rendering_data;
    std::vector<sonogram_structure> data_to_render = this->sonogram_data_to_render;
    rendering_data.set_data_to_render(data_to_render);
}


//opens link to Organizaiton page on Github
void MainWindow::on_actionGithub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/ColumbiaOpenSourceUltrasound", QUrl::TolerantMode));
}


//Opens up an email client with Yazmin as the address
void MainWindow::on_actionContact_triggered()
{
    QDesktopServices::openUrl(QUrl("mailto:yf2233@columbia.edu?subject=Help Regarding Ultrasound Software&body=Please inlude a brief summary of issue. If this issue is a bug, please inlcude a way to reproduce the error if possible.", QUrl::TolerantMode));
}
