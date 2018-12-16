#ifndef RELENTLESSSTRIKES_H
#define RELENTLESSSTRIKES_H

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;
class StatisticsResource;

class RelentlessStrikes: public Proc, public TalentRequirer {
public:
    RelentlessStrikes(Character* pchar);
    ~RelentlessStrikes() override;

    void proc_effect() override;
    void set_current_combo_points(const unsigned);

protected:
private:
    friend class RelentlessStrikesTalent;

    StatisticsResource* statistics_resource;
    Rogue* rogue;
    unsigned combo_proc_percent;
    QVector<unsigned> talent_ranks;

    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // RELENTLESSSTRIKES_H
