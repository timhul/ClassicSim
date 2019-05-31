#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Shaman;

class WindfuryWeaponProc: public Proc, public TalentRequirer {
public:
    WindfuryWeaponProc(Shaman* pchar, const int spell_rank);

private:
    friend class WindfuryWeapon;

    void proc_effect() override;

    unsigned bonus_melee_ap;
    unsigned base_bonus_melee_ap;

    void prepare_set_of_combat_iterations_spell_specific() override;
    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
