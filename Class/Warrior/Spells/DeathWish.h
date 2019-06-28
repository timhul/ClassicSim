#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class DeathWishBuff;
class Warrior;

class DeathWish: public Spell, public TalentRequirer {
public:
    DeathWish(Character* pchar);
    ~DeathWish() override;

private:
    Warrior* warr;
    DeathWishBuff* death_wish_buff;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
