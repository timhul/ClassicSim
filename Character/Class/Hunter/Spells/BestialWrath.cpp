#include "BestialWrath.h"

#include "BestialWrathBuff.h"
#include "Character.h"

BestialWrath::BestialWrath(Character* pchar, const QString& pet_name) :
    Spell("Bestial Wrath",
          "Assets/ability/Ability_druid_ferociousbite.png",
          pchar,
          RestrictedByGcd::Yes,
          120.0,
          ResourceType::Mana,
          206),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Bestial Wrath", 1, DisabledAtZero::Yes)}),
    bestial_wrath_buff(new BestialWrathBuff(pchar, pet_name))
{
    enabled = false;
}

BestialWrath::~BestialWrath() {
    if (bestial_wrath_buff->is_enabled())
        bestial_wrath_buff->disable_buff();

    delete bestial_wrath_buff;
}

void BestialWrath::spell_effect() {
    add_gcd_event();
    pchar->lose_mana(resource_cost);
    bestial_wrath_buff->apply_buff();
}

Buff* BestialWrath::get_hunters_mark_buff() const {
    return bestial_wrath_buff;
}

void BestialWrath::increase_talent_rank_effect(const QString&, const int) {
    bestial_wrath_buff->enable_buff();
}

void BestialWrath::decrease_talent_rank_effect(const QString&, const int) {
    bestial_wrath_buff->disable_buff();
}

