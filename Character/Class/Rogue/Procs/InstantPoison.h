#ifndef INSTANTPOISON_H
#define INSTANTPOISON_H

#include "Enchant.h"
#include "Proc.h"
#include "TalentRequirer.h"

class Random;
class Rogue;

class InstantPoison: public Proc, public Enchant, public TalentRequirer {
public:
    InstantPoison(Character* pchar, const QString &weapon_side, const int weapon);
    ~InstantPoison() override;

    void perform_pre_combat() override;

private:
    friend class ImprovedPoisons;
    friend class VilePoisons;

    Buff* instant_poison_buff;
    Random* dmg_roll;
    Rogue* rogue;

    const unsigned base_proc_range;

    double vile_poisons;
    QVector<double> vile_poisons_modifiers;
    QVector<unsigned> improved_poisons_proc_range_increases;

    void proc_effect() override;
    void enable_spell_effect() override;
    void disable_spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // INSTANTPOISON_H
