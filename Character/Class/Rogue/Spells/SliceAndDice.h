#ifndef SLICEANDDICE_H
#define SLICEANDDICE_H

#include "Spell.h"

class Rogue;
class SliceAndDiceBuff;

class SliceAndDice: public Spell {
public:
    SliceAndDice(Character* pchar);
    ~SliceAndDice() override;

protected:
private:
    Rogue* rogue;
    SliceAndDiceBuff* buff;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};

#endif // SLICEANDDICE_H
