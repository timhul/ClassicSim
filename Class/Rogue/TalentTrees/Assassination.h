#pragma once

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Assassination : public TalentTree {
public:
    Assassination(Rogue* pchar);

private:
    Rogue* rogue;
    RogueSpells* spells;

    void add_improved_eviscerate(QMap<QString, Talent*>& talent_tier);
    void add_ruthlessness(QMap<QString, Talent*>& talent_tier);
    void add_improved_slice_and_dice(QMap<QString, Talent*>& talent_tier);
    void add_relentless_strikes(QMap<QString, Talent*>& talent_tier);
    void add_lethality(QMap<QString, Talent*>& talent_tier);
    void add_vile_poisons(QMap<QString, Talent*>& talent_tier);
    void add_improved_poisons(QMap<QString, Talent*>& talent_tier);
    void add_seal_fate(QMap<QString, Talent*>& talent_tier);
};
