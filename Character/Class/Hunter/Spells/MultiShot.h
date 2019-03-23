#ifndef MULTISHOT_H
#define MULTISHOT_H

#include "Spell.h"
#include "TalentRequirer.h"

class MultiShot: public Spell, public TalentRequirer {
public:
    MultiShot(Character* pchar);

private:
    QVector<double> talent_ranks;
    double resource_base;
    QVector<double> efficiency_ranks;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // MULTISHOT_H
