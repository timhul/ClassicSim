#ifndef TWOHANDER_H
#define TWOHANDER_H

#include "MeleeWeapon.h"

class TwoHander: public MeleeWeapon {
public:
    TwoHander(QString name, Random* random,
              int type, int min, int max, float speed, float proc_rate):
         MeleeWeapon(name, random, type, min, max, speed, proc_rate) {}
    int get_item_type() const override;
protected:
private:
};

#endif // TWOHANDER_H
