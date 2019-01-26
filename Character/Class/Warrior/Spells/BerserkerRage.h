#ifndef BERSERKERRAGE_H
#define BERSERKERRAGE_H

#include "Spell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class BerserkerRage: public Spell, public TalentRequirer {
public:
    BerserkerRage(Character* pchar);

private:
    Warrior* warr;
    StatisticsResource* statistics_resource;
    QVector<unsigned> talent_ranks;
    unsigned rage_gain;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // BERSERKERRAGE_H
