#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Character;
class Weapon;

class SwordSpecialization : public Proc, public TalentRequirer {
public:
    SwordSpecialization(Character* pchar);
    ~SwordSpecialization() override;

    bool proc_specific_conditions_fulfilled() const override;

private:
    friend class SwordSpecializationTalent;

    Character* warr;
    const QVector<unsigned> talent_ranks;

    bool weapon_is_sword(Weapon*) const;

    void proc_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
