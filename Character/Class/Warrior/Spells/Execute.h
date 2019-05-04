#ifndef EXECUTE_H
#define EXECUTE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Execute: public Spell, public TalentRequirer {
public:
    Execute(Character* pchar);

private:
    Warrior* warr;
    QVector<QPair<int, int>> spell_ranks;
    QVector<int> talent_ranks;
    unsigned initial_dmg;
    unsigned dmg_per_rage_converted;
    double execute_threshold;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // EXECUTE_H
