#include "FireballInstant.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectUniqueDebuff.h"
#include "PeriodicDamageSpell.h"
#include "Random.h"
#include "Utils/Check.h"

FireballInstant::FireballInstant(Character* pchar_,
                                 const QString& name_,
                                 const unsigned instant_min,
                                 const unsigned instant_max,
                                 const unsigned dmg_over_duration,
                                 const int duration,
                                 const unsigned resource_cost_,
                                 const unsigned casting_time,
                                 const double spell_coefficient,
                                 const double spell_coefficient_dot,
                                 const int spell_rank_) :
    Spell(QString("Fireball%1").arg(name_), "Assets/spell/Spell_fire_flamebolt.png", pchar_,
          new CooldownControl(pchar_, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          spell_rank_),
    fireball_dot(new PeriodicDamageSpell(QString("Fireball DoT (rank %1)").arg(spell_rank_),
                                         "Assets/spell/Spell_fire_flamebolt.png", pchar_, Priority::Trash, RestrictedByGcd::No,
                                         MagicSchool::Fire, 2.0, duration, dmg_over_duration, resource_cost_, casting_time, spell_coefficient_dot)),
    instant_dmg(new Random(instant_min, instant_max)),
    spell_coefficient(spell_coefficient)
{
    fireball_dot->enable();
}

FireballInstant::~FireballInstant() {
    delete fireball_dot;
    delete cooldown;
    delete instant_dmg;
}

void FireballInstant::spell_effect() {
    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Fire, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire) + crit_bonus);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::MISS) {
        magic_attack_result = MagicAttackResult::MISS;
        return increment_miss();
    }
    if (resist_roll == MagicResistResult::FULL_RESIST) {
        magic_attack_result = MagicAttackResult::MISS;
        return increment_full_resist();
    }

    fireball_dot->perform();

    const unsigned damage_dealt = instant_dmg->get_roll() + static_cast<unsigned>(round(pchar->get_stats()->get_spell_damage(MagicSchool::Fire) * spell_coefficient));
    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);
    const double damage_mod = pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        magic_attack_result = MagicAttackResult::CRITICAL;
        pchar->spell_critical_effect(MagicSchool::Fire);
        last_damage_dealt = round(damage_dealt * damage_mod * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod);
        add_spell_crit_dmg(static_cast<int>(last_damage_dealt), get_resource_cost(), 0, resist_roll);
    }
    else {
        magic_attack_result = MagicAttackResult::HIT;
        pchar->spell_hit_effect(MagicSchool::Fire);
        last_damage_dealt = round(damage_dealt * damage_mod * resist_mod);
        add_spell_hit_dmg(static_cast<int>(last_damage_dealt), get_resource_cost(), 0, resist_roll);
    }
}

void FireballInstant::prepare_set_of_combat_iterations_spell_specific() {
    fireball_dot->prepare_set_of_combat_iterations();
}
