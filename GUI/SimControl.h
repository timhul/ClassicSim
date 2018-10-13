#ifndef SIMCONTROL_H
#define SIMCONTROL_H

class Character;
class SimSettings;

class SimControl {
public:
    SimControl(SimSettings* sim_settings);

    void run_sim(Character*);

private:
    SimSettings* sim_settings;
};

#endif // SIMCONTROL_H
