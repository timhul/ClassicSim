#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class BattleShoutBuff;
class Buff;
class Warrior;

class BattleShout: public Spell {
public:
    BattleShout(Warrior* pchar);
    ~BattleShout() override;

    Buff* get_buff() const;

private:
    BattleShoutBuff* buff;

    void spell_effect() override;
};

#endif // BATTLESHOUT_H
