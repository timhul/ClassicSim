
#include "Buffs.h"
#include "Character.h"
#include "HolyStrength.h"

Buffs::Buffs(Character* pchar, QObject* parent) :
    QObject(parent),
    pchar(pchar)
{
    this->holy_strength_mh = new HolyStrength(pchar);
    this->holy_strength_oh = new HolyStrength(pchar);

    this->buffs = {holy_strength_mh, holy_strength_oh};
}

Buffs::~Buffs()
{
    for (int i = 0; i < buffs.size(); ++i) {
        delete buffs[i];
    }

    buffs.clear();
}

void Buffs::add_buff(Buff* buff) {
    buffs.append(buff);
}

void Buffs::reset() {
    for (int i = 0; i < buffs.size(); ++i) {
        buffs[i]->reset();
    }
}

HolyStrength* Buffs::get_holy_strength_mh() const {
    return this->holy_strength_mh;
}

HolyStrength* Buffs::get_holy_strength_oh() const {
    return this->holy_strength_oh;
}
