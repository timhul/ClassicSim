#include "HunterSpells.h"

#include "AutoShoot.h"
#include "Hunter.h"
#include "MainhandAttack.h"
#include "MultiShot.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->mh_attack = new MainhandAttack(hunter);
    this->auto_shoot = new AutoShoot(hunter);
    this->multi_shot = new MultiShot(hunter);

    spells.append(mh_attack);
    spells.append(auto_shoot);
    spells.append(multi_shot);
}

void HunterSpells::add_next_ranged_attack() {
}

AutoShoot* HunterSpells::get_auto_shoot() const {
    return this->auto_shoot;
}

MultiShot* HunterSpells::get_multi_shot() const {
    return this->multi_shot;
}
