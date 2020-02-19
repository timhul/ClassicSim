#pragma once

#include "PaladinSeal.h"
#include "TalentRequirer.h"

class Paladin;
class Random;
class SealOfCommandProc;

class SealOfCommand : public PaladinSeal, public TalentRequirer {
public:
    SealOfCommand(Paladin* paladin, PaladinSpells* paladin_spells);
    ~SealOfCommand() override;

    void refresh_seal() const override;
    Proc* get_proc() const;
    void signal_proc_in_progress();
    bool proc_is_in_progress() const;
    void run_proc();

private:
    PaladinSpells* paladin_spells;
    SealOfCommandProc* proc;
    Random* random;

    bool proc_in_progress {false};
    const unsigned base_min_dmg {47};
    const unsigned base_max_dmg {56};
    const int base_mana_cost {65};
    const QVector<double> benediction_ranks {1.0, 0.97, 0.94, 0.91, 0.88, 0.85};

    void judge_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
