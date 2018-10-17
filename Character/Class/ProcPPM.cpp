
#include "ProcPPM.h"
#include "Character.h"
#include "CharacterStats.h"
#include <cassert>
#include "ItemNamespace.h"

ProcPPM::ProcPPM(const QString& name,
                 const int wpn,
                 const double ppm,
                 const double inner_cooldown,
                 const QVector<Proc*>& linked_procs,
                 const QVector<ProcInfo::Source>& proc_sources,
                 Character* pchar) :
    Proc(name, 0.0, inner_cooldown, linked_procs, proc_sources, pchar),
    proc_rate_base(ppm * 100 / 60),
    weapon(wpn)
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);
}

ProcPPM::~ProcPPM() = default;

unsigned ProcPPM::get_proc_range() const {
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        return static_cast<unsigned>(round(proc_rate_base * pchar->get_stats()->get_mh_wpn_speed() * 100));
    case EnchantSlot::OFFHAND:
        return static_cast<unsigned>(round(proc_rate_base * pchar->get_stats()->get_oh_wpn_speed() * 100));
    default:
        assert(false);
    }

    return 0;
}

