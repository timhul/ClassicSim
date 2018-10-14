#ifndef SIMSETTINGS_H
#define SIMSETTINGS_H

#include <QSet>

enum SimOption {
    NoScale = -1,
    ScaleAgility,
    ScaleStrength,
    ScaleHitChance,
    ScaleCritChance,
    ScaleMeleeAP,
    ScaleWeaponSkill
};

class SimSettings {
public:
    SimSettings();

    void set_combat_length(const int);
    void set_combat_iterations(const int);

    int get_combat_length() const;
    int get_combat_iterations() const;

    int get_num_threads_current() const;
    int get_num_threads_max() const;
    void set_num_threads(const int);

    void add_sim_option(SimOption);
    void remove_sim_option(SimOption);
    bool option_active(SimOption) const;
    QSet<SimOption> get_active_options() const;

private:
    int combat_length;
    int combat_iterations;
    int num_threads;

    QSet<SimOption> sim_options;
};

#endif // SIMSETTINGS_H
