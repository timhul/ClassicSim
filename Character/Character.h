#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Class.h"

class Character {
public:
    Character(Race* _race, Class* _class): race(_race), pclass(_class) {}
    Race* get_race(void);
    Class* get_class(void);
protected:
private:
    Race* race;
    Class* pclass;
};

#endif // CHARACTER_H
