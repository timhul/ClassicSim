#include "HunterSpells.h"

#include "AutoShoot.h"
#include "Hunter.h"
#include "MainhandAttack.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->mh_attack = new MainhandAttack(hunter);
    this->auto_shoot = new AutoShoot(hunter);

    spells.append(mh_attack);
    spells.append(auto_shoot);
}

AutoShoot* HunterSpells::get_auto_shoot() const {
    return this->auto_shoot;
}

void HunterSpells::add_next_ranged_attack() {
}
