#ifndef TWOHANDER_H
#define TWOHANDER_H

#include "MeleeWeapon.h"

class TwoHander: public MeleeWeapon {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // TWOHANDER_H
