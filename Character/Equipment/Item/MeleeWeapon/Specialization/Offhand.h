#ifndef OFFHAND_H
#define OFFHAND_H

#include "MeleeWeapon.h"

class Offhand: public MeleeWeapon {
public:
    Offhand(std::string name, int type, int min, int max, float speed, float proc_rate):
        MeleeWeapon(name, type, min, max, speed, proc_rate) {}
    int get_item_type() const override;
protected:
private:
};

#endif // OFFHAND_H
