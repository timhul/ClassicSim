#include "Rotation.h"

#include <utility>

#include <QDebug>

#include "CastingTimeRequirer.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "ClassStatistics.h"
#include "ConditionBuffDuration.h"
#include "ConditionBuffStacks.h"
#include "ConditionResource.h"
#include "ConditionSpell.h"
#include "ConditionVariableBuiltin.h"
#include "EnabledBuffs.h"
#include "RaidControl.h"
#include "RotationExecutor.h"
#include "Spell.h"
#include "SpellRankGroup.h"
#include "Utils/Check.h"

Rotation::Rotation(QString class_name) : pchar(nullptr), class_name(std::move(class_name)), attack_mode(AttackMode::MeleeAttack) {}

Rotation::~Rotation() {
    for (const auto& executor : all_executors) {
        delete executor;
    }
}

void Rotation::run_precombat_actions() {
    QSet<int> acceptable_status {static_cast<int>(SpellStatus::Available), static_cast<int>(SpellStatus::OnCooldown)};
    for (const auto& spell : precombat_spells) {
        if (acceptable_status.contains(static_cast<int>(spell->get_spell_status())))
            spell->perform();
    }
}

void Rotation::perform_rotation() const {
    for (const auto& executor : active_executors)
        executor->attempt_cast();
}

void Rotation::prepare_set_of_combat_iterations() {
    for (const auto& executor : active_executors)
        executor->prepare_set_of_combat_iterations(pchar->get_statistics()->get_executor_statistics(executor->get_spell_name()));
}

void Rotation::finish_set_of_combat_iterations() {
    for (const auto& executor : active_executors)
        executor->finish_set_of_combat_iterations();
}

void Rotation::link_spells(Character* pchar) {
    this->pchar = pchar;

    active_executors.clear();

    for (const auto& executor : all_executors) {
        SpellRankGroup* spell_group = pchar->get_spells()->get_spell_rank_group_by_name(executor->get_spell_name());

        if (spell_group == nullptr)
            continue;

        Spell* spell = spell_group->get_spell_rank(executor->get_spell_rank());

        if (spell == nullptr || !spell->is_enabled())
            continue;

        executor->set_spell(spell);

        if (this->add_conditionals(executor))
            active_executors.append(executor);
    }

    link_precast_spell();
    link_precombat_spells();
}

void Rotation::link_precast_spell() {
    SpellRankGroup* spell_group = pchar->get_spells()->get_spell_rank_group_by_name(precast_spell_name);

    if (spell_group == nullptr)
        return;

    // TODO: Doesn't have to be max rank, could include "rank" attribute on element.
    Spell* spell = spell_group->get_max_available_spell_rank();

    if (dynamic_cast<CastingTimeRequirer*>(spell) == nullptr)
        return;

    precast_spell = spell;
}

void Rotation::link_precombat_spells() {
    precombat_spells.clear();

    for (const auto& spell_name : precombat_spell_names) {
        SpellRankGroup* spell_group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);

        if (spell_group == nullptr)
            return;

        // TODO: Doesn't have to be max rank, could include "rank" attribute on element.
        Spell* spell = spell_group->get_max_available_spell_rank();

        if (spell == nullptr || !spell->is_enabled())
            continue;

        precombat_spells.append(spell);
    }
}

bool Rotation::add_conditionals(RotationExecutor* executor) {
    for (const auto& group : executor->condition_groups)
        for (const auto& condition : group)
            delete condition;
    executor->condition_groups.clear();

    QVector<Condition*> condition_group_to_add;

    for (const auto& sentence : executor->sentences) {
        Condition* condition = nullptr;

        if (sentence->logical_connective == LogicalConnective::OR) {
            check((condition_group_to_add.empty() == false), "Cannot use OR conditional at start");
            executor->add_condition(condition_group_to_add);
            condition_group_to_add.clear();
        }

        switch (sentence->condition_type) {
        case ConditionType::BuffStacksCondition: {
            Buff* buff = pchar->get_spells()->get_buff_by_name(sentence->type_value);
            if (buff == nullptr) {
                return false;
            }
            condition = new ConditionBuffStacks(buff, sentence->mathematical_symbol, sentence->compared_value.toInt());
            break;
        }
        case ConditionType::BuffDurationCondition: {
            Buff* buff = pchar->get_spells()->get_buff_by_name(sentence->type_value);
            if (buff == nullptr) {
                return false;
            }
            condition = new ConditionBuffDuration(buff, sentence->mathematical_symbol, sentence->compared_value.toDouble());
            break;
        }
        case ConditionType::SpellCondition:
            condition = new ConditionSpell(pchar->get_spells()->get_spell_rank_group_by_name(sentence->type_value)->get_max_available_spell_rank(),
                                           sentence->mathematical_symbol, sentence->compared_value.toDouble());
            break;
        case ConditionType::ResourceCondition:
            condition = new ConditionResource(this->pchar, sentence->mathematical_symbol, get_resource_from_string(sentence->type_value),
                                              sentence->compared_value.toDouble());
            break;
        case ConditionType::VariableBuiltinCondition:
            if (ConditionVariableBuiltin::get_builtin_variable(sentence->type_value) == BuiltinVariables::Undefined)
                break;
            condition = new ConditionVariableBuiltin(this->pchar, ConditionVariableBuiltin::get_builtin_variable(sentence->type_value),
                                                     sentence->mathematical_symbol, sentence->compared_value.toDouble());
            break;
        }

        condition_group_to_add.append(condition);
    }

    // Add last condition manually
    if (!condition_group_to_add.empty())
        executor->add_condition(condition_group_to_add);

    return true;
}

double Rotation::get_time_required_to_run_precombat() {
    return precast_spell ? dynamic_cast<CastingTimeRequirer*>(precast_spell)->get_cast_time() : pchar->global_cooldown();
}

void Rotation::set_name(const QString& name) {
    this->name = name;
}

void Rotation::set_description(const QString& desc) {
    this->description = desc;
}

bool Rotation::try_set_attack_mode(const QString& value) {
    if (value == "melee")
        attack_mode = AttackMode::MeleeAttack;
    else if (value == "ranged")
        attack_mode = AttackMode::RangedAttack;
    else if (value == "magic")
        attack_mode = AttackMode::MagicAttack;
    else
        return false;

    return true;
}

void Rotation::add_precombat_spell(const QString& spell_name) {
    this->precombat_spell_names.append(spell_name);
}

void Rotation::add_precast_spell(const QString& spell_name) {
    this->precast_spell_name = spell_name;
}

void Rotation::add_executor(RotationExecutor* executor) {
    this->all_executors.append(executor);
}

QString Rotation::get_class() const {
    return this->class_name;
}

QString Rotation::get_name() const {
    return this->name;
}

QString Rotation::get_description() const {
    return this->description;
}

AttackMode Rotation::get_attack_mode() const {
    return this->attack_mode;
}

ResourceType Rotation::get_resource_from_string(const QString& resource) const {
    if (resource == "Mana")
        return ResourceType::Mana;
    if (resource == "Rage")
        return ResourceType::Rage;
    if (resource == "Energy")
        return ResourceType::Energy;

    qDebug() << "Failed to find resource for" << resource;
    check(false, QString("Failed to find resource for '%1'").arg(resource).toStdString());
    return ResourceType::Rage;
}

void Rotation::dump() {
    qDebug() << "class" << class_name;
    qDebug() << "name" << name;
    qDebug() << "desc" << description;
    qDebug() << "executors:";
    for (const auto& executor : all_executors) {
        executor->dump();
    }
}
