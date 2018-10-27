#ifndef USETRINKETAPPLYBUFF_H
#define USETRINKETAPPLYBUFF_H

#include "Spell.h"

class Buff;

class UseTrinketApplyBuff: public Spell {
public:
    UseTrinketApplyBuff(Character* pchar,
                        const QString& name,
                        const QString &icon,
                        const int cooldown,
                        Buff *buff);
    ~UseTrinketApplyBuff() override;

protected:
private:
    Buff* buff;

    void spell_effect() override;
};

#endif // USETRINKETAPPLYBUFF_H
