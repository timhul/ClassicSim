#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Item.h"

class MeleeWeapon: public Item {
public:
    MeleeWeapon(std::string name, int type, int min, int max, float speed, float proc_rate):
        Item(name) {
        this->weapon_type = type;
        this->min_dmg = min;
        this->max_dmg = max;
        this->weapon_speed = speed;
        this->proc_rate = proc_rate;
    }
    int get_weapon_type() const;
    int get_min_dmg() const;
    int get_max_dmg() const;
    float get_base_weapon_speed() const;
    float get_weapon_proc_rate() const;
    // Also need a pointer to some proc event (e.g. Ironfoe triggers an extra attack event).

protected:
    int weapon_type;
    int min_dmg;
    int max_dmg;
    float weapon_speed;
    float proc_rate;
private:
};

#endif // MELEEWEAPON_H
