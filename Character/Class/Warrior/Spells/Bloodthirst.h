#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Bloodthirst: public Spell, public TalentRequirer {
public:
    Bloodthirst(Character* pchar);

protected:
private:
    friend class BloodthirstTalent;

    Warrior* warr;

    void spell_effect() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // BLOODTHIRST_H
