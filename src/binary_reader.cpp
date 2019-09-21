#include <iostream>
#include <vector>
#include <stdlib.h> 


struct tx_interval 
{
    double angle;
    std::vector<int> intensities;
};

tx_interval* create_tx_interval();
FILE* open_binary_file(char * raw_file_ptr);
std::vector<tx_interval*>* binary_file_to_sonogram_data(FILE* binary_file);


std::vector<int> intensity_values(char* char_intensities)
{
    std::vector<int> intensities;
    char* p = char_intensities;
    while (p != nullptr)
    {
        intensities.push_back(*p);
        p++;
    }
    return intensities;
}

FILE* open_binary_file(char * raw_file_ptr){
    FILE* binary_file;
    binary_file = fopen(raw_file_ptr,"rb");
    return binary_file;
}


std::vector<tx_interval*>* binary_file_to_sonogram_data(FILE* binary_file)
{
    std::vector<tx_interval*>* scans = new std::vector<tx_interval*>();
    if (binary_file == NULL) perror ("Error opening sonogram binary data file");

    else
    {
        while (!feof(binary_file))
        {
            auto sonogram_data = create_tx_interval();
            char tx[10];
            char angle[2];
            char intensities[500];
            fgets(tx, 11, binary_file);
            fgets(angle, 3, binary_file);
            fgets(intensities, 501, binary_file);
            sonogram_data->angle = atof(angle); /* Standard Lib  char* to double */
            sonogram_data->intensities = intensity_values(intensities); /* in house formatting */
            scans->push_back(sonogram_data);
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