#include "WintersChillProc.h"

#include "Mage.h"
#include "ProcInfo.h"
#include "SharedDebuff.h"
#include "Utils/Check.h"

WintersChillProc::WintersChillProc(Mage* pchar, SharedDebuff* winters_chill) :
    Proc("Winter's Chill", "Assets/spell/Spell_frost_chillingblast.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>{ProcInfo::Source::Manual},
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Winter's Chill", 5, DisabledAtZero::Yes)}),
    debuff(winters_chill),
    proc_ranges({0, 2000, 4000, 6000, 8000, 10000})
{
    this->enabled = false;
}

void WintersChillProc::proc_effect() {
    debuff->apply_buff();
}

void WintersChillProc::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = proc_ranges[curr];
}

void WintersChillProc::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = proc_ranges[curr];
}
