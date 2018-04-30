
#include "Spells.h"
#include "Character.h"
#include "FieryWeaponAttack.h"

Spells::Spells(Character* pchar, QObject* parent) :
    QObject(parent),
    pchar(pchar)
{
    this->fiery_weapon_attack = new FieryWeaponAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    this->spells = {fiery_weapon_attack};
}

Spells::~Spells()
{
    for (int i = 0; i < spells.size(); ++i) {
        delete spells[i];
    }

    spells.clear();
}

void Spells::add_spell(Spell* spell) {
    spells.append(spell);
}

void Spells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}

FieryWeaponAttack* Spells::get_fiery_weapon() const {
    return fiery_weapon_attack;
}
