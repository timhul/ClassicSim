#ifndef MAINHAND_H
#define MAINHAND_H

#include "MeleeWeapon.h"

class Mainhand: public MeleeWeapon {
public:
    Mainhand(QString name, Random* random,
             int type, int min, int max, float speed, float proc_rate):
        MeleeWeapon(name, random, type, min, max, speed, proc_rate) {}
    int get_item_type() const override;
protected:
private:
};

#endif // MAINHAND_H
