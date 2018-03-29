
#include "TalentTree.h"
#include "Talent.h"
#include <QDebug>

TalentTree::TalentTree(const QString &name_, const QString &background_, QObject *parent) :
    QObject(parent),
    name(name_),
    background(background_),
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

QString TalentTree::get_background_image() const {
    return background;
}

QString TalentTree::get_talent_name(const QString &position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->get_name();
}

QString TalentTree::get_requirement_string(const QString &position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->get_requirement_string();
}

QString TalentTree::get_current_rank_description(const QString &position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->get_current_rank_description();
}

QString TalentTree::get_next_rank_description(const QString &position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->get_next_rank_description();
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

QString TalentTree::get_right_arrow(const QString &position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->get_right_arrow_image();
}

QString TalentTree::get_bottom_arrow(const QString &position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->get_bottom_arrow_image();
}

bool TalentTree::bottom_child_is_available(const QString &position) const {
    if (!talents.contains(position) || !talents[position]->has_bottom_child() || !is_maxed(position)) {
        return false;
    }

    QString child_pos = talents[position]->get_bottom_child()->get_position();

    return total_spent_points >= (QString(child_pos[0]).toInt() - 1) * 5;
}

bool TalentTree::bottom_child_is_active(const QString &position) const {
    if (!talents.contains(position) || !talents[position]->has_bottom_child()) {
        return false;
    }

    return talents[position]->get_bottom_child()->is_active();
}

bool TalentTree::right_child_is_available(const QString &position) const {
    if (!talents.contains(position) || !talents[position]->has_right_child() || !is_maxed(position))
        return false;

    QString child_pos = talents[position]->get_right_child()->get_position();

    return total_spent_points >= (QString(child_pos[0]).toInt() - 1) * 5;
}

bool TalentTree::right_child_is_active(const QString &position) const {
    if (!talents.contains(position) || !talents[position]->has_right_child()) {
        return false;
    }

    return talents[position]->get_right_child()->is_active();
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

    if (has_parent(position) && !talents[position]->get_parent()->is_maxed())
        return false;

    return total_spent_points >= (QString(position[0]).toInt() - 1) * 5;
}

bool TalentTree::has_parent(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->has_parent();
}

bool TalentTree::has_right_child(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->has_right_child();
}

bool TalentTree::has_bottom_child(const QString &position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->has_bottom_child();
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

void TalentTree::clear_tree() {
    for (auto it : talents.keys()) {
        talents.value(it)->force_clear_rank();
    }

    total_spent_points = 0;
}
