#include "ClearcastingShaman.h"

#include "NoEffectBuff.h"
#include "ProcInfo.h"
#include "Shaman.h"
#include "Utils/Check.h"

ClearcastingShaman::ClearcastingShaman(Shaman* pchar) :
    Proc("Clearcasting", "Assets/spell/Spell_shadow_manaburn.png", 0.1, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>{ProcInfo::Source::Manual},
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Elemental Focus", 1, DisabledAtZero::Yes)}),
    buff(new NoEffectBuff(pchar, BuffDuration::PERMANENT, name, icon, Hidden::No, Debuff::No, 1))
{
    this->enabled = false;
}

ClearcastingShaman::~ClearcastingShaman() {
    delete buff;
}

void ClearcastingShaman::proc_effect() {
    buff->apply_buff();
}

void ClearcastingShaman::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void ClearcastingShaman::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
