#ifndef OFFHAND_H
#define OFFHAND_H

#include "MeleeWeapon.h"

class Offhand: public MeleeWeapon {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // OFFHAND_H
