#include <iostream>
#include <vector>
#include <stdlib.h> 


struct tx_interval 
{
    double angle;
    std::vector<unsigned short> intensities;
};

tx_interval* create_tx_interval();
FILE* open_binary_file(char * raw_file_ptr);
std::vector<tx_interval*> binary_file_to_sonogram_data(FILE* binary_file);


std::vector<unsigned short> intensity_values(char* char_intensities)
{
    std::vector<unsigned short> intensities;
    unsigned short* p = (unsigned short *)char_intensities;
    int limit = 20;
    int counter = 0;
    while (counter < limit)
    {
        std::cout << "intensity values: " << (unsigned short)*p << " counter: " << counter << std::endl;
        intensities.push_back(*p);
        p = p + 1;
        counter++;
    }
    return intensities;
}

FILE* open_binary_file(char * raw_file_ptr){
    FILE* binary_file;
    binary_file = fopen(raw_file_ptr,"rb");
    return binary_file;
}


std::vector<tx_interval*> binary_file_to_sonogram_data(FILE* binary_file)
{
    std::vector<tx_interval*> scans;
    if (binary_file == NULL) perror ("Error opening sonogram binary data file");

    else
    {
        while (!feof(binary_file))
        {
            
            auto sonogram_data = create_tx_interval();
            char tx[11];
            char angle[3];
            char intensities[501];
            
            fgets(tx, 11, binary_file);

            if (feof(binary_file))
            {
                break;
            }

            fgets(angle, 3, binary_file);

            if (feof(binary_file))
            {
                break;
            }

            fgets(intensities, 501, binary_file);
            if (feof(binary_file))
            {
                break;
            }
            angle[2] = '\0';

            sonogram_data->angle = atof(angle); /* Standard Lib  char* to double */
            sonogram_data->intensities = intensity_values(intensities); /* in house formatting */

            std::cout << "This is the angle" << atof(angle) << std::endl;
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