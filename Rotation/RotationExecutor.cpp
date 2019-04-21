#include "RotationExecutor.h"

#include <QDebug>
#include <utility>

#include "Condition.h"
#include "Spell.h"
#include "StatisticsRotationExecutor.h"
#include "Utils/Check.h"

RotationExecutor::RotationExecutor(QString name) :
    spell_name(std::move(name))
{
    spell_status_statistics.insert(SpellStatus::Available, 0);
    spell_status_statistics.insert(SpellStatus::NotEnabled, 0);
    spell_status_statistics.insert(SpellStatus::OnGCD, 0);
    spell_status_statistics.insert(SpellStatus::OnCooldown, 0);
    spell_status_statistics.insert(SpellStatus::CastInProgress, 0);
    spell_status_statistics.insert(SpellStatus::SpellSpecific, 0);
    spell_status_statistics.insert(SpellStatus::InsufficientResources, 0);
}

RotationExecutor::~RotationExecutor() {
    for (auto & condition_group : condition_groups) {
        for (auto & j : condition_group) {
            delete j;
        }
    }

    for (auto & sentence : sentences) {
        delete sentence;
    }

    condition_groups.clear();
    sentences.clear();
}

void RotationExecutor::attempt_cast() {
    SpellStatus spell_status = spell->get_spell_status();

    if (spell_status != SpellStatus::Available) {
        ++spell_status_statistics[spell_status];
        return;
    }

    if (condition_groups.empty()) {
        ++successful_casts;
        spell->perform();
        return;
    }

    for (int i = 0; i < condition_groups.size(); ++i) {
        if (condition_group_fulfilled(i)) {
            ++successful_casts;
            spell->perform();
            return;
        }
    }
    ++no_condition_group_fulfilled;
}

bool RotationExecutor::condition_group_fulfilled(const int index) const {
    for (int i = 0; i < condition_groups.at(index).size(); ++i) {
        if (!condition_groups[index][i]->condition_fulfilled()) {
            return false;
        }
    }

    return true;
}

QString RotationExecutor::get_spell_name() const {
    return this->spell_name;
}

QString RotationExecutor::get_conditions_string() const {
    QStringList condition_descriptions;
    for (int i = 0; i < condition_groups.size(); ++i) {
        for (auto & condition : condition_groups[i])
            condition_descriptions << condition->condition_description();

        if (i + 1 < condition_groups.size())
            condition_descriptions << "OR";
    }

    return condition_descriptions.join("\n");
}

Spell* RotationExecutor::get_spell() const {
    return this->spell;
}

void RotationExecutor::set_spell(Spell* spell) {
    if (spell != nullptr)
        check((spell_name == spell->get_name()), "Mismatched spell name when setting spell");

    this->spell = spell;
}

void RotationExecutor::prepare_set_of_combat_iterations(StatisticsRotationExecutor* rotation_statistics) {
    check((this->rotation_statistics == nullptr), "Rotation statistics is not nullptr");
    this->rotation_statistics = rotation_statistics;
    no_condition_group_fulfilled = 0;
    successful_casts = 0;

    for (auto & status : spell_status_statistics)
        status = 0;
}

void RotationExecutor::finish_set_of_combat_iterations() {
    check((rotation_statistics != nullptr), "Rotation statistics nullptr");
    rotation_statistics->add_successful_casts(successful_casts);
    rotation_statistics->add_no_condition_group_fulfilled(no_condition_group_fulfilled);
    rotation_statistics->add_spell_status_map(spell_status_statistics);
    rotation_statistics = nullptr;
}

void RotationExecutor::add_sentence(Sentence* sentence) {
    this->sentences.append(sentence);
}

void RotationExecutor::add_condition(const QVector<Condition*>& condition) {
    this->condition_groups.append(condition);
}

void RotationExecutor::add_variable_assignment(const QString& var, const QString& value) {
    this->variable_assignments.insert(var, value);
}

QMap<QString, QString>& RotationExecutor::get_variable_assignments() {
    return this->variable_assignments;
}

void RotationExecutor::dump() {
    qDebug() << "\nspell_name" << spell_name;
    qDebug() << "spell ptr" << spell;
    qDebug() << "variable assignments" << variable_assignments;
    qDebug() << "conditions:";
    for (auto sentence : sentences) {
        qDebug() << "----- sentence ------";
        sentence->dump();
    }
}
