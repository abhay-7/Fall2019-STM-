#include <vector>
#include <stdlib.h>

/*
 * Function declarations:
 */
std::unique_ptr<tx_interval> create_tx_interval();
FILE* open_binary_file(char * raw_file_ptr);
std::vector<std::unique_ptr<tx_interval>> binary_file_to_sonogram_data(FILE* binary_file);


/* struct declarations */

struct tx_interval 
{
    double angle;
    std::vector<int> intensities;
};