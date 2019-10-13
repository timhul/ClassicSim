#include "ProcPPM.h"

#include "Character.h"
#include "Equipment.h"
#include "ItemNamespace.h"
#include "Utils/Check.h"
#include "Weapon.h"
#include <cmath>

ProcPPM::ProcPPM(const QString& name,
                 const QString& icon,
                 const int wpn,
                 const double ppm,
                 const double inner_cooldown,
                 const QVector<Proc*>& linked_procs,
                 const QVector<ProcInfo::Source>& proc_sources,
                 Character* pchar) :
    Proc(name, icon, 0.0, inner_cooldown, linked_procs, proc_sources, pchar),
    proc_rate_base(ppm * 100 / 60),
    weapon(wpn)
{
    check((weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND), "Tried setting ProcPPM on non MH/OH");
}

ProcPPM::~ProcPPM() = default;

unsigned ProcPPM::get_proc_range() const {
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        return static_cast<unsigned>(round(proc_rate_base * pchar->get_equipment()->get_mainhand()->get_base_weapon_speed() * 100));
    case EnchantSlot::OFFHAND:
        return static_cast<unsigned>(round(proc_rate_base * pchar->get_equipment()->get_mainhand()->get_base_weapon_speed() * 100));
    default:
        check(false, "ProcPPM::get_proc_range reached end of switch");
        return 0;
    }
}
