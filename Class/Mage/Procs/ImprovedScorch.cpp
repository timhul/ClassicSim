#include "ImprovedScorch.h"

#include "Mage.h"
#include "ProcInfo.h"
#include "SharedDebuff.h"
#include "Utils/Check.h"

ImprovedScorch::ImprovedScorch(Mage* pchar, SharedDebuff* fire_vulnerability) :
    Proc("Improved Scorch",
         "Assets/spell/Spell_fire_soulburn.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source> {ProcInfo::Source::Manual},
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Improved Scorch", 3, DisabledAtZero::Yes)}),
    debuff(fire_vulnerability),
    proc_ranges({0, 3333, 6666, 10000}) {
    this->enabled = false;
}

void ImprovedScorch::proc_effect() {
    debuff->apply_buff();
}

void ImprovedScorch::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = proc_ranges[curr];
}

void ImprovedScorch::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = proc_ranges[curr];
}
