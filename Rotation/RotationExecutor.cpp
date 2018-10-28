
#include "RotationExecutor.h"
#include "Condition.h"
#include "Spell.h"

#include <QDebug>
#include <utility>

RotationExecutor::RotationExecutor(QString name) :
    spell_name(std::move(name)),
    spell(nullptr)
{}

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
    if (spell == nullptr)
        return;

    if (!spell->is_available())
        return;

    if (condition_groups.empty()) {
        spell->perform();
        return;
    }

    for (int i = 0; i < condition_groups.size(); ++i) {
        if (condition_group_fulfilled(i)) {
            spell->perform();
            return;
        }
    }
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

Spell* RotationExecutor::get_spell() const {
    return this->spell;
}

void RotationExecutor::set_spell(Spell* spell) {
    if (spell != nullptr)
        assert(spell_name == spell->get_name());

    this->spell = spell;
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
