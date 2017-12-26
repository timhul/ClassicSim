#ifndef STATS_H
#define STATS_H

#include "Race.h"

class Stats {
public:
    Stats(Race* race);

    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();
protected:
private:
    Race* race;
    int STR;
    int AGI;
    int STAM;
    int INT;
    int SPI;
    int melee_ap;
    int ranged_ap;
    float percent_hit;
    float percent_crit;
};

#endif // STATS_H
