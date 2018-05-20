
#include "Crusader.h"
#include "Character.h"
#include "Buffs.h"
#include "HolyStrength.h"

Crusader::Crusader(Engine* engine, Character* pchar, CombatRoll* roll, const int weapon) :
    ProcPPM("Holy Strength", weapon, 1.0, 0.0, false, QVector<Proc*>(),
            QVector<ProcInfo::Source>(),
            engine, pchar, roll)
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);

    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing});
        break;
    }
}

Crusader::~Crusader() {
}

void Crusader::proc_effect() {
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        // TODO: Add proc/resource gain statistics
        // add_proc_stats(1, "Mainhand Proc");
        return pchar->get_buffs()->get_holy_strength_mh()->apply_buff();
    case EnchantSlot::OFFHAND:
        // TODO: Add proc/resource gain statistics
        // add_proc_stats(1, "Offhand Proc");
        return pchar->get_buffs()->get_holy_strength_oh()->apply_buff();
    }
}
