#include "Spell.h"

#include <utility>

#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownReady.h"
#include "Engine.h"
#include "Mechanics.h"
#include "Spells.h"
#include "StatisticsSpell.h"
#include "Target.h"

Spell::Spell(QString name,
             QString icon,
             Character* pchar,
             bool restricted_by_gcd,
             double cooldown,
             const ResourceType resource_type,
             int resource_cost) :
    name(std::move(name)),
    icon(std::move(icon)),
    pchar(pchar),
    engine(pchar->get_engine()),
    roll(pchar->get_combat_roll()),
    statistics_spell(nullptr),
    restricted_by_gcd(restricted_by_gcd),
    cooldown(cooldown),
    last_used(0 - cooldown),
    resource_type(resource_type),
    resource_cost(resource_cost),
    spell_rank(0),
    instance_id(SpellStatus::INACTIVE),
    enabled(true)
{}

QString Spell::get_name() const {
    return this->name;
}

double Spell::get_base_cooldown() {
    return this->cooldown;
}

double Spell::get_last_used() {
    return this->last_used;
}

double Spell::get_next_use() const {
    return last_used + cooldown;
}

bool Spell::is_ready() const {
    if (restricted_by_gcd && pchar->on_global_cooldown())
        return false;

    if (!is_ready_spell_specific())
        return false;

    return (get_next_use() - engine->get_current_priority()) < 0.0001;
}

bool Spell::is_ready_spell_specific() const {
    return true;
}

void Spell::enable_spell_effect() {

}

void Spell::disable_spell_effect() {

}

bool Spell::is_available() const {
    return enabled && is_ready() && static_cast<int>(pchar->get_resource_level(resource_type)) >= this->resource_cost;
}

bool Spell::is_enabled() const {
    return enabled;
}

void Spell::enable() {
    assert(enabled == false);
    enabled = true;
    enable_spell_effect();
}

void Spell::disable() {
    if (enabled)
        disable_spell_effect();

    enabled = false;
}

double Spell::get_cooldown_remaining() const {
    double delta = last_used + cooldown - engine->get_current_priority();

    return delta > 0 ? delta : 0;
}

void Spell::increase_spell_rank() {
    ++spell_rank;
}

void Spell::decrease_spell_rank() {
    --spell_rank;
}

void Spell::perform() {
    assert(static_cast<int>(pchar->get_resource_level(resource_type)) >= resource_cost);
    last_used = engine->get_current_priority();
    this->spell_effect();
}

void Spell::add_spell_cd_event() const {
    double cooldown_ready = engine->get_current_priority() + cooldown;
    auto* new_event = new CooldownReady(pchar->get_rotation(), cooldown_ready);
    engine->add_event(new_event);
}

void Spell::add_gcd_event() const {
    pchar->start_global_cooldown();
    double gcd_ready = engine->get_current_priority() + pchar->global_cooldown();
    auto* new_event = new CooldownReady(pchar->get_rotation(), gcd_ready);
    engine->add_event(new_event);
}

void Spell::increment_miss() {
    statistics_spell->increment_miss();
}

void Spell::increment_full_resist() {
    statistics_spell->increment_full_resist();
}

void Spell::increment_dodge() {
    statistics_spell->increment_dodge();
}

void Spell::increment_parry() {
    statistics_spell->increment_parry();
}

void Spell::increment_full_block() {
    statistics_spell->increment_full_block();
}

void Spell::add_partial_resist_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_partial_resist_dmg(damage, resource_cost, execution_time);
}

void Spell::add_partial_block_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_partial_block_dmg(damage, resource_cost, execution_time);
}

void Spell::add_partial_block_crit_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_partial_block_crit_dmg(damage, resource_cost, execution_time);
}

void Spell::add_glancing_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_glancing_dmg(damage, resource_cost, execution_time);
}

void Spell::add_hit_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_hit_dmg(damage, resource_cost, execution_time);
}

void Spell::add_crit_dmg(const int damage, const int resource_cost, const double execution_time) {
    statistics_spell->add_crit_dmg(damage, resource_cost, execution_time);
}

double Spell::damage_after_modifiers(const double damage) const {
    double armor_reduction = 1 - roll->get_mechanics()->get_reduction_from_armor(pchar->get_target()->get_armor(), pchar->get_clvl());
    return damage * pchar->get_stats()->get_total_phys_dmg_mod() * armor_reduction;
}

double Spell::get_partial_resist_dmg_modifier(const int resist_result) const {
    switch (resist_result) {
    case MagicResistResult::FULL_RESIST:
        return 0.0;
    case MagicResistResult::PARTIAL_RESIST_75:
        return 0.25;
    case MagicResistResult::PARTIAL_RESIST_50:
        return 0.5;
    case MagicResistResult::PARTIAL_RESIST_25:
        return 0.75;
    case MagicResistResult::NO_RESIST:
        return 1.0;
    default:
        assert(false);
    }

    return 0.0;
}

void Spell::reset() {
    last_used = 0 - cooldown;
    reset_effect();
}

void Spell::prepare_set_of_combat_iterations() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(name, icon);
    prepare_set_of_combat_iterations_spell_specific();
}

StatisticsSpell* Spell::get_statistics_for_spell() const {
    return this->statistics_spell;
}

int Spell::get_instance_id() const {
    return this->instance_id;
}

void Spell::set_instance_id(const int instance_id) {
    this->instance_id = instance_id;
}

void Spell::prepare_set_of_combat_iterations_spell_specific() {

}

void Spell::reset_effect() {

}

void Spell::perform_periodic() {

}

void Spell::perform_pre_combat() {

}
