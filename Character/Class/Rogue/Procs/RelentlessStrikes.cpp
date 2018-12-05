#include "RelentlessStrikes.h"

#include "ProcInfo.h"
#include "Rogue.h"

RelentlessStrikes::RelentlessStrikes(Character* pchar) :
    Proc("Relentless Strikes", "Assets/ability/Ability_warrior_decisivestrike.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Relentless Strikes", 1, DisabledAtZero::Yes)}),
    rogue(dynamic_cast<Rogue*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 2000};
    proc_range = talent_ranks[0];
    combo_proc_percent = talent_ranks[0];
}

RelentlessStrikes::~RelentlessStrikes() = default;

void RelentlessStrikes::proc_effect() {
    rogue->gain_energy(25);
}

void RelentlessStrikes::set_current_combo_points(const unsigned combo_points) {
    proc_range = combo_proc_percent * combo_points;
}

void RelentlessStrikes::increase_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
    combo_proc_percent = talent_ranks[curr];
}

void RelentlessStrikes::decrease_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
    combo_proc_percent = talent_ranks[curr];
}
