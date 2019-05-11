#ifndef CAT_H
#define CAT_H

#include "HunterPet.h"

class Claw;
class Hunter;

class Cat: public HunterPet {
public:
    Cat(Hunter* pchar);

    void use_resource() override;

private:
    Claw* claw;
};

#endif // CAT_H
