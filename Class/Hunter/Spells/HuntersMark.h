#ifndef HUNTERSMARK_H
#define HUNTERSMARK_H

#include "Spell.h"

class Buff;
class HuntersMarkBuff;

class HuntersMark: public Spell {
public:
    HuntersMark(Character *pchar, HuntersMarkBuff* hunters_mark);
    ~HuntersMark() override;

    Buff* get_hunters_mark_buff() const;

private:
    HuntersMarkBuff* hunters_mark;

    void spell_effect() override;
};

#endif // HUNTERSMARK_H
