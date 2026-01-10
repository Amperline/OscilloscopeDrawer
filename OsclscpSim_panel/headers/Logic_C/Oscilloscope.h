#ifndef OSCILLOSCOPE
#define OSCILLOSCOPE

#include <vector>
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

class Oscilloscope {
    // Режими

    // Normal
    // чекає тригер

    // Auto
    // якщо тригера нема — все одно малює

    // Single
    // один раз спрацював → стоп

    // Roll
    // повільна розгортка (як самописець)

    //РОЗГОРТКА
    //time required for beam to go through 
    sf::Time* time_per_Div;

    //s_ - recieved ouy where
    //m_ - class-related(standart test)
    double* time_scale;     // мс/діл

    //Y = (Vin − Vref) / (VoltsPerDiv)
    //Reference Voltage (Vref)(опорна напруга, 0 В в центрі екрану)
    double* voltage_scale;  // В/діл

    double trigger_level;  // рівень тригера
    bool trigger_rising;   // true = по наростаючому фронту

    unsigned int s_frequency;
    // array recieved from simulation
    //starts with frequency(first value)
    std::vector<double> s_arr;
    // embeded standart array for tests;
    std::array<double, 100> m_arr;

    // Trigger Mode

    // Auto
    // якщо нема фронту → запускається сам

    // Normal
    // без фронту нічого не малює

    // Single
    // один раз і стоп

    int H_offset_in_percents = 0;
    int V_offset_in_percents = 0;

    int height;
    int width;

public:

Oscilloscope(int height, int width, std::vector<double> signal_arr);
~Oscilloscope();

std::vector<double> collect_Signal_Data(std::string path_to_Signal);

};


#endif