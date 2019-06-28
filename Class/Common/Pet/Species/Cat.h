#pragma once

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
