#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class NoEffectSelfBuff;
class Shaman;
class WindfuryWeaponProc;

class WindfuryWeapon: public Spell, public TalentRequirer {
public:
    WindfuryWeapon(Shaman* pchar, const int spell_rank);
    ~WindfuryWeapon() override;

    Proc* get_proc() const;

private:
    NoEffectSelfBuff* buff;
    WindfuryWeaponProc* proc;

    void prepare_set_of_combat_iterations_spell_specific() override;
    void spell_effect() override;
    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
