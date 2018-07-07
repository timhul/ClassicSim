
#include "CastIf.h"
#include "Condition.h"
#include "Spell.h"

#include <QDebug>

CastIf::CastIf(QString name, QObject* parent) :
    QObject(parent),
    spell_name(name),
    spell(nullptr)
{}

CastIf::~CastIf() {
    for (int i = 0; i < condition_groups.size(); ++i) {
        for (int j = 0; j < condition_groups.at(i).size(); ++j) {
            delete condition_groups[i][j];
        }
    }

    for (int i = 0; i < sentences.size(); ++i) {
        delete sentences[i];
    }

    condition_groups.clear();
    sentences.clear();
}

void CastIf::attempt_cast() {
    assert(spell != nullptr);
    if (spell->is_available() == false)
        return;

    if (condition_groups.empty()) {
        spell->perform();
        return;
    }

    for (int i = 0; i < condition_groups.size(); ++i) {
        if (condition_group_fulfilled(i) == true) {
            spell->perform();
            return;
        }
    }
}

bool CastIf::condition_group_fulfilled(const int index) const {
    for (int i = 0; i < condition_groups.at(index).size(); ++i) {
        if (condition_groups[index][i]->condition_fulfilled() == false) {
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

void CastIf::add_condition(QVector<Condition*> condition) {
    this->condition_groups.append(condition);
}

void CastIf::add_variable_assignment(QString var, QString value) {
    this->variable_assignments.insert(var, value);
}

QMap<QString, QString>& CastIf::get_variable_assignments() {
    return this->variable_assignments;
}

void CastIf::dump() {
    qDebug() << "variable assignments" << variable_assignments;
    qDebug() << "conditions:";
    for (int i = 0; i < sentences.size(); ++i) {
        qDebug() << "----- sentences ------";
        sentences.at(i)->dump();
    }
}
