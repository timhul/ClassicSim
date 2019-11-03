#include "FelstrikerProc.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "EnabledBuffs.h"
#include "FelstrikerBuff.h"
#include "GeneralBuffs.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

FelstrikerProc::FelstrikerProc(Character* pchar_,
                               const QString& name_,
                               const QVector<ProcInfo::Source>& proc_sources_,
                               const double proc_rate,
                               const int duration) :
    Proc(name_, "Assets/items/Inv_weapon_shortblade_25.png", proc_rate, 0, QVector<Proc*>(), proc_sources_, pchar_)
{
    check((proc_sources_.contains(ProcInfo::Source::MainhandSwing) || proc_sources_.contains(ProcInfo::Source::OffhandSwing)),
          "No valid proc sources found");

    SharedBuff* buff = pchar_->get_enabled_buffs()->use_shared_buff("Felstriker");
    if (buff == nullptr) {
        felstriker_buff = new FelstrikerBuff(pchar_, duration);
        felstriker_buff->increment_reference();
        felstriker_buff->enable_buff();
    }
    else
        felstriker_buff = static_cast<FelstrikerBuff*>(buff);
}

FelstrikerProc::~FelstrikerProc() {
    pchar->get_enabled_buffs()->return_shared_buff(felstriker_buff);
}

void FelstrikerProc::proc_effect() {
    felstriker_buff->apply_buff();
}
