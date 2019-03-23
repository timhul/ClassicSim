#include "CharacterSpells.h"

#include "Berserking.h"
#include "BloodFury.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandAttack.h"
#include "OffhandMeleeHit.h"
#include "Race.h"
#include "Rotation.h"
#include "Target.h"
#include "Utils/Check.h"

CharacterSpells::CharacterSpells(Character* pchar) :
    pchar(pchar),
    rotation(nullptr),
    cast_is_in_progress(false),
    id_of_cast_in_progress(0),
    attack_mode(AttackMode::MeleeAttack),
    attack_mode_active(false),
    next_instance_id(SpellStatus::INITIAL_ID)
{
    berserking = new Berserking(pchar);
    blood_fury = new BloodFury(pchar);
    spells = {berserking, blood_fury};
}

CharacterSpells::~CharacterSpells()
{
    for (auto & spell : spells)
        delete spell;

    spells.clear();
    pre_combat_spells.clear();
}

void CharacterSpells::set_rotation(Rotation* rotation) {
    this->rotation = rotation;
    this->rotation->link_spells(pchar);
    set_attack_mode(this->rotation->get_attack_mode());
}

void CharacterSpells::relink_spells() {
    if (rotation != nullptr)
        rotation->link_spells(pchar);
}

void CharacterSpells::perform_rotation() {
    if (rotation == nullptr || cast_is_in_progress)
        return;

    this->rotation->perform_rotation();
}

Rotation* CharacterSpells::get_rotation() {
    return this->rotation;
}

bool CharacterSpells::cast_in_progress() const {
    return this->cast_is_in_progress;
}

unsigned CharacterSpells::start_cast() {
    check(!cast_is_in_progress, "Cast in progress when starting new cast");

    cast_is_in_progress = true;

    return ++id_of_cast_in_progress;
}

void CharacterSpells::complete_cast(const unsigned cast_id) {
    check(cast_is_in_progress, "Cast not in progress when completing cast");
    check((id_of_cast_in_progress == cast_id), "Mismatched cast id");

    cast_is_in_progress = false;

    pchar->add_player_reaction_event();
}

void CharacterSpells::activate_racials() {
    switch (pchar->get_race()->get_race_int()) {
    case Races::Orc:
        blood_fury->enable();
        break;
    case Races::Troll:
        berserking->enable();
        if (pchar->get_target()->get_creature_type() == Target::CreatureType::Beast)
            pchar->get_stats()->increase_total_phys_dmg_mod(5);
        break;
    }
}

void CharacterSpells::deactivate_racials() {
    switch (pchar->get_race()->get_race_int()) {
    case Races::Orc:
        blood_fury->disable();
        break;
    case Races::Troll:
        berserking->disable();
        if (pchar->get_target()->get_creature_type() == Target::CreatureType::Beast)
            pchar->get_stats()->decrease_total_phys_dmg_mod(5);
        break;
    }
}

void CharacterSpells::add_spell(Spell* spell, bool relink) {
    if (spell->get_instance_id() == SpellStatus::INACTIVE) {
        spell->set_instance_id(next_instance_id);
        ++next_instance_id;
    }

    spells.append(spell);

    if (relink)
        relink_spells();
}

void CharacterSpells::remove_spell(Spell* spell) {
    for (auto & i : spells) {
        if (i->get_instance_id() == spell->get_instance_id()) {
            spells.removeOne(i);
            break;
        }
    }
    relink_spells();
}

void CharacterSpells::add_pre_combat_spell(Spell* spell) {
    if (spell->get_instance_id() == SpellStatus::INACTIVE) {
        spell->set_instance_id(next_instance_id);
        ++next_instance_id;
    }

    pre_combat_spells.append(spell);
}

void CharacterSpells::remove_pre_combat_spell(Spell* spell) {
    for (auto & i : pre_combat_spells) {
        if (i->get_instance_id() == spell->get_instance_id()) {
            pre_combat_spells.removeOne(i);
            return;
        }
    }
}

void CharacterSpells::run_pre_combat_spells() {
    for (auto & spell : pre_combat_spells)
        spell->perform_pre_combat();
}

Spell* CharacterSpells::get_spell_by_name(const QString& spell_name) const {
    for (auto & spell : spells) {
        if (spell->get_name() == spell_name)
            return spell;
    }

    return nullptr;
}

void CharacterSpells::reset() {
    cast_is_in_progress = false;
    id_of_cast_in_progress = 0;
    attack_mode_active = false;

    for (auto & spell : spells)
        spell->reset();
}

void CharacterSpells::start_attack() {
    attack_mode_active = true;

    switch (attack_mode) {
    case AttackMode::MeleeAttack:
        return start_melee_attack();
    case AttackMode::RangedAttack:
        return add_next_ranged_attack();
    default:
        return;
    }
}

void CharacterSpells::start_melee_attack() {
    add_next_mh_attack();

    if (pchar->is_dual_wielding()) {
        add_next_oh_attack();
    }
}

void CharacterSpells::stop_attack() {
    attack_mode_active = false;
}

bool CharacterSpells::is_melee_attacking() const {
    return attack_mode == AttackMode::MeleeAttack && attack_mode_active;
}

bool CharacterSpells::is_ranged_attacking() const {
    return attack_mode == AttackMode::RangedAttack && attack_mode_active;
}

void CharacterSpells::set_attack_mode(const AttackMode attack_mode) {
    check(!attack_mode_active, "Attack mode active when setting new attack mode");
    this->attack_mode = attack_mode;
}

void CharacterSpells::mh_auto_attack(const int iteration) {
    if (!mh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    mh_attack->perform();

    add_next_mh_attack();
}

void CharacterSpells::add_next_mh_attack() {
    auto* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void CharacterSpells::oh_auto_attack(const int) {
    check(false, "Not implemented");
}

void CharacterSpells::add_next_oh_attack() {
    check(false, "Not implemented");
}

void CharacterSpells::ranged_auto_attack(const int) {
    check(false, "Not implemented");
}

void CharacterSpells::add_next_ranged_attack() {
    check(false, "Not implemented");
}

MainhandAttack* CharacterSpells::get_mh_attack() const {
    return this->mh_attack;
}

OffhandAttack* CharacterSpells::get_oh_attack() const {
    check(false, "Not implemented");
    return nullptr;
}

AutoShot* CharacterSpells::get_auto_shot() const {
    return nullptr;
}

Berserking* CharacterSpells::get_berserking() const {
    return this->berserking;
}

BloodFury* CharacterSpells::get_blood_fury() const {
    return this->blood_fury;
}

void CharacterSpells::prepare_set_of_combat_iterations() {
    cast_is_in_progress = false;
    id_of_cast_in_progress = 0;
    attack_mode_active = false;

    for (auto & spell : spells)
        spell->prepare_set_of_combat_iterations();
}
