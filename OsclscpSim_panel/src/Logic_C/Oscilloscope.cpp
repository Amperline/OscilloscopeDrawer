#include "Oscilloscope.h"
#include <iostream>
#include <fstream>
#include <sstream>

typedef Oscilloscope osc;

osc::Oscilloscope(int height, int width, std::vector<double> signal_arr)
{
    this->height = height;
    this->width = width;

    this->s_arr = signal_arr;

    
}

std::vector<double> osc::collect_Signal_Data(std::string path_to_Signal)
{
    using namespace std;

    vector<double> temp_arr;
    ifstream out(path_to_Signal);

    while(out)
    {
        string to_string;
        stringstream t_signal;
        double t_value;

        out >> to_string;
        t_signal << to_string;
        t_signal >> t_value;

        temp_arr.push_back(t_value);
    }
    
    return temp_arr;
}
