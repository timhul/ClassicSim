
#include "Rotation.h"
#include "CastIf.h"
#include "ConditionBuff.h"
#include "ConditionResource.h"
#include "ConditionSpell.h"
#include "ConditionVariableAssign.h"
#include "ConditionVariableBuiltin.h"

#include <QDebug>

Rotation::Rotation(QString class_name, QObject* parent) :
    QObject(parent),
    class_name(class_name)
{}

Rotation::~Rotation() {
    for (auto & cast_if : cast_ifs) {
        delete cast_if;
    }

    cast_ifs.clear();
}

void Rotation::perform_rotation() const {
    for (auto cast_if : cast_ifs) {
        cast_if->attempt_cast();
    }
}

bool Rotation::link_spells(Character* pchar) {
    this->pchar = pchar;

    for (int i = 0; i < cast_ifs.size(); ++i) {
        QString spell_name = cast_ifs[i]->get_spell_name();

        Spell* spell = get_spell_from_name(spell_name);
        if (spell == nullptr) {
            qDebug() << "Could not find matching spell for" << spell_name;
            return false;
        }

        cast_ifs[i]->set_spell(spell);
        if (!this->add_conditionals(i))
            return false;
    }

    return true;
}

bool Rotation::add_conditionals(const int index) {
    CastIf* cast_if = cast_ifs[index];
    QVector<Condition*> condition_group_to_add;

    for (int i = 0; i < cast_if->sentences.size(); ++i) {
        Condition* condition = nullptr;
        Sentence* sentence = cast_if->sentences[i];

        if (sentence->logical_connective == LogicalConnectives::OR) {
            assert(condition_group_to_add.empty() == false);
            cast_if->add_condition(condition_group_to_add);
            condition_group_to_add.clear();
        }

        switch (sentence->condition_type) {
        case ConditionTypes::BuffCondition:
            condition = new ConditionBuff(get_buff_from_name(sentence->type_value),
                                          sentence->mathematical_symbol,
                                          sentence->compared_value.toDouble());
            break;
        case ConditionTypes::SpellCondition:
            condition = new ConditionSpell(get_spell_from_name(sentence->type_value),
                                           sentence->mathematical_symbol,
                                           sentence->compared_value.toDouble());
            break;
        case ConditionTypes::ResourceCondition:
            condition = new ConditionResource(this->pchar,
                                              sentence->mathematical_symbol,
                                              sentence->compared_value.toDouble());
            break;
        case ConditionTypes::VariableBuiltinCondition:
            if (get_builtin_variable(sentence->type_value) == BuiltinVariables::Undefined)
                break;
            condition = new ConditionVariableBuiltin(this->pchar,
                                                     get_builtin_variable(sentence->type_value),
                                                     sentence->mathematical_symbol,
                                                     sentence->compared_value.toDouble());
            break;
        default:
            qDebug() << "condition type not supported:" << sentence->condition_type;
            sentence->dump();
            return false;
        }

        condition_group_to_add.append(condition);
    }

    // Add last condition manually
    if (!condition_group_to_add.empty())
        cast_if->add_condition(condition_group_to_add);

    return true;
}

void Rotation::set_name(const QString& name) {
    this->name = name;
}

void Rotation::set_description(const QString& desc) {
    this->description = desc;
}

void Rotation::add_variable(const QString& var, const QString& value) {
    this->defined_variables.insert(var, value);
}

void Rotation::add_prerequisite(const QString& key, const QString& value) {
    this->prerequisites.insert(key, value);
}

void Rotation::add_cast_if(CastIf* cast_if) {
    this->cast_ifs.append(cast_if);
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

int Rotation::get_builtin_variable(const QString& var_name) const {
    if (var_name == "target_health")
        return BuiltinVariables::TargetHealth;
    if (var_name == "time_remaining_encounter")
        return BuiltinVariables::TimeRemainingEncounter;
    if (var_name == "time_remaining_execute")
        return BuiltinVariables::TimeRemainingExecute;
    if (var_name == "time_since_swing")
        return BuiltinVariables::SwingTimer;

    return BuiltinVariables::Undefined;
}

void Rotation::dump() {
    qDebug() << "class" << class_name;
    qDebug() << "name" << name;
    qDebug() << "desc" << description;
    qDebug() << "defined_variables" << defined_variables;
    qDebug() << "prerequisites" << prerequisites;
    qDebug() << "cast_ifs:";
    for (auto & cast_if : cast_ifs) {
        cast_if->dump();
    }
}
