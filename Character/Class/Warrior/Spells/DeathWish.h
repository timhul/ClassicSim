#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class DeathWish: public Spell, public TalentRequirer {
public:
    DeathWish(Character* pchar);

protected:
private:
    friend class DeathWishTalent;

    Warrior* warr;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // DEATHWISH_H
