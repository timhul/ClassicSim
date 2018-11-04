#ifndef SIMCONTROL_H
#define SIMCONTROL_H

#include "SimSettings.h"

class Character;
class NumberCruncher;

class SimControl {
public:
    SimControl(SimSettings* sim_settings, NumberCruncher* scaler);

    void run_quick_sim(Character*);
    void run_full_sim(Character*);

private:
    SimSettings* sim_settings;
    NumberCruncher* scaler;

    void add_option(Character*, SimOption::Name);
    void remove_option(Character*, SimOption::Name);
    void run_sim_with_option(Character*, SimOption::Name, const int combat_length, const int iterations);

    void run_sim(Character*, const int combat_length, const int iterations);

    int thread_iterations(const int);

};

#endif // SIMCONTROL_H
