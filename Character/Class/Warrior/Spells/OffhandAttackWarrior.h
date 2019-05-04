#ifndef OFFHANDATTACKWARRIOR_H
#define OFFHANDATTACKWARRIOR_H

#include "Spell.h"
#include "OffhandAttack.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class OffhandAttackWarrior: public OffhandAttack, public TalentRequirer {
public:
    OffhandAttackWarrior(Character* pchar);

    void extra_attack() override;

private:
    Warrior* warr;
    StatisticsResource* statistics_resource {nullptr};
    QVector<double> talent_ranks;

    void spell_effect() override;
    void calculate_damage(const bool) override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void gain_rage(const double rage_gain);
};

#endif // OFFHANDATTACKWARRIOR_H
