#ifndef MORTALSTRIKE_H
#define MORTALSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class MortalStrike: public Spell, public TalentRequirer {
public:
    MortalStrike(Character* pchar);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // MORTALSTRIKE_H
