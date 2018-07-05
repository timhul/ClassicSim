
#include "Spell.h"
#include "Character.h"
#include "StatisticsSpell.h"

Spell::Spell(QString name, Engine* engine, Character* pchar, CombatRoll* roll,
             bool restricted_by_gcd, float cooldown, int resource_cost) :
    name(name),
    engine(engine),
    pchar(pchar),
    roll(roll),
    statistics(new StatisticsSpell(name)),
    restricted_by_gcd(restricted_by_gcd),
    cooldown(cooldown),
    last_used(0 - cooldown),
    resource_cost(resource_cost),
    rank_talent(0),
    rank_spell(0),
    enabled_by_talent(false)
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

float Spell::get_base_cooldown() {
    return this->cooldown;
}

float Spell::get_last_used() {
    return this->last_used;
}

float Spell::get_next_use() const {
    return last_used + cooldown;
}

bool Spell::is_ready() const {
    // TODO: Check stance cd if spell restricted by stance cd
    if (restricted_by_gcd && pchar->on_global_cooldown())
        return false;

    if (is_ready_spell_specific() == false)
        return false;

    return (get_next_use() - engine->get_current_priority()) < 0.0001;
}

bool Spell::is_ready_spell_specific() const {
    return true;
}

bool Spell::is_available() const {
    return is_enabled() && is_ready() && pchar->get_resource_level() >= this->resource_cost;
}

bool Spell::is_enabled() const {
    return enabled_by_talent ? rank_talent > 0 : true;
}

float Spell::get_cooldown_remaining() const {
    float delta = last_used + cooldown - engine->get_current_priority();

    return delta > 0 ? delta : 0;
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

void Spell::perform() {
    assert(pchar->get_resource_level() >= resource_cost);
    last_used = engine->get_current_priority();
    this->spell_effect();
}

void Spell::add_spell_cd_event(void) const {
    float cooldown_ready = engine->get_current_priority() + cooldown;
    CooldownReady* new_event = new CooldownReady(pchar->get_rotation(), cooldown_ready);
    engine->add_event(new_event);
}

void Spell::add_gcd_event(void) const {
    pchar->start_global_cooldown();
    float gcd_ready = engine->get_current_priority() + pchar->global_cooldown();
    CooldownReady* new_event = new CooldownReady(pchar->get_rotation(), gcd_ready);
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
