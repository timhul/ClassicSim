#ifndef FLURRY_H
#define FLURRY_H

#include "Buff.h"

class Flurry: public Buff {
public:
    Flurry(): Buff("Flurry", 15.0) {}

    void buff_effect(Character*) override;
protected:
private:
};




#endif // FLURRY_H
