
#include "Spell.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "Target.h"
#include "StatisticsSpell.h"
#include "Mechanics.h"
#include "Spells.h"

Spell::Spell(const QString& name,
             const QString& icon,
             Character* pchar,
             bool restricted_by_gcd,
             double cooldown, int
             resource_cost) :
    name(name),
    icon(icon),
    pchar(pchar),
    engine(pchar->get_engine()),
    roll(pchar->get_combat_roll()),
    statistics_spell(nullptr),
    restricted_by_gcd(restricted_by_gcd),
    cooldown(cooldown),
    last_used(0 - cooldown),
    resource_cost(resource_cost),
    spell_rank(0),
    instance_id(SpellStatus::INACTIVE),
    enabled(true)
{}

Spell::~Spell() {
}

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
    return enabled && is_ready() && static_cast<int>(pchar->get_resource_level()) >= this->resource_cost;
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
    assert(static_cast<int>(pchar->get_resource_level()) >= resource_cost);
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

void Spell::add_partial_resist_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_partial_resist_dmg(damage, resource_cost);
}

void Spell::add_partial_block_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_partial_block_dmg(damage, resource_cost);
}

void Spell::add_partial_block_crit_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_partial_block_crit_dmg(damage, resource_cost);
}

void Spell::add_glancing_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_glancing_dmg(damage, resource_cost);
}

void Spell::add_hit_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_hit_dmg(damage, resource_cost);
}

void Spell::add_crit_dmg(const int damage, const int resource_cost) {
    statistics_spell->add_crit_dmg(damage, resource_cost);
}

double Spell::damage_after_modifiers(const double damage) const {
    double armor_reduction = 1 - roll->get_mechanics()->get_reduction_from_armor(pchar->get_target()->get_armor(), pchar->get_clvl());
    return damage * pchar->get_stats()->get_total_phys_dmg_mod() * armor_reduction;
}

void Spell::reset() {
    last_used = 0 - cooldown;
    reset_effect();
}

void Spell::prepare_set_of_combat_iterations() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(name, icon);
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

void Spell::reset_effect() {

}

void Spell::perform_periodic() {

}
