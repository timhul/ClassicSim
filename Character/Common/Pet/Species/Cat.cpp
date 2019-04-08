#include "Cat.h"

#include "Claw.h"
#include "Focus.h"
#include "FrenzyProc.h"
#include "Hunter.h"
#include "PetAutoAttack.h"
#include "Utils/Check.h"

Cat::Cat(Hunter* hunter) :
    Pet(hunter, "Cat", 1.5, 64.7)
{
    focus = new class Focus(hunter);
    resource = focus;

    claw = new Claw(hunter, this);
    frenzy_proc = new FrenzyProc(pchar, this);
    pet_auto_attack = new PetAutoAttack(hunter, this, "Assets/items/Inv_misc_monsterclaw_03.png");

    spells.append(claw);

    add_spells();
}

Cat::~Cat() {
    delete focus;
}

unsigned Cat::get_resource_level() const {
    return focus->current;
}

void Cat::use_focus() {
    if (!action_ready())
        return;

    if (pchar->get_resource_level(ResourceType::Focus) >= claw->get_resource_cost())
        claw->perform();
}
