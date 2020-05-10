#pragma once

#include "Enchant.h"
#include "Proc.h"
#include "SetBonusRequirer.h"
#include "TalentRequirer.h"

class Random;
class Rogue;

class InstantPoison : public Proc, public Enchant, public TalentRequirer, public SetBonusRequirer {
public:
    InstantPoison(Rogue* rogue, EnchantInfo* enchant_info, const QString& weapon_side, const int weapon);
    ~InstantPoison() override;

    void perform_start_of_combat() override;

private:
    Buff* instant_poison_buff;
    Random* dmg_roll;
    Rogue* rogue;

    double vile_poisons;
    QVector<double> vile_poisons_modifiers;
    unsigned improved_poisons_increase;

    void proc_effect() override;
    void enable_spell_effect() override;
    void disable_spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};
