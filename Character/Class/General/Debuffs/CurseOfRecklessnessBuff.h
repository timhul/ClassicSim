#ifndef CURSEOFRECKLESSNESSBUFF_H
#define CURSEOFRECKLESSNESSBUFF_H

#include "ExternalBuff.h"

class CurseOfRecklessnessBuff: public ExternalBuff {
public:
    CurseOfRecklessnessBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};

#endif // CURSEOFRECKLESSNESSBUFF_H
