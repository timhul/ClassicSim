#ifndef RUTHLESSNESS_H
#define RUTHLESSNESS_H

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;

class Ruthlessness: public Proc, public TalentRequirer {
public:
    Ruthlessness(Character* pchar);
    ~Ruthlessness() override;

    void proc_effect() override;

protected:
private:
    friend class RuthlessnessTalent;

    Rogue* rogue;
    QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // RUTHLESSNESS_H
