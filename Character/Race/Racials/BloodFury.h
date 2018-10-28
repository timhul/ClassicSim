#ifndef BLOODFURY_H
#define BLOODFURY_H

#include "Spell.h"

class BloodFuryBuff;

class BloodFury: public Spell {
public:
    BloodFury(Character* pchar);
    ~BloodFury() override;

protected:
private:
    BloodFuryBuff* buff;

    void spell_effect() override;
    void enable_spell_effect() override;
    void disable_spell_effect() override;
};

#endif // BLOODFURY_H
