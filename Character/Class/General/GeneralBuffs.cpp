
#include "GeneralBuffs.h"
#include "Character.h"
#include "HolyStrength.h"

GeneralBuffs::GeneralBuffs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction)
{
    this->holy_strength_mh = new HolyStrength(pchar);
    this->holy_strength_oh = new HolyStrength(pchar);

    this->buffs = {holy_strength_mh, holy_strength_oh};
}

GeneralBuffs::~GeneralBuffs()
{
    for (int i = 0; i < this->buffs.size(); ++i) {
        delete this->buffs[i];
    }

    this->buffs.clear();
}

void GeneralBuffs::switch_faction() {
}

HolyStrength* GeneralBuffs::get_holy_strength_mh() const {
    return this->holy_strength_mh;
}

HolyStrength* GeneralBuffs::get_holy_strength_oh() const {
    return this->holy_strength_oh;
}
