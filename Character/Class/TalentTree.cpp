
#include "TalentTree.h"
#include "Talent.h"
#include <QDebug>

TalentTree::TalentTree(const QString &name_, QObject *parent) :
    QObject(parent),
    name(name_),
    spent_points(0),
    talents(QMap<QString, Talent*>())
{}

TalentTree::~TalentTree() {
    for (auto it : talents.keys()) {
        delete talents.value(it);
    }

    talents.clear();
}

QString TalentTree::get_name() const {
    return name;
}

void TalentTree::add_talents(const QMap<QString, Talent*> &new_talents) {
    for (auto it : new_talents.toStdMap()) {
        assert(!talents.contains(it.first));
        talents.insert(it.first, it.second);
    }
}

QString TalentTree::get_icon(const QString &position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->get_icon();
}

int TalentTree::get_current_rank(const QString &position) const {
    if (!talents.contains(position))
        return -1;

    return talents[position]->get_current_rank();
}

int TalentTree::get_max_rank(const QString &position) const {
    if (!talents.contains(position))
        return -1;

    return talents[position]->get_max_rank();
}

bool TalentTree::increment_rank(const QString &position) {
    if (!talents.contains(position) || !is_available(position))
        return false;

    if (talents[position]->increment_rank()) {
        ++spent_points;
        return true;
    }

    return false;
}

bool TalentTree::decrement_rank(const QString &position) {
    if (!talents.contains(position))
        return false;

    return talents[position]->decrement_rank();
}

void TalentTree::set_rank(const QString &position, const int new_rank) {
    if (!talents.contains(position))
        return;

    talents[position]->set_rank(new_rank);
}

bool TalentTree::is_active(const QString &position) const {
    if (!talents.contains(position))
        return false;

    if (talents[position]->is_active())
        return true;

    return spent_points >= (QString(position[0]).toInt() - 1) * 5;
}

bool TalentTree::is_maxed(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->is_maxed();
}

bool TalentTree::is_available(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return spent_points >= (QString(position[0]).toInt() - 1) * 5;
}
