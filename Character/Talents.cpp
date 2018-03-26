
#include "Talents.h"

#include <QDebug>

Talents::Talents(QObject* parent) :
    QObject(parent),
    max_talent_points(51)
{}

Talents::~Talents() {
    for (auto it : talent_trees.keys()) {
        if (talent_trees.value(it) != nullptr)
            delete talent_trees.value(it);
    }
}

QString Talents::getIcon(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getIcon could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_icon(talent_position);
}

bool Talents::showPosition(const QString tree_position, const QString talent_position) const {
    return getIcon(tree_position, talent_position) != "";
}

bool Talents::showBottomArrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::showBottomArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->has_bottom_child(talent_position);
}

bool Talents::showRightArrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::showRightArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->has_right_child(talent_position);
}

QString Talents::getBottomArrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getBottomArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_bottom_arrow(talent_position);
}

QString Talents::getRightArrow(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRightArrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[tree_position]->get_right_arrow(talent_position);
}

bool Talents::bottomChildAvailable(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->bottom_child_is_available(talent_position);
}

bool Talents::rightChildAvailable(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->right_child_is_available(talent_position);
}

bool Talents::bottomChildActive(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->bottom_child_is_active(talent_position);
}

bool Talents::rightChildActive(const QString tree_position, const QString talent_position) const {
    return talent_trees[tree_position]->right_child_is_active(talent_position);
}

bool Talents::isActive(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isActive could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[tree_position]->is_active(talent_position);
}

bool Talents::isAvailable(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isAvailable could not find tree position" << tree_position;
        return false;
    }

    if (max_talent_points == 0 && !talent_trees[tree_position]->is_active(talent_position))
        return false;

    return talent_trees[tree_position]->is_available(talent_position);
}

bool Talents::isMaxed(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::isMaxed could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[tree_position]->is_maxed(talent_position);
}

bool Talents::hasTalentPointsRemaining() const {
    return max_talent_points > 0;
}

QString Talents::getRank(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[tree_position]->get_current_rank(talent_position));
}

QString Talents::getMaxRank(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getRank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[tree_position]->get_max_rank(talent_position));
}

void Talents::incrementRank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return;
    }

    assert(max_talent_points >= 0);

    if (max_talent_points == 0)
        return;

    if (talent_trees[tree_position]->increment_rank(talent_position)) {
        --max_talent_points;
        Q_EMIT talentsUpdated();
    }
}

void Talents::decrementRank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return;
    }

    assert(max_talent_points >= 0);

    if (max_talent_points == 51)
        return;

    if (talent_trees[tree_position]->decrement_rank(talent_position)) {
        ++max_talent_points;
        Q_EMIT talentsUpdated();
    }
}

QString Talents::getRequirements(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_requirement_string(talent_position);
}

QString Talents::getCurrentRankDescription(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_current_rank_description(talent_position);
}

QString Talents::getNextRankDescription(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::incrementRank could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_next_rank_description(talent_position);
}

int Talents::getTreePoints(const QString tree_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTreePoints could not find tree position" << tree_position;
        return 0;
    }

    return talent_trees[tree_position]->get_total_points();
}

QString Talents::getTreeName(const QString tree_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTreeName could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_name();
}

QString Talents::getTalentName(const QString tree_position, const QString talent_position) const {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::getTalentName could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[tree_position]->get_talent_name(talent_position);
}

void Talents::maxRank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::maxRank could not find tree position" << tree_position;
        return;
    }

    while (max_talent_points > 0 && !talent_trees[tree_position]->is_maxed(talent_position)) {
        if (talent_trees[tree_position]->increment_rank(talent_position))
            --max_talent_points;
        else
            break;
    }

    Q_EMIT talentsUpdated();
}

void Talents::minRank(const QString tree_position, const QString talent_position) {
    if (!talent_trees.contains(tree_position)) {
        qDebug() << "Talents::minRank could not find tree position" << tree_position;
        return;
    }

    while (max_talent_points < 51 && talent_trees[tree_position]->is_active(talent_position)) {
        if (talent_trees[tree_position]->decrement_rank(talent_position))
            ++max_talent_points;
        else
            break;
    }

    Q_EMIT talentsUpdated();
}

void Talents::setTalentTree(const QString &tree_position, TalentTree *tree) {
    if (talent_trees.contains(tree_position) && talent_trees[tree_position] != nullptr) {
        delete talent_trees[tree_position];
    }

    talent_trees[tree_position] = tree;
}
