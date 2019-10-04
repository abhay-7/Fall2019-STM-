#ifndef SONOGRAM_STRUCTURE_H
#define SONOGRAM_STRUCTURE_H

#endif // SONOGRAM_STRUCTURE_H
#include <vector>


struct sonogram_raw{

    char sonogram_data[513];
};


struct sonogram_structure{
    int checksum;
    int angle;
    std::vector<int> intensities;
};
