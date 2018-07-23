
#include "Spells.h"
#include "Berserking.h"
#include "BloodFury.h"
#include "Character.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "ClassStatistics.h"

Spells::Spells(Character* pchar, QObject* parent) :
    QObject(parent),
    pchar(pchar)
{
    berserking = new Berserking(pchar->get_engine(), pchar, pchar->get_combat_roll());
    blood_fury = new BloodFury(pchar->get_engine(), pchar, pchar->get_combat_roll());
    spells = {berserking, blood_fury};
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

void Spells::mh_auto_attack(const int iteration) {
    if (!mh_attack->attack_is_valid(iteration))
        return;

    mh_attack->perform();

    add_next_mh_attack();
}

void Spells::add_next_mh_attack(void) {
    MainhandMeleeHit* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void Spells::oh_auto_attack(const int) {
    assert(false);
}

void Spells::add_next_oh_attack(void) {
    assert(false);
}

MainhandAttack* Spells::get_mh_attack() const {
    return this->mh_attack;
}

OffhandAttack* Spells::get_oh_attack() const {
    assert(false);
    return nullptr;
}

Berserking* Spells::get_berserking() const {
    return this->berserking;
}

BloodFury* Spells::get_blood_fury() const {
    return this->blood_fury;
}

void Spells::add_statistics() {
    for (int i = 0; i < spells.size(); ++i) {
        pchar->get_statistics()->add_spell_statistics(spells[i]->get_statistics_for_spell());
    }
}
