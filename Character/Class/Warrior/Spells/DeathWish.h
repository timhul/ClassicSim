#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class DeathWish: public Spell, public TalentRequirer {
public:
    DeathWish(Character* pchar);

private:
    Warrior* warr;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // DEATHWISH_H
