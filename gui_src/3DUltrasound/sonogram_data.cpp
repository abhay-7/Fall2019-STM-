#include <vector>
#include "mainwindow.h"

//We use implicit construcots for now...

std::vector<sonogram_structure> SonogramData::get_data_to_render(MainWindow idempotent)
{
    return idempotent.sonogram_data_to_render;
}
