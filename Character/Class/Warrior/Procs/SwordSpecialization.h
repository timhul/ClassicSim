#ifndef SWORDSPECIALIZATION_H
#define SWORDSPECIALIZATION_H

#include "Proc.h"
#include "TalentRequirer.h"

class Character;
class Weapon;

class SwordSpecialization: public Proc, public TalentRequirer {
public:
    SwordSpecialization(Character* pchar);
    ~SwordSpecialization() override;

    void proc_effect() override;

    bool proc_specific_conditions_fulfilled() const override;
protected:
private:
    friend class SwordSpecializationTalent;
    friend class SwordSpecializationTalentRogue;

    Character* warr;

    bool weapon_is_sword(Weapon*) const;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // SWORDSPECIALIZATION_H
