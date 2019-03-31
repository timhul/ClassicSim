#ifndef CAT_H
#define CAT_H

#include "Pet.h"

class Claw;
class Hunter;

class Cat: public Pet {
public:
    Cat(Hunter *pchar);

    void use_focus() override;

private:
    Claw* claw;
};

#endif // CAT_H
