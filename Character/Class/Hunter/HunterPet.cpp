#include "HunterPet.h"

#include "Focus.h"
#include "FrenzyProc.h"
#include "Hunter.h"

HunterPet::HunterPet(Hunter* pchar,
                     const QString &name,
                     double base_attack_speed,
                     double base_dps):
    Pet(pchar, name, base_attack_speed, base_dps),
    focus(new class Focus(pchar)),
    frenzy_proc(new FrenzyProc(pchar, this))
{
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
