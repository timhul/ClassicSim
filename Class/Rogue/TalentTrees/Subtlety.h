#pragma once

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Subtlety : public TalentTree {
public:
    Subtlety(Rogue* pchar);

private:
    Rogue* rogue;
    RogueSpells* spells;

    void add_opportunity(QMap<QString, Talent*>& talent_tier);
    void add_hemorrhage(QMap<QString, Talent*>& talent_tier);
};
