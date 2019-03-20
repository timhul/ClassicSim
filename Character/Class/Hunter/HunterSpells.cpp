#include "HunterSpells.h"

#include "AimedShot.h"
#include "AutoShot.h"
#include "Hunter.h"
#include "MainhandAttack.h"
#include "MultiShot.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->aimed_shot = new AimedShot(hunter);
    this->auto_shot = new AutoShot(hunter);
    this->mh_attack = new MainhandAttack(hunter);
    this->multi_shot = new MultiShot(hunter);

    spells.append(aimed_shot);
    spells.append(auto_shot);
    spells.append(mh_attack);
    spells.append(multi_shot);
}

void HunterSpells::add_next_ranged_attack() {
}

AimedShot* HunterSpells::get_aimed_shot() const {
    return this->aimed_shot;
}

AutoShot* HunterSpells::get_auto_shot() const {
    return this->auto_shot;
}

MultiShot* HunterSpells::get_multi_shot() const {
    return this->multi_shot;
}
