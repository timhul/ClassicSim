
#include "Spell.h"
#include "Character.h"
#include "StatisticsSpell.h"

Spell::Spell(QString _name, Engine* _eng, Character* _pchar, CombatRoll* _roll,
             float _cd, int _cost) :
    name(_name),
    engine(_eng),
    pchar(_pchar),
    roll(_roll),
    statistics(new StatisticsSpell(name)),
    cooldown(_cd),
    last_used(0 - _cd),
    resource_cost(_cost),
    rank_talent(0),
    rank_spell(0)
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

float Spell::get_cooldown() {
    return this->cooldown;
}

float Spell::get_last_used() {
    return this->last_used;
}

float Spell::get_next_use() const {
    return last_used + cooldown;
}

bool Spell::is_ready() const {
    return cooldown_less_than(0);
}

bool Spell::is_available(const int resource_level) const {
    return is_ready() && resource_level >= this->resource_cost;
}

bool Spell::is_enabled() const {
    return rank_talent > 0;
}

bool Spell::cooldown_less_than(const float value) const {
    const float curr = engine->get_current_priority();
    float target_timestamp = curr + value;

    float delta = get_next_use() - target_timestamp;
    if (delta < 0.0001)
        return true;

    return target_timestamp >= get_next_use();
}

bool Spell::cooldown_greater_than(const float value) const {
    // Note that this function actually returns GEQ and not greater.
    return !cooldown_less_than(value);
}

void Spell::increase_effect_via_talent() {
    ++rank_talent;
    // TODO: Assert max rank?
}

void Spell::decrease_effect_via_talent() {
    --rank_talent;
    assert(rank_talent >= 0);
}

void Spell::increase_spell_rank() {
    ++rank_spell;
}

void Spell::decrease_spell_rank() {
    --rank_spell;
}

int Spell::perform(const int resource_level) {
    assert(resource_level >= resource_cost);
    last_used = engine->get_current_priority();
    return this->spell_effect(resource_level);
}

void Spell::add_spell_cd_event(void) const {
    float cooldown_ready = engine->get_current_priority() + cooldown;
    CooldownReady* new_event = new CooldownReady(pchar->get_spells(), cooldown_ready);
    engine->add_event(new_event);
}

void Spell::add_gcd_event(void) const {
    pchar->start_global_cooldown();
    float gcd_ready = engine->get_current_priority() + pchar->global_cooldown();
    CooldownReady* new_event = new CooldownReady(pchar->get_spells(), gcd_ready);
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

void Spell::reset() {
    last_used = 0 - cooldown;
    reset_effect();
}

void Spell::reset_effect() {

}

void Spell::periodic_effect() {

}
