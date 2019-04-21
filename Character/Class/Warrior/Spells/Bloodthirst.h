#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Bloodthirst: public Spell, public TalentRequirer {
public:
    Bloodthirst(Character* pchar);

private:
    Warrior* warr;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // BLOODTHIRST_H
