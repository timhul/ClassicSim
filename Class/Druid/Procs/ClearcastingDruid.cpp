#include "ClearcastingDruid.h"

#include <cmath>

#include "Druid.h"
#include "Equipment.h"
#include "ItemNamespace.h"
#include "NoEffectSelfBuff.h"
#include "ProcInfo.h"
#include "Utils/Check.h"
#include "Weapon.h"

ClearcastingDruid::ClearcastingDruid(Druid* pchar) :
    ProcPPM("Clearcasting", "Assets/spell/Spell_shadow_manaburn.png", EnchantSlot::MAINHAND, 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>{ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing},
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Omen of Clarity", 1, DisabledAtZero::Yes)}),
    buff(new NoEffectSelfBuff(pchar, 600, name, icon, Hidden::No, 1))
{
    this->enabled = false;
}

ClearcastingDruid::~ClearcastingDruid() {
    delete buff;
}

void ClearcastingDruid::proc_effect() {
    buff->apply_buff();
}

unsigned ClearcastingDruid::get_proc_range() const {
    return static_cast<unsigned>(round(proc_rate_base * pchar->get_equipment()->get_mainhand()->get_base_weapon_speed() * 100));
}

void ClearcastingDruid::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void ClearcastingDruid::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
