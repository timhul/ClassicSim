#ifndef RAPIDFIRE_H
#define RAPIDFIRE_H

#include "Spell.h"
#include "SetBonusRequirer.h"

class RapidFireBuff;

class RapidFire: public Spell, public SetBonusRequirer {
public:
    RapidFire(Character *pchar);
    ~RapidFire() override;

    RapidFireBuff* get_rapid_fire_buff() const;

private:
    RapidFireBuff* rapid_fire;

    void spell_effect() override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // RAPIDFIRE_H
