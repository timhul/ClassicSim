#include "ClearcastingMage.h"

#include "Mage.h"
#include "NoEffectSelfBuff.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

ClearcastingMage::ClearcastingMage(Mage* pchar) :
    Proc("Clearcasting",
         "Assets/spell/Spell_shadow_manaburn.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source> {ProcInfo::Source::Manual},
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Arcane Concentration", 5, DisabledAtZero::Yes)}),
    buff(new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT, name, icon, Hidden::No, 1)),
    proc_ranges({0, 200, 400, 600, 800, 1000}) {
    this->enabled = false;
}

ClearcastingMage::~ClearcastingMage() {
    delete buff;
}

void ClearcastingMage::proc_effect() {
    buff->apply_buff();
}

void ClearcastingMage::increase_talent_rank_effect(const QString&, const int curr) {
    if (curr == 1)
        buff->enable_buff();

    proc_range = proc_ranges[curr];
}

void ClearcastingMage::decrease_talent_rank_effect(const QString&, const int curr) {
    if (curr == 0)
        buff->disable_buff();

    proc_range = proc_ranges[curr];
}
