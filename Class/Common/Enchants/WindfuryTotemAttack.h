#ifndef WINDFURYTOTEMATTACK_H
#define WINDFURYTOTEMATTACK_H

#include "Proc.h"

class WindfuryTotemAttack: public Proc {
public:
    WindfuryTotemAttack(Character* pchar);
    ~WindfuryTotemAttack() override;

    void proc_effect() override;

private:
    QVector<unsigned> rank_spells = {0, 122, 229, 315};
};

#endif // WINDFURYTOTEMATTACK_H
