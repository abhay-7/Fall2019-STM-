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

void SonogramData::set_raw_data(std::vector<sonogram_raw> raw)
{
    this->raw_data = raw;
}

//Gets a single angle at a specified index
double SonogramData::get_angle(unsigned int pos)
{
    //return this->data_to_render[pos].encoder_angle;
    return 0.0;
}



//Places all the ecnoder angles in a single list
std::vector<double> SonogramData::get_angles()
{
   std::vector<double> angles;
   for(unsigned int i = 0; i < this->data_to_render.size(); i++) //unsignd int stops a compiler warning
   {
       angles.push_back(get_angle(i));
   }

   return angles;
}


std::vector<int> SonogramData::get_single_intensities(unsigned int pos)
{
    std::vector<int> intensities;
    for (unsigned int i =0; i <  513; i++)
    {
        //intensities.push_back(this->data_to_render[pos].sonogram_intensities[i]);
    }

    return intensities;
}


//Places all the intensity values into a list of vectors of ints
//note O(n^2)
std::vector<std::vector<int>> SonogramData::get_all_intensities()
{
   std::vector<std::vector<int>> intensities;

   for(unsigned int i = 0; i < this->data_to_render.size(); i++) //unsignd int stops a compiler warning
   {
       intensities.push_back(get_single_intensities(i));
   }

   return intensities;
}

//Applies HASH on single element
bool SonogramData::get_check_sum(unsigned int pos)
{
    //Fille in logic after checksum format is finalized...

    return  true;
}



//Applies HASH on data and compares to stored checksum
std::vector<bool> SonogramData::get_check_sums()
{
    std::vector<bool> check_sums;
    for(unsigned int i = 0; i < this->data_to_render.size(); i++) //unsignd int stops a compiler warning
    {
        //Fill in logic later
        check_sums.push_back(get_check_sum(i));
    }

    return check_sums;
}


std::vector<sonogram_raw>  MainWindow::ProcessFile(FILE* fileIn)
{
    char marker[] = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";
    bool markerFound = false;
    char* markerStart;

    //vars for tracking reading and the input buffer
    size_t numRead = 0;
    long offset = 0;
    char buf[ARRAY_LEN + 1];

    //null terminate the buffer for ease of computation
    buf[ARRAY_LEN] = '\0';

    //find first set of 10 0xff (marker)
    while (!markerFound) {
        //read in bufLen bytes
        numRead = fread(buf, 1, ARRAY_LEN, fileIn);

        if (numRead != ARRAY_LEN) {
            //exit
            std::cerr << "failed fread at start" << std::endl;
            std::cerr << "numRead: " << numRead << std::endl;
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


    sonogram_raw data;

    //Now we will fill in the data structure
    std::vector<sonogram_raw> raw_data;


    while (fread(data.sonogram_data, ARRAY_LEN, 1, fileIn) == 1)
    {
       raw_data.push_back(data); //put in one sonogram structure at a time
    }


    return raw_data;

}



void MainWindow::on_open_file_triggered()
{
    FILE *fileIn;

    //Open dialog to read in the file
    QString filename = QFileDialog::getOpenFileName(this, tr("Open the file"), "~", tr("*.txt")); //Update this for out custom file extension (whatever that will be)

    //Concert from Qt's nonsense to a normal FILE* setup
    QByteArray ba = filename.toLocal8Bit();
    const char *sonogram_data = ba.data();
    fileIn = fopen(sonogram_data, "rb");


    //Put the FILE* into an easily parsable data structure
    this->sonogram_data_to_render = ProcessFile(fileIn);



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



void SonogramData::convertRawToStructure(std::vector<sonogram_raw> raw_data)
{
    std::vector<sonogram_structure> structured_data;

    char angle[3];
    char checksum[2];

    sonogram_structure temp;
    std::vector<int> intensities;

    for (unsigned int i = 0; i < raw_data.size(); i++)
    {
      for (unsigned int j = 0; j < 512; j++)
      {

          //WARNING THIS IS ALL SUBJECT TO CHANGE
          //I need to see exact data rep (some of this is guess work D: )

          if (j < 10)
          { //skip the marker
              continue;
          }

          if(j == 11 || j == 12)
          {
              angle[j - 11] = raw_data[i].sonogram_data[j];
          }

          else
          {
              intensities.push_back(raw_data[i].sonogram_data[j]);
          }

          //Check sum at the end? Not sure yet...
      }


      //Null terminate
      angle[2] = '\0';
      intensities[500] = '\0';

      short* short_ptr = (short *)angle;
      short angle = *short_ptr;

      temp.angle = angle;
      temp.intensities = intensities;
      temp.checksum = 0; //TODO
      structured_data.push_back(temp);
    }

    this->data_to_render = structured_data;
}


std::vector<sonogram_raw> SonogramData::getRawData(){

    return this->raw_data;
}




void MainWindow::on_pushButton_clicked()
{
    if(this->sonogram_data_to_render.size() < 2)
    {


        QMessageBox msgBox;
        msgBox.setText("Warning! Please load a file before rendering");
        msgBox.exec();
    }

    else
    {

        SonogramData *render = new SonogramData();
        render->set_raw_data(this->sonogram_data_to_render);

        render->convertRawToStructure(render->getRawData());

        //Now we have the data in clean format.

        //Inlcude render code here
        // Assuming render is the array of sonogram structure that I get
        pair <int,vector<int>> b; // pair storing at first index the angle, and at second index the array of intensities at 0.1 cm difference
        int ang=0;
        int n=0;
        for (int i=0;i<render.size();i++){
            ang = render[i]->angle;
            b.first=ang;
            n=(render[i]->intensities).size();
            for (int j=0;j<n;j++){
            if(j%2) {
            b.second.push_back(render[i]->intensities[j]+render[i]->intensities[j-1]);
            }
            }
        }
    }

}
