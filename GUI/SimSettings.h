#ifndef SIMSETTINGS_H
#define SIMSETTINGS_H

#include <QSet>

enum SimOption {
    ScaleAgility,
    ScaleStrength,
    ScaleIntellect,
    ScaleHitChance,
    ScaleCritChance,
    ScaleMeleeAP,
    ScaleRangedAP,
    ScaleWeaponSkill
};

class SimSettings {
public:
    SimSettings();

    void set_combat_length(const int);
    void set_combat_iterations(const int);

    int get_combat_length() const;
    int get_combat_iterations() const;

    void add_sim_option(SimOption);
    void remove_sim_option(SimOption);
    bool option_active(SimOption) const;
    QSet<SimOption> get_active_options() const;

private:
    int combat_length;
    int combat_iterations;

    QSet<SimOption> sim_options;
};

#endif // SIMSETTINGS_H
