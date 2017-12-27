#ifndef MAINHAND_H
#define MAINHAND_H

#include "MeleeWeapon.h"

class Mainhand: public MeleeWeapon {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // MAINHAND_H
