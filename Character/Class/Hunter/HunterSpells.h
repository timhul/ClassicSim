#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "CharacterSpells.h"

class AimedShot;
class Hunter;
class MultiShot;

class HunterSpells: public CharacterSpells {
public:
    HunterSpells(Hunter *hunter);

    void add_next_ranged_attack() override;

    AimedShot* get_aimed_shot() const;
    AutoShot* get_auto_shot() const override;
    MultiShot* get_multi_shot() const;

private:
    Hunter* hunter;
    AimedShot* aimed_shot;
    AutoShot* auto_shot;
    MultiShot* multi_shot;
};

#endif // HUNTERSPELLS_H
