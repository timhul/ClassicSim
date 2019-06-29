#include "FireballInstant.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectUniqueDebuff.h"
#include "Random.h"
#include "Utils/Check.h"

FireballInstant::FireballInstant(Character* pchar,
                                 const QString& name,
                                 const unsigned instant_min,
                                 const unsigned instant_max,
                                 const unsigned dmg_over_duration,
                                 const int duration,
                                 const double spell_coefficient,
                                 const int spell_rank) :
    Spell(QString("Fireball%1").arg(name), "Assets/spell/Spell_fire_flamebolt.png", pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          spell_rank),
    fireball_dot(new NoEffectUniqueDebuff(pchar, duration, QString("Fireball%1 (rank %2)").arg(name).arg(spell_rank), "Assets/spell/Spell_fire_flamebolt.png", Hidden::No)),
    instant_dmg(new Random(instant_min, instant_max)),
    max_ticks(static_cast<unsigned>(round(static_cast<double>(duration) / 2.0))),
    base_dmg_per_tick(static_cast<double>(dmg_over_duration) / max_ticks),
    spell_coefficient(spell_coefficient)
{
    check((max_ticks > 0), "FireballInstant max ticks is zero");

    fireball_dot->enable_buff();
}

FireballInstant::~FireballInstant() {
    if (fireball_dot->is_enabled())
        fireball_dot->disable_buff();

    delete fireball_dot;
    delete cooldown;
    delete instant_dmg;
}

void FireballInstant::spell_effect() {
    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Fire, pchar->get_stats()->get_spell_crit_chance());
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::MISS) {
        magic_attack_result = MagicAttackResult::MISS;
        return increment_miss();
    }
    if (resist_roll == MagicResistResult::FULL_RESIST) {
        magic_attack_result = MagicAttackResult::MISS;
        return increment_full_resist();
    }

    apply_fireball_dot();

    const unsigned damage_dealt = instant_dmg->get_roll() + static_cast<unsigned>(round(pchar->get_stats()->get_spell_damage(MagicSchool::Fire) * spell_coefficient));
    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);
    const double damage_mod =  pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        magic_attack_result = MagicAttackResult::CRITICAL;
        pchar->spell_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * damage_mod * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod)), resource_cost, 0);
    }
    else {
        magic_attack_result = MagicAttackResult::HIT;
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt * damage_mod * resist_mod)), resource_cost, 0);
    }
}

void FireballInstant::perform_periodic() {
    if (!fireball_dot->is_active())
        return reset_effect();

    const double damage_dealt = (base_dmg_per_tick + damage_remaining) * pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire);
    damage_remaining = std::max(0.0, damage_dealt - round(damage_dealt));

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);

    --num_ticks_left;
    if (num_ticks_left > 0)
        this->engine->add_event(new DotTick(this, engine->get_current_priority() + 2.0));
}

void FireballInstant::apply_fireball_dot() {
    fireball_dot->apply_buff();

    if (!fireball_dot->is_active())
        return reset_effect();

    if (num_ticks_left == 0)
        this->engine->add_event(new DotTick(this, engine->get_current_priority() + 2.0));

    num_ticks_left = max_ticks;
}

void FireballInstant::reset_effect() {
    damage_remaining = 0;
    num_ticks_left = 0;
}
