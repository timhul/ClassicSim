#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Proc.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class UnbridledWrath: public Proc, public TalentRequirer {
public:
    UnbridledWrath(Character* pchar);
    ~UnbridledWrath() override;

    void proc_effect() override;

protected:
private:
    friend class UnbridledWrathTalent;

    StatisticsResource* statistics_resource;
    Warrior* warr;
    QVector<unsigned> talent_ranks;

    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // UNBRIDLEDWRATH_H
