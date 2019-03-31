#ifndef CAT_H
#define CAT_H

#include "Pet.h"

class Claw;
class Hunter;

class Cat: public Pet {
public:
    Cat(Hunter *pchar);
    ~Cat() override;

    unsigned get_resource_level() const override;
    void use_focus() override;

private:
    class Focus* focus;
    Claw* claw;
};

#endif // CAT_H
