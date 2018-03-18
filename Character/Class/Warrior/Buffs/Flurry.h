#ifndef FLURRY_H
#define FLURRY_H

#include "Buff.h"

class Flurry: public Buff {
public:
    Flurry(Character* pchar): Buff(pchar, "Flurry", 15.0) {}

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
protected:
private:

};




#endif // FLURRY_H
