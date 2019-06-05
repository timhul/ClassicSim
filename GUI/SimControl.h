#ifndef SIMCONTROL_H
#define SIMCONTROL_H

#include "SimSettings.h"

class Character;
class NumberCruncher;
class RaidControl;

class SimControl {
public:
    SimControl(SimSettings* sim_settings, NumberCruncher* scaler);

    void run_quick_sim(QVector<Character*> raid, RaidControl* raid_control);
    void run_full_sim(QVector<Character*> raid, RaidControl* raid_control);

private:
    SimSettings* sim_settings;
    NumberCruncher* scaler;

    void add_option(Character*, SimOption::Name);
    void remove_option(Character*, SimOption::Name);
    void run_sim_with_option(QVector<Character*> raid, RaidControl* raid_control, SimOption::Name option, const int combat_length, const int iterations);

    void run_sim(QVector<Character*> raid, RaidControl* raid_control, const int combat_length, const int iterations);

    int thread_iterations(const int);

};

#endif // SIMCONTROL_H
