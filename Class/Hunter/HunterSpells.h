#pragma once

#include "CharacterSpells.h"

class AspectOfTheHawk;
class ExposeWeaknessProc;
class Hunter;
class HuntersMark;

class HunterSpells: public CharacterSpells {
public:
    HunterSpells(Hunter *hunter);
    ~HunterSpells() override;

    void start_pet_attack() override;
    void add_next_ranged_attack() override;
    void add_next_oh_attack() override;
    void oh_auto_attack(const int) override;
    void ranged_auto_attack(const int iteration) override;

    AspectOfTheHawk* get_aspect_of_the_hawk() const;
    AutoShot* get_auto_shot() const override;
    ExposeWeaknessProc* get_expose_weakness_proc() const;
    OffhandAttack* get_oh_attack() const override;

private:
    Hunter* hunter;
    AspectOfTheHawk* aspect_of_the_hawk;
    AutoShot* auto_shot;
    ExposeWeaknessProc* expose_weakness_proc;
    HuntersMark* hunters_mark;
};
