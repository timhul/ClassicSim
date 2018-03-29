
#include "Talents.h"

#include <QDebug>

Talents::Talents(QObject* parent) :
    QObject(parent),
    talent_points_remaining(51)
{}

Talents::~Talents() {
    for (auto it : talent_trees.keys()) {
        if (talent_trees.value(it) != nullptr)
            delete talent_trees.value(it);
    }
}

QString Talents::get_icon(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getIcon could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_icon(talent_position);
}

bool Talents::show_position(const QString tree_position, const QString talent_position) const {
    return get_icon(tree_position, talent_position) != "";
}

bool Talents::show_bottom_arrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::showBottomArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->has_bottom_child(talent_position);
}

bool Talents::show_right_arrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::showRightArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->has_right_child(talent_position);
}

QString Talents::get_bottom_arrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getBottomArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_bottom_arrow(talent_position);
}

QString Talents::get_right_arrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRightArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_right_arrow(talent_position);
}

bool Talents::bottom_child_available(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->bottom_child_is_available(talent_position);
}

bool Talents::right_child_available(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->right_child_is_available(talent_position);
}

bool Talents::bottom_child_active(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->bottom_child_is_active(talent_position);
}

bool Talents::right_child_active(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->right_child_is_active(talent_position);
}

bool Talents::is_active(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isActive could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[tree_position]->is_active(talent_position);
}

bool Talents::is_available(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isAvailable could not find tree position" << tree_position;
        return false;
    }

    if (talent_points_remaining == 0 && !talent_trees[tree_position]->is_active(talent_position))
        return false;

    return talent_trees[tree_position]->is_available(talent_position);
}

bool Talents::is_maxed(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isMaxed could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[tree_position]->is_maxed(talent_position);
}

bool Talents::has_talent_points_remaining() const {
    return talent_points_remaining > 0;
}

QString Talents::get_rank(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[tree_position]->get_current_rank(talent_position));
}

QString Talents::get_max_rank(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[tree_position]->get_max_rank(talent_position));
}

void Talents::increment_rank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return;
    }

    assert(talent_points_remaining >= 0);

    if (talent_points_remaining == 0)
        return;

    if (talent_trees[tree_position]->increment_rank(talent_position)) {
        --talent_points_remaining;
    }
}

void Talents::decrement_rank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return;
    }

    assert(talent_points_remaining >= 0);

    if (talent_points_remaining == 51)
        return;

    if (talent_trees[tree_position]->decrement_rank(talent_position)) {
        ++talent_points_remaining;
    }
}

QString Talents::get_requirements(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_requirement_string(talent_position);
}

QString Talents::get_current_rank_description(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_current_rank_description(talent_position);
}

QString Talents::get_next_rank_description(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_next_rank_description(talent_position);
}

int Talents::get_tree_points(const QString tree_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTreePoints could not find tree position" << tree_position;
        return 0;
    }

    return talent_trees[tree_position]->get_total_points();
}

QString Talents::get_tree_name(const QString tree_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTreeName could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_name();
}

QString Talents::get_talent_name(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTalentName could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_talent_name(talent_position);
}

void Talents::increase_to_max_rank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::maxRank could not find tree position" << tree_position;
        return;
    }

    while (talent_points_remaining > 0 && !talent_trees[tree_position]->is_maxed(talent_position)) {
        if (talent_trees[tree_position]->increment_rank(talent_position))
            --talent_points_remaining;
        else
            break;
    }
}

void Talents::decrease_to_min_rank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::minRank could not find tree position" << tree_position;
        return;
    }

    while (talent_points_remaining < 51 && talent_trees[tree_position]->is_active(talent_position)) {
        if (talent_trees[tree_position]->decrement_rank(talent_position))
            ++talent_points_remaining;
        else
            break;
    }
}

void Talents::clear_tree(const QString tree_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::clearTree could not find tree position" << tree_position;
        return;
    }

    int points_refunded = talent_trees[tree_position]->get_total_points();
    talent_trees[tree_position]->clear_tree();
    talent_points_remaining += points_refunded;
    assert(talent_points_remaining <= 51);
}

void Talents::set_talent_tree(const QString &tree_position, TalentTree *tree) {
    if (talent_trees.contains(tree_position) && talent_trees[tree_position] != nullptr) {
        delete talent_trees[tree_position];
    }

    talent_trees[tree_position] = tree;
}

int Talents::get_talent_points_remaining() const {
    return talent_points_remaining;
}
