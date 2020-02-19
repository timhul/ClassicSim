#include "HunterPet.h"

#include "Focus.h"
#include "FrenzyProc.h"
#include "Hunter.h"
#include "Utils/Check.h"

HunterPet::HunterPet(Hunter* pchar, const QString& name, double base_attack_speed, double base_dps) :
    Pet(pchar, name, base_attack_speed, base_dps),
    ItemModificationRequirer({22015, 22061}),
    focus(new class Focus(pchar)),
    frenzy_proc(new FrenzyProc(pchar, this)) {
    resource = focus;
}

HunterPet::~HunterPet() {
    delete frenzy_proc;
    delete focus;
}

void HunterPet::melee_critical_effect() {
    if (frenzy_proc->is_enabled())
        frenzy_proc->perform();
}

FrenzyProc* HunterPet::get_frenzy_proc() {
    return this->frenzy_proc;
}

unsigned HunterPet::get_resource_level() const {
    return focus->current;
}

void HunterPet::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 22015:
        increase_crit_chance(300);
        break;
    case 22061:
        increase_damage_modifier(3);
        break;
    default:
        check(false, "HunterPet::activate_item_effect reached end of switch");
    }
}

void HunterPet::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 22015:
        decrease_crit_chance(300);
        break;
    case 22061:
        decrease_damage_modifier(3);
        break;
    default:
        check(false, "HunterPet::deactivate_item_effect reached end of switch");
    }
}
