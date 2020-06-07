#include "CharacterSpells.h"

#include <algorithm>

#include "Berserking.h"
#include "BloodFury.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "DemonicRune.h"
#include "DragonbreathChili.h"
#include "EnabledBuffs.h"
#include "Engine.h"
#include "Equipment.h"
#include "EssenceOfTheRed.h"
#include "MainhandAttack.h"
#include "ManaPotion.h"
#include "NightDragonsBreath.h"
#include "OffhandAttack.h"
#include "OffhandMeleeHit.h"
#include "Pet.h"
#include "Race.h"
#include "RaidControl.h"
#include "Rotation.h"
#include "SpellRankGroup.h"
#include "Target.h"
#include "Utils/Check.h"

CharacterSpells::CharacterSpells(Character* pchar) :
    pchar(pchar),
    rotation(nullptr),
    cast_is_in_progress(false),
    id_of_cast_in_progress(0),
    attack_mode(AttackMode::MeleeAttack),
    attack_mode_active(false) {
    blood_fury = new BloodFury(pchar);
    demonic_rune = new DemonicRune(pchar);
    mana_potion = new ManaPotion(pchar);
    night_dragons_breath = new NightDragonsBreath(pchar);
    dragonbreath_chili = new DragonbreathChili(pchar);

    add_spell_group({blood_fury});
    add_spell_group({demonic_rune});
    add_spell_group({mana_potion});
    add_spell_group({night_dragons_breath});
    add_spell_group({new EssenceOfTheRed(pchar)});
}

CharacterSpells::~CharacterSpells() {
    for (const auto& spell : spells)
        delete spell;

    for (const auto& cc : cooldown_controls)
        delete cc;

    for (const auto& spell_group : spell_rank_groups)
        delete spell_group;

    delete dragonbreath_chili;
}

void CharacterSpells::set_rotation(Rotation* rotation) {
    this->rotation = rotation;
    this->pchar->set_rotation_name(rotation->get_name());
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
        if (pchar->get_pet())
            pchar->get_pet()->increase_damage_modifier(5);
        break;
    case Races::Troll:
        berserking->enable();
        pchar->get_stats()->increase_dmg_vs_type(Target::CreatureType::Beast, 0.05);
        break;
    }
}

void CharacterSpells::deactivate_racials() {
    switch (pchar->get_race()->get_race_int()) {
    case Races::Orc:
        blood_fury->disable();
        if (pchar->get_pet())
            pchar->get_pet()->decrease_damage_modifier(5);
        break;
    case Races::Troll:
        berserking->disable();
        pchar->get_stats()->decrease_dmg_vs_type(Target::CreatureType::Beast, 0.05);
        break;
    }
}

void CharacterSpells::add_spell(Spell* spell, bool relink) {
    if (spell->get_instance_id() == InstanceID::INACTIVE)
        spell->set_instance_id(pchar->get_raid_control()->next_instance_id());

    spells.append(spell);

    if (relink)
        relink_spells();
}

void CharacterSpells::remove_spell(Spell* spell) {
    QVector<Spell*>::iterator it = std::find(spells.begin(), spells.end(), spell);
    if (it == spells.end())
        return;

    spell_rank_groups.remove(spell->get_name());
    spells.erase(it);

    relink_spells();
}

void CharacterSpells::add_start_of_combat_spell(Spell* spell) {
    if (spell->get_instance_id() == InstanceID::INACTIVE)
        spell->set_instance_id(pchar->get_raid_control()->next_instance_id());

    start_of_combat_spells.append(spell);
}

void CharacterSpells::remove_start_of_combat_spell(Spell* spell) {
    QVector<Spell*>::iterator it = std::find(spells.begin(), spells.end(), spell);
    if (it != spells.end())
        spells.erase(it);
}

void CharacterSpells::run_start_of_combat_spells() {
    for (const auto& spell : start_of_combat_spells)
        spell->perform_start_of_combat();
}

void CharacterSpells::add_spell_group(const QVector<Spell*> spell_group, const bool relink) {
    check(!spell_group.empty(), "Cannot add empty spell group");
    check(!spell_rank_groups.contains(spell_group[0]->get_name()),
          QString("%1 has already been added as a spell group").arg(spell_group[0]->get_name()).toStdString());

    spell_rank_groups[spell_group[0]->get_name()] = new SpellRankGroup(spell_group[0]->get_name(), spell_group);

    for (auto& spell : spell_group)
        add_spell(spell, relink);
}

SpellRankGroup* CharacterSpells::get_spell_rank_group_by_name(const QString& spell_name) const {
    if (spell_rank_groups.contains(spell_name))
        return spell_rank_groups[spell_name];

    return nullptr;
}

Buff* CharacterSpells::get_buff_by_name(const QString& name) const {
    Buff* buff = pchar->get_enabled_buffs()->get_buff_by_name(name);
    if (buff != nullptr)
        return buff;

    buff = pchar->get_raid_control()->get_shared_party_buff(name, pchar->get_party());
    if (buff != nullptr)
        return buff;

    return pchar->get_raid_control()->get_shared_raid_buff(name);
}

void CharacterSpells::reset() {
    cast_is_in_progress = false;
    id_of_cast_in_progress = 0;
    attack_mode_active = false;

    for (const auto& spell : spells)
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
    if (!pchar->get_equipment()->get_mainhand())
        return;

    add_next_mh_attack();

    if (pchar->is_dual_wielding()) {
        add_next_oh_attack();
    }
}

void CharacterSpells::start_pet_attack() {}

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

AttackMode CharacterSpells::get_attack_mode() const {
    return this->attack_mode;
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
    if (attack_mode != AttackMode::MeleeAttack)
        return;

    mh_attack->add_next_mh_attack();
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

DragonbreathChili* CharacterSpells::get_dragonbreath_chili() const {
    return this->dragonbreath_chili;
}

CooldownControl* CharacterSpells::new_cooldown_control(const QString& spell_name, const double cooldown) {
    if (cooldown_controls.contains(spell_name))
        return cooldown_controls[spell_name];

    const auto new_cc = new CooldownControl(pchar, cooldown);
    cooldown_controls[spell_name] = new_cc;
    return new_cc;
}

void CharacterSpells::prepare_set_of_combat_iterations_class_specific() {}

void CharacterSpells::prepare_set_of_combat_iterations() {
    cast_is_in_progress = false;
    id_of_cast_in_progress = 0;
    attack_mode_active = false;

    for (const auto& spell : spells)
        spell->prepare_set_of_combat_iterations();

    if (rotation)
        rotation->prepare_set_of_combat_iterations();

    prepare_set_of_combat_iterations_class_specific();
}
