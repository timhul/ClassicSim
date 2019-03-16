#include "Character.h"
#include "EnabledBuffs.h"
#include "FelstrikerBuff.h"
#include "FelstrikerProc.h"
#include "GeneralBuffs.h"
#include "ProcInfo.h"
#include "CharacterSpells.h"

FelstrikerProc::FelstrikerProc(Character* pchar,
                               const QString& name,
                               const QVector<ProcInfo::Source>& proc_sources,
                               const double proc_rate,
                               const int duration) :
    Proc(name, "Assets/items/Inv_weapon_shortblade_25.png", proc_rate, 0, QVector<Proc*>(), proc_sources, pchar)
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));

    SharedBuff* buff = pchar->get_enabled_buffs()->use_shared_buff("Felstriker");
    if (buff == nullptr) {
        felstriker_buff = new FelstrikerBuff(pchar, duration);
        felstriker_buff->increment_reference();
        felstriker_buff->enable_buff();
    }
    else
        felstriker_buff = dynamic_cast<FelstrikerBuff*>(buff);
}

FelstrikerProc::~FelstrikerProc() {
    pchar->get_enabled_buffs()->return_shared_buff(felstriker_buff);
}

void FelstrikerProc::proc_effect() {
    felstriker_buff->apply_buff();
}
