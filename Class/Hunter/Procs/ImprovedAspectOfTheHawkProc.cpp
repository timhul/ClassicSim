#include "ImprovedAspectOfTheHawkProc.h"

#include "AspectOfTheHawkBuff.h"
#include "ImprovedAspectOfTheHawkBuff.h"
#include "ProcInfo.h"

ImprovedAspectOfTheHawkProc::ImprovedAspectOfTheHawkProc(Character* pchar, AspectOfTheHawkBuff* hawk_buff) :
    Proc("Improved Aspect of the Hawk", "Assets/spell/Spell_nature_ravenform.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::RangedAutoShot, ProcInfo::Source::RangedSpell}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Aspect of the Hawk", 5, DisabledAtZero::Yes)}),
    hawk_buff(hawk_buff),
    imp_hawk_buff(new ImprovedAspectOfTheHawkBuff(pchar)),
    talent_ranks({0, 100, 200, 300, 400, 500})
{
    this->enabled = false;
    proc_range = talent_ranks[0];
}

ImprovedAspectOfTheHawkProc::~ImprovedAspectOfTheHawkProc() {
    if (imp_hawk_buff->is_enabled())
        imp_hawk_buff->disable_buff();

    delete imp_hawk_buff;
}

void ImprovedAspectOfTheHawkProc::proc_effect() {
    imp_hawk_buff->apply_buff();
}

ImprovedAspectOfTheHawkBuff* ImprovedAspectOfTheHawkProc::get_improved_aspect_of_the_hawk_proc() const {
    return this->imp_hawk_buff;
}

void ImprovedAspectOfTheHawkProc::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];

    if (curr == 1)
        imp_hawk_buff->enable_buff();
}

void ImprovedAspectOfTheHawkProc::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];

    if (curr == 0)
        imp_hawk_buff->disable_buff();
}

bool ImprovedAspectOfTheHawkProc::proc_specific_conditions_fulfilled() const {
    return hawk_buff->is_active();
}
