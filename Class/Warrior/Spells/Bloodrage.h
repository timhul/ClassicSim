#ifndef BLOODRAGE_H
#define BLOODRAGE_H

#include "Spell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class Bloodrage: public Spell, public TalentRequirer {
public:
    Bloodrage(Character* pchar);
    ~Bloodrage() override;

    void perform_periodic() override;

private:
    friend class ImprovedBloodrage;

    Warrior* warr;
    StatisticsResource* statistics_resource {nullptr};

    QVector<unsigned> talent_ranks {10, 12, 15};
    unsigned immediate_rage_gain {10};
    const unsigned periodic_rage_base {10};
    unsigned periodic_rage_current {10};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void gain_rage(const unsigned rage_gain);
};

#endif // BLOODRAGE_H
