
#include "ProcPPM.h"
#include "Character.h"
#include "CharacterStats.h"
#include <assert.h>

ProcPPM::ProcPPM(const QString& name, const int wpn,
                 const double ppm, const double inner_cooldown, const bool recursive,
                 const QVector<Proc*> linked_procs,
                 const QVector<ProcInfo::Source> proc_sources,
                 Engine* engine, Character* pchar, CombatRoll* roll) :
    Proc(name, 0.0, inner_cooldown, recursive, linked_procs, proc_sources, engine, pchar, roll),
    proc_rate_base(ppm * 100 / 60),
    weapon(wpn)
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);
}

ProcPPM::~ProcPPM() {

}

int ProcPPM::get_proc_range() const {
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        return static_cast<int>(round(proc_rate_base * pchar->get_stats()->get_mh_wpn_speed() * 100));
    case EnchantSlot::OFFHAND:
        return static_cast<int>(round(proc_rate_base * pchar->get_stats()->get_oh_wpn_speed() * 100));
    default:
        assert(false);
    }

    return 0;
}

