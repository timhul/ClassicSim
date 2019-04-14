#include "ExposeWeaknessProc.h"

#include "ExposeWeaknessBuff.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

ExposeWeaknessProc::ExposeWeaknessProc(Character* pchar) :
    Proc("Expose Weakness", "Assets/ability/Ability_hunter_snipershot.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::RangedAutoShot, ProcInfo::Source::RangedSpell}),
         pchar),
    SetBonusRequirer({"Dragonstalker Armor"}),
    expose_weakness_buff(new ExposeWeaknessBuff(pchar))
{
    this->enabled = false;
    proc_range = 1600;
}

ExposeWeaknessProc::~ExposeWeaknessProc() {
    if (is_enabled())
        disable();

    delete expose_weakness_buff;
}

void ExposeWeaknessProc::proc_effect() {
    expose_weakness_buff->apply_buff();
}

ExposeWeaknessBuff* ExposeWeaknessProc::get_expose_weakness_buff() const {
    return this->expose_weakness_buff;
}

void ExposeWeaknessProc::enable_spell_effect() {
    enable_proc();
    expose_weakness_buff->enable_buff();
}

void ExposeWeaknessProc::disable_spell_effect() {
    expose_weakness_buff->disable_buff();
    disable_proc();
}

void ExposeWeaknessProc::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Dragonstalker Armor") {
        switch (set_bonus) {
        case 8:
            enable();
            break;
        default:
            check(false, "ExposeWeakness::activate_set_bonus_effect reached end of switch");
        }
    }
}

void ExposeWeaknessProc::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Dragonstalker Armor") {
        switch (set_bonus) {
        case 8:
            disable();
            break;
        default:
            check(false, "ExposeWeakness::activate_set_bonus_effect reached end of switch");
        }
    }
}
