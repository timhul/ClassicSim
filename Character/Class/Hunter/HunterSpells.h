#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "CharacterSpells.h"

class AimedShot;
class Hunter;
class HuntersMark;
class MultiShot;

class HunterSpells: public CharacterSpells {
public:
    HunterSpells(Hunter *hunter);

    void add_next_ranged_attack() override;
    void add_next_oh_attack() override;
    void oh_auto_attack(const int) override;
    void ranged_auto_attack(const int iteration) override;

    AimedShot* get_aimed_shot() const;
    AutoShot* get_auto_shot() const override;
    HuntersMark* get_hunters_mark() const;
    MultiShot* get_multi_shot() const;
    OffhandAttack* get_oh_attack() const override;

private:
    Hunter* hunter;
    AimedShot* aimed_shot;
    AutoShot* auto_shot;
    HuntersMark* hunters_mark;
    MultiShot* multi_shot;
};

#endif // HUNTERSPELLS_H
