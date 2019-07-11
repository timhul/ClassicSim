#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Paladin;
class PeriodicDamageSpell;

class Consecration: public Spell, public TalentRequirer {
public:
    Consecration(Paladin* pchar,
                 CooldownControl* cooldown_control,
                 const int spell_rank);
    ~Consecration() override;

    bool is_rank_learned() const override;

private:
    PeriodicDamageSpell* cons_dot_1;
    PeriodicDamageSpell* cons_dot_2;

    void spell_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};
