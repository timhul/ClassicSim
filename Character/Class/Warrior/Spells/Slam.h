#ifndef SLAM_H
#define SLAM_H

#include <QVector>

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class Slam: public SpellCastingTime, public TalentRequirer {
public:
    Slam(Warrior* pchar, WarriorSpells* spells);

private:
    Warrior* warr;
    WarriorSpells* spells;
    QVector<unsigned> talent_ranks;

    void spell_effect() override;
    void complete_cast_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // SLAM_H
