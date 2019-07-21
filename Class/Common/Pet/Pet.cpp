#include "Pet.h"

#include <cmath>

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Engine.h"
#include "PetAction.h"
#include "PetAutoAttack.h"
#include "PetMeleeHit.h"
#include "Random.h"
#include "Spell.h"
#include "Utils/CompareDouble.h"

Pet::Pet(Character* pchar, const QString& name, double attack_speed, double base_dps) :
    pchar(pchar),
    resource(nullptr),
    name(name),
    base_attack_speed(attack_speed),
    base_dps(base_dps),
    min(static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 0.9))),
    max(static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 1.1))),
    normalized_dmg_roll(new Random(min, max)),
    global_cooldown(1.5),
    next_gcd(0.0),
    is_attacking(false),
    crit_chance(500),
    attack_speed_modifier(1.0),
    damage_modifier(1.0),
    pet_auto_attack(nullptr)
{}

Pet::~Pet() {
    remove_spells();

    for (const auto & spell: spells)
        delete spell;

    delete pet_auto_attack;
    delete normalized_dmg_roll;
}

QString Pet::get_name() const {
    return this->name;
}

void Pet::lose_resource(const unsigned loss) {
    this->resource->lose_resource(loss);
}

void Pet::start_attack() {
    if (is_attacking)
        return;

    this->is_attacking = true;

    pet_auto_attack->perform();
    add_next_auto_attack();

    use_resource();
}

void Pet::add_gcd_event() {
    next_gcd =  pchar->get_engine()->get_current_priority() + global_cooldown;
    auto* new_event = new PetAction(this, next_gcd);
    pchar->get_engine()->add_event(new_event);
}

void Pet::add_pet_reaction() {
    pchar->get_engine()->add_event(new PetAction(this, pchar->get_engine()->get_current_priority() + 0.1));
}

bool Pet::action_ready() {
    return lhs_almost_equal_or_less(next_gcd, pchar->get_engine()->get_current_priority());
}

void Pet::auto_attack(const int iteration) {
    if (!pet_auto_attack->attack_is_valid(iteration))
        return;

    pet_auto_attack->perform();

    add_next_auto_attack();
}

double Pet::get_attack_speed() const {
    return base_attack_speed / this->attack_speed_modifier;
}

void Pet::increase_attack_speed(const unsigned increase) {
    CharacterStats::add_multiplicative_effect(attack_speed_modifiers, static_cast<int>(increase), attack_speed_modifier);

    double increase_double = double(increase) / 100;
    pet_auto_attack->update_next_expected_use(increase_double);
    add_next_auto_attack();
}

void Pet::decrease_attack_speed(const unsigned decrease) {
    CharacterStats::remove_multiplicative_effect(attack_speed_modifiers, static_cast<int>(decrease), attack_speed_modifier);

    double decrease_double = double(decrease) / 100;
    pet_auto_attack->update_next_expected_use(-decrease_double);
    add_next_auto_attack();
}

double Pet::get_damage_modifier() const {
    return this->damage_modifier;
}

void Pet::increase_damage_modifier(const unsigned increase) {
    CharacterStats::add_multiplicative_effect(damage_modifiers, static_cast<int>(increase), damage_modifier);
}

void Pet::decrease_damage_modifier(const unsigned decrease) {
    CharacterStats::remove_multiplicative_effect(damage_modifiers, static_cast<int>(decrease), damage_modifier);
}

unsigned Pet::get_crit_chance() const {
    return this->crit_chance;
}

void Pet::increase_crit_chance(const unsigned increase) {
    this->crit_chance += increase;
}

void Pet::decrease_crit_chance(const unsigned decrease) {
    this->crit_chance -= decrease;
}

unsigned Pet::get_min_dmg() const {
    return this->min;
}

unsigned Pet::get_max_dmg() const {
    return this->max;
}

void Pet::increase_attack_power(const unsigned increase) {
    attack_power += increase;

    min = static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 0.9));
    max = static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 1.1));

    normalized_dmg_roll->set_new_range(min, max);
}

void Pet::decrease_attack_power(const unsigned decrease) {
    attack_power -= decrease;

    min = static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 0.9));
    max = static_cast<unsigned>(round((base_dps + attack_power / 14 * base_attack_speed) * 1.1));

    normalized_dmg_roll->set_new_range(min, max);
}

unsigned Pet::get_random_normalized_dmg() {
    return normalized_dmg_roll->get_roll();
}

void Pet::melee_critical_effect() {

}

void Pet::reset() {
    this->is_attacking = false;
    this->next_gcd = 0.0;
    this->resource->reset_resource();
}

Resource* Pet::get_resource() {
    return this->resource;
}

void Pet::add_next_auto_attack() {
    auto* new_event = new PetMeleeHit(this, pet_auto_attack->get_next_iteration(), pet_auto_attack->get_next_expected_use());
    pchar->get_engine()->add_event(new_event);
}

void Pet::add_spells() {
    pchar->get_spells()->add_spell_group({pet_auto_attack});

    for (const auto & spell : spells)
        pchar->get_spells()->add_spell_group({spell});
}

void Pet::remove_spells() {
    pchar->get_spells()->remove_spell(pet_auto_attack);

    for (const auto & spell : spells)
        pchar->get_spells()->remove_spell(spell);
}
