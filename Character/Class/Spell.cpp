
#include "Spell.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Target.h"
#include "StatisticsSpell.h"
#include "Mechanics.h"

Spell::Spell(const QString& name,
             Character* pchar,
             bool restricted_by_gcd,
             double cooldown, int
             resource_cost) :
    name(name),
    pchar(pchar),
    engine(pchar->get_engine()),
    roll(pchar->get_combat_roll()),
    statistics(new StatisticsSpell(name)),
    restricted_by_gcd(restricted_by_gcd),
    cooldown(cooldown),
    last_used(0 - cooldown),
    resource_cost(resource_cost),
    rank_talent(0),
    rank_spell(0),
    is_enabled_externally(false),
    enabled(true)
{}

Spell::~Spell() {
    delete statistics;
}

StatisticsSpell* Spell::get_statistics_for_spell() const {
    return statistics;
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
    assert(is_enabled_externally);
    assert(enabled == false);
    enabled = true;
    enable_spell_effect();
}

void Spell::disable() {
    assert(is_enabled_externally);
    if (enabled)
        disable_spell_effect();

    enabled = false;
}

double Spell::get_cooldown_remaining() const {
    double delta = last_used + cooldown - engine->get_current_priority();

    return delta > 0 ? delta : 0;
}

void Spell::increase_effect_via_talent() {
    ++rank_talent;
    if (is_enabled_externally && !enabled)
        enabled = true;
}

void Spell::decrease_effect_via_talent() {
    --rank_talent;
    assert(rank_talent >= 0);
    if (is_enabled_externally && enabled && rank_talent == 0)
        enabled = false;
}

void Spell::increase_spell_rank() {
    ++rank_spell;
}

void Spell::decrease_spell_rank() {
    --rank_spell;
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
    statistics->increment_miss();
}

void Spell::increment_full_resist() {
    statistics->increment_full_resist();
}

void Spell::increment_dodge() {
    statistics->increment_dodge();
}

void Spell::increment_parry() {
    statistics->increment_parry();
}

void Spell::increment_full_block() {
    statistics->increment_full_block();
}

void Spell::add_partial_resist_dmg(const int damage) {
    statistics->add_partial_resist_dmg(damage);
    statistics->increment_partial_resist();
}

void Spell::add_partial_block_dmg(const int damage) {
    statistics->add_partial_block_dmg(damage);
    statistics->increment_partial_block();
}

void Spell::add_partial_block_crit_dmg(const int damage) {
    statistics->add_partial_block_crit_dmg(damage);
    statistics->increment_partial_block_crit();
}

void Spell::add_glancing_dmg(const int damage) {
    statistics->add_glancing_dmg(damage);
    statistics->increment_glancing();
}

void Spell::add_hit_dmg(const int damage) {
    statistics->add_hit_dmg(damage);
    statistics->increment_hit();
}

void Spell::add_crit_dmg(const int damage) {
    statistics->add_crit_dmg(damage);
    statistics->increment_crit();
}

double Spell::damage_after_modifiers(const double damage) const {
    double armor_reduction = 1 - roll->get_mechanics()->get_reduction_from_armor(pchar->get_target()->get_armor(), pchar->get_clvl());
    return damage * pchar->get_stats()->get_total_phys_dmg_mod() * armor_reduction;
}

void Spell::reset() {
    last_used = 0 - cooldown;
    reset_effect();
}

void Spell::reset_effect() {

}

void Spell::perform_periodic() {

}
