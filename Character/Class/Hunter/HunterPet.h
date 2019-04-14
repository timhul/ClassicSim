#ifndef HUNTERPET_H
#define HUNTERPET_H

#include "Pet.h"

class FrenzyProc;
class Hunter;

class HunterPet: public Pet {
public:
    HunterPet(Hunter* pchar, const QString& name, double base_attack_speed, double base_dps);
    virtual ~HunterPet() override;

    FrenzyProc* get_frenzy_proc();
    void melee_critical_effect() override;

    unsigned get_resource_level() const override;

protected:
    class Focus* focus;
    FrenzyProc* frenzy_proc;
};

#endif // HUNTERPET_H
