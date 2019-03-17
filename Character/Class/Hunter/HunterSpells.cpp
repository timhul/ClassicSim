#include "HunterSpells.h"

#include "AutoShot.h"
#include "Hunter.h"
#include "MainhandAttack.h"
#include "MultiShot.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->mh_attack = new MainhandAttack(hunter);
    this->auto_shot = new AutoShot(hunter);
    this->multi_shot = new MultiShot(hunter);

    spells.append(mh_attack);
    spells.append(auto_shot);
    spells.append(multi_shot);
}

void HunterSpells::add_next_ranged_attack() {
}

AutoShot* HunterSpells::get_auto_shot() const {
    return this->auto_shot;
}

MultiShot* HunterSpells::get_multi_shot() const {
    return this->multi_shot;
}
