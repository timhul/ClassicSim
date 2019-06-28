#pragma once

#include "Spell.h"

class AspectOfTheHawkBuff;
class Buff;
class ImprovedAspectOfTheHawkProc;
class Proc;

class AspectOfTheHawk: public Spell {
public:
    AspectOfTheHawk(Character *pchar);
    ~AspectOfTheHawk() override;

    Proc* get_improved_aspect_of_the_hawk_proc() const;
    AspectOfTheHawkBuff *get_aspect_of_the_hawk_buff() const;

private:
    AspectOfTheHawkBuff* aspect_of_the_hawk_buff;
    ImprovedAspectOfTheHawkProc* imp_hawk_proc;

    void spell_effect() override;
};
