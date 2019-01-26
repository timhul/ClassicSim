#ifndef ANGERMANAGEMENT_H
#define ANGERMANAGEMENT_H

#include "Spell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class AngerManagement: public Spell, public TalentRequirer {
public:
    AngerManagement(Character* pchar);

    void perform_periodic() override;
    void perform_pre_combat() override;

private:
    Warrior* warr;
    StatisticsResource* statistics_resource;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // ANGERMANAGEMENT_H
