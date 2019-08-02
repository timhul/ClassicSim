#pragma once

#include "TalentTree.h"

class Druid;
class DruidSpells;

class Balance: public TalentTree {
public:
    Balance(Druid* druid);
    ~Balance() override = default;

private:
    Druid* druid;
    DruidSpells* spells;

    void add_improved_wrath(QMap<QString, Talent*>& talent_tier);
    void add_improved_natures_grasp(QMap<QString, Talent*>& talent_tier);
    void add_improved_moonfire(QMap<QString, Talent*>& talent_tier);
    void add_natural_weapons(QMap<QString, Talent*>& talent_tier);
    void add_omen_of_clarity(QMap<QString, Talent*>& talent_tier);
    void add_vengeance(QMap<QString, Talent*>& talent_tier);
    void add_improved_starfire(QMap<QString, Talent*>& talent_tier);
    void add_natures_grace(QMap<QString, Talent*>& talent_tier);
    void add_moonglow(QMap<QString, Talent*>& talent_tier);
    void add_moonfury(QMap<QString, Talent*>& talent_tier);
};
