#pragma once

#include "PeriodicResourceGainSpell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;
class WarriorSpells;

class AngerManagement : public PeriodicResourceGainSpell, public TalentRequirer {
public:
    AngerManagement(Warrior* warrior, WarriorSpells* warrior_spells);

    void perform_start_of_combat() override;

private:
    Warrior* warrior;
    WarriorSpells* warrior_spells;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
