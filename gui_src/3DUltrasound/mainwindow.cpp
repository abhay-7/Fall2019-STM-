#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <cstdio>

#define ARRAY_LEN 512

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


void MainWindow::on_actionOpen_triggered()
{
    FILE *fileIn;

    //Open dialog to read in the file
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");

    //Concert from Qt's nonsense to a normal FILE* setup
    QByteArray ba = filename.toLocal8Bit();
    const char *sonogram_data = ba.data();


    fileIn = fopen(sonogram_data, "rb");

}




void MainWindow::ProcessFile(FILE* fileIn)
{


    //vars for marker
    char marker[] = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";
    bool markerFound = false;
    char* markerStart;

    //vars for tracking reading and the input buffer
    size_t numRead = 0;
    long offset = 0;
    char buf[ARRAY_LEN + 1];

    //null terminate the buffer for ease of computation
    buf[ARRAY_LEN] = '\0';

    while (!markerFound)
{
        //read in bufLen bytes
        numRead = fread(buf, 1, ARRAY_LEN, fileIn);

        if (numRead != ARRAY_LEN) {
            //exit
            std::cerr << "failed fread at start" << std::endl;
            std::cerr << "numRead: " << numRead << std::endl;
            system(0);
        }

        //check for marker in the read string
        markerStart = strstr(buf, marker);

        //if marker found, set markerFound, fseek to start of marker
        if (markerStart) {
            markerFound = true;

            //calculate offset, move pointer back
            offset = -1 * strlen(markerStart);
            fseek(fileIn, offset, SEEK_CUR);
        }
    }






}
