
#include "CastIf.h"
#include "Condition.h"
#include "Spell.h"

#include <QDebug>
#include <utility>

CastIf::CastIf(QString name, QObject* parent) :
    QObject(parent),
    spell_name(std::move(name)),
    spell(nullptr)
{}

CastIf::~CastIf() {
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

void CastIf::attempt_cast() {
    assert(spell != nullptr);
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

bool CastIf::condition_group_fulfilled(const int index) const {
    for (int i = 0; i < condition_groups.at(index).size(); ++i) {
        if (!condition_groups[index][i]->condition_fulfilled()) {
            return false;
        }
    }

    return true;
}

QString CastIf::get_spell_name() const {
    return this->spell_name;
}

Spell* CastIf::get_spell() const {
    return this->spell;
}

void CastIf::set_spell(Spell* spell) {
    assert(spell_name == spell->get_name());
    this->spell = spell;
}

void CastIf::add_sentence(Sentence* sentence) {
    this->sentences.append(sentence);
}

void CastIf::add_condition(const QVector<Condition*>& condition) {
    this->condition_groups.append(condition);
}

void CastIf::add_variable_assignment(const QString& var, const QString& value) {
    this->variable_assignments.insert(var, value);
}

QMap<QString, QString>& CastIf::get_variable_assignments() {
    return this->variable_assignments;
}

void CastIf::dump() {
    qDebug() << "variable assignments" << variable_assignments;
    qDebug() << "conditions:";
    for (auto sentence : sentences) {
        qDebug() << "----- sentences ------";
        sentence->dump();
    }
}
