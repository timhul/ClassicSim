#include "Cat.h"

#include "Claw.h"
#include "Hunter.h"
#include "PetAutoAttack.h"
#include "Utils/Check.h"

Cat::Cat(Hunter* hunter) :
    Pet(hunter, "Cat", 1.5, 64.7)
{
    claw = new Claw(hunter, this);
    pet_auto_attack = new PetAutoAttack(hunter, this, "Assets/items/Inv_misc_monsterclaw_03.png");

    spells.append(claw);

    add_spells();
}

void Cat::use_focus() {
    check(action_ready(), "Pet on GCD but attempted to cast pet ability");

    if (pchar->get_resource_level(ResourceType::Focus) >= claw->get_resource_cost())
        claw->perform();
}
