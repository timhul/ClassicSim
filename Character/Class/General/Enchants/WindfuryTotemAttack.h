#ifndef WINDFURYTOTEMATTACK_H
#define WINDFURYTOTEMATTACK_H

#include "Proc.h"

class WindfuryTotemAttack: public Proc {
public:
    WindfuryTotemAttack(Engine* engine, Character* pchar, CombatRoll* roll);
    ~WindfuryTotemAttack();

    void proc_effect() override;

    void increase_spell_rank() override;
    void decrease_spell_rank() override;

protected:
private:
    QVector<int> rank_spells = {0, 122, 229, 315};
};

#endif // WINDFURYTOTEMATTACK_H
