#ifndef TWOHANDER_H
#define TWOHANDER_H

#include "MeleeWeapon.h"

class TwoHander: public MeleeWeapon {
public:
    TwoHander(std::string name, int type, int min, int max, float speed, float proc_rate):
        MeleeWeapon(name, type, min, max, speed, proc_rate) {}
    int get_item_type() const override;
protected:
private:
};

#endif // TWOHANDER_H
