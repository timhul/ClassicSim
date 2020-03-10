#include "DeathWish.h"

#include "CooldownControl.h"
#include "DeathWishBuff.h"
#include "Warrior.h"

DeathWish::DeathWish(Warrior* warrior) :
    Spell("Death Wish",
          "Assets/spell/Spell_shadow_deathpact.png",
          warrior,
          new CooldownControl(warrior, 180.0),
          RestrictedByGcd::Yes,
          ResourceType::Rage,
          10),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Death Wish", 1, DisabledAtZero::Yes)}),
    warrior(warrior),
    death_wish_buff(new DeathWishBuff(warrior)) {
    this->enabled = false;
}

DeathWish::~DeathWish() {
    delete death_wish_buff;
    delete cooldown;
}

void DeathWish::spell_effect() {
    death_wish_buff->apply_buff();

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    warrior->lose_rage(resource_cost);
}

SpellStatus DeathWish::is_ready_spell_specific() const {
    return warrior->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void DeathWish::increase_talent_rank_effect(const QString&, const int) {
    death_wish_buff->enable_buff();
}

void DeathWish::decrease_talent_rank_effect(const QString&, const int) {
    death_wish_buff->disable_buff();
}
