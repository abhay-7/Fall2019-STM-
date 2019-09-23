#include <iostream>
#include <vector>
#include <stdlib.h> 

#define TX_SIZE 11
#define ANGLE_SIZE 3
#define INTENSITY_SIZE 501



struct tx_interval 
{
    double angle;
    std::vector<unsigned short> intensities;
};

tx_interval* create_tx_interval();
FILE* open_binary_file(char * raw_file_ptr);
std::vector<tx_interval*> binary_file_to_sonogram_data(FILE* binary_file);
void free_tx_interval(std::vector<tx_interval*> scans);

std::vector<unsigned short> intensity_values(char* char_intensities)
{
    std::vector<unsigned short> intensities;
    char* p = char_intensities;
    int limit = 500;
    int counter = 0;
    while (counter < limit)
    {
        //std::cout << "intensity values: " << (int)*p << " counter: " << counter << std::endl;
        intensities.push_back((unsigned short)*p);
        p = p + 1;
        counter++;
    }
    return intensities;
}


/* 
takes a raw pointer and makes it into a FILE pointer.
Also opens to read a binary file 
*/

FILE* open_binary_file(char * raw_file_ptr)
{
    FILE* binary_file;
    binary_file = fopen(raw_file_ptr,"rb");

    return binary_file;
}


std::vector<tx_interval*> binary_file_to_sonogram_data(FILE* binary_file)
{
    std::vector<tx_interval*> scans;
    if (binary_file == NULL)
    {
        perror ("Error opening sonogram binary data file");
    }

    else
    {
        while (!feof(binary_file))
        {
            auto sonogram_data = create_tx_interval();
            char tx[TX_SIZE];
            char angle[ANGLE_SIZE];
            char intensities[INTENSITY_SIZE];
            
            fgets(tx, TX_SIZE, binary_file);

            if (feof(binary_file))
            {
                break;
            }

            fgets(angle, ANGLE_SIZE, binary_file);

            if (feof(binary_file))
            {
                break;
            }

            fgets(intensities, INTENSITY_SIZE, binary_file);
            if (feof(binary_file))
            {
                break;
            }
         
            char* p = (char *)angle;
            p = p + 1;
            angle[2] = '\0';

            sonogram_data->angle = (int)*p; /* Standard Lib char* to double */
            sonogram_data->intensities = intensity_values(intensities); /* in house formatting */

            //std::cout << "This is the angle" << (int)*p << std::endl;
            scans.push_back(sonogram_data);
        }
    } 

    fclose (binary_file);
    return scans;
}


//Same format at server.cpp for compatibility sake
tx_interval* create_tx_interval()
{
    tx_interval* sonogram_data(new tx_interval());
    return sonogram_data;
}

//frees the tx interval scans
void free_tx_interval(std::vector<tx_interval*> scans)
{
    for (auto& x: scans)
    {
        free(x);
    }
}
