#ifndef DRUID_H
#define DRUID_H

#include "Class.h"

class Druid: public Class {
public:
    Druid(Race* race, Stats* stats, Engine* engine) : Class(race, stats, engine) {}

    std::string get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() const override;
    float global_cooldown() const override;

protected:
private:
};

#endif // DRUID_H
