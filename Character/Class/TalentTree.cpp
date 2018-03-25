
#include "TalentTree.h"
#include "Talent.h"
#include <QDebug>

TalentTree::TalentTree(const QString &name_, QObject *parent) :
    QObject(parent),
    name(name_),
    total_spent_points(0),
    talents(QMap<QString, Talent*>())
{
    spent_points = {{"1", 0}, {"2", 0}, {"3", 0}, {"4", 0}, {"5", 0}, {"6", 0}, {"7", 0}};
}

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
        ++total_spent_points;
        if (spent_points.contains(QString(position[0])))
            spent_points[QString(position[0])]++;
        else
            qDebug() << "TalentTree::increment_rank Missing position" << position;
        return true;
    }

    return false;
}

bool TalentTree::decrement_rank(const QString &position) {
    if (!talents.contains(position))
        return false;

    int investigated_rank = get_highest_invested_rank().toInt();
    int decremented_rank = QString(position[0]).toInt();

    while (investigated_rank > decremented_rank) {
        int attempted_decrement = get_points_spent_up_to_rank(investigated_rank) - 1;
        int minimum_requirement = get_investment_requirement_for_rank(investigated_rank);

        if (attempted_decrement < minimum_requirement) {
            return false;
        }

        --investigated_rank;
    }

    if (talents[position]->decrement_rank()) {
        --total_spent_points;
        spent_points[QString(position[0])]--;
        return true;
    }

    return false;
}

void TalentTree::set_rank(const QString &position, const int new_rank) {
    if (!talents.contains(position))
        return;

    talents[position]->set_rank(new_rank);
}

bool TalentTree::is_active(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->is_active();
}

bool TalentTree::is_maxed(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->is_maxed();
}

bool TalentTree::is_available(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return total_spent_points >= (QString(position[0]).toInt() - 1) * 5;
}

QString TalentTree::get_highest_invested_rank() const {
    if (spent_points["7"] > 0)
        return "7";
    if (spent_points["6"] > 0)
        return "6";
    if (spent_points["5"] > 0)
        return "5";
    if (spent_points["4"] > 0)
        return "4";
    if (spent_points["3"] > 0)
        return "3";
    if (spent_points["2"] > 0)
        return "2";
    return "1";
}

int TalentTree::get_investment_requirement_for_rank(const int rank) const {
    return (rank - 1) * 5;
}

int TalentTree::get_points_spent_up_to_rank(const int rank) const {
    int invested_below_rank = 0;

    // Breaks are purposefully omitted.
    switch (rank) {
    case 7:
        invested_below_rank += spent_points["6"];
    case 6:
        invested_below_rank += spent_points["5"];
    case 5:
        invested_below_rank += spent_points["4"];
    case 4:
        invested_below_rank += spent_points["3"];
    case 3:
        invested_below_rank += spent_points["2"];
    case 2:
        invested_below_rank += spent_points["1"];
    }

    return invested_below_rank;
}

int TalentTree::get_total_points() const {
    return total_spent_points;
}
