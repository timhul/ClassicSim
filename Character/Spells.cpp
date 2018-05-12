
#include "Spells.h"
#include "Character.h"
#include "FieryWeaponAttack.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "ClassStatistics.h"

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

void Spells::start_attack(void) {
    add_next_mh_attack();

    if (pchar->is_dual_wielding()) {
        add_next_oh_attack();
    }
}

MainhandAttack* Spells::get_mh_attack() const {
    return this->mh_attack;
}

OffhandAttack* Spells::get_oh_attack() const {
    return this->oh_attack;
}

FieryWeaponAttack* Spells::get_fiery_weapon() const {
    return fiery_weapon_attack;
}

void Spells::add_next_mh_attack(void) {
    MainhandMeleeHit* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void Spells::add_next_oh_attack(void) {
    OffhandMeleeHit* new_event = new OffhandMeleeHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void Spells::add_statistics() {
    for (int i = 0; i < spells.size(); ++i) {
        pchar->get_statistics()->add_spell_statistics(spells[i]->get_statistics_for_spell());
    }
}
