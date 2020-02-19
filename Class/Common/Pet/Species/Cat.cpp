#include "Cat.h"

#include "Claw.h"
#include "Hunter.h"
#include "PetAutoAttack.h"
#include "Utils/Check.h"

Cat::Cat(Hunter* hunter) : HunterPet(hunter, "Cat", 1.5, 37.7) {
    claw = new Claw(hunter, this);
    pet_auto_attack = new PetAutoAttack(hunter, this, "Assets/items/Inv_misc_monsterclaw_03.png");

    spells.append(claw);

    add_spells();
}

void Cat::use_resource() {
    if (!action_ready())
        return;

    if (get_resource_level() >= claw->get_resource_cost())
        claw->perform();
}
