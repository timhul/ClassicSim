
#include "GUIControl.h"

GUIControl::GUIControl(Talents*talents_, QObject* parent) :
    QObject(parent),
    talents(talents_)
{}

QString GUIControl::getIcon(const QString tree_position, const QString talent_position) const {
    return talents->get_icon(tree_position, talent_position);
}

bool GUIControl::showPosition(const QString tree_position, const QString talent_position) const {
    return talents->show_position(tree_position, talent_position);
}

bool GUIControl::showBottomArrow(const QString tree_position, const QString talent_position) const {
    return talents->show_bottom_arrow(tree_position, talent_position);
}
bool GUIControl::showRightArrow(const QString tree_position, const QString talent_position) const {
    return talents->show_right_arrow(tree_position, talent_position);
}

QString GUIControl::getBottomArrow(const QString tree_position, const QString talent_position) const {
    return talents->get_bottom_arrow(tree_position, talent_position);
}

QString GUIControl::getRightArrow(const QString tree_position, const QString talent_position) const {
    return talents->get_right_arrow(tree_position, talent_position);
}

bool GUIControl::bottomChildAvailable(const QString tree_position, const QString talent_position) const {
    return talents->bottom_child_available(tree_position, talent_position);
}

bool GUIControl::bottomChildActive(const QString tree_position, const QString talent_position) const {
    return talents->bottom_child_active(tree_position, talent_position);
}

bool GUIControl::rightChildAvailable(const QString tree_position, const QString talent_position) const {
    return talents->right_child_available(tree_position, talent_position);
}

bool GUIControl::rightChildActive(const QString tree_position, const QString talent_position) const {
    return talents->right_child_active(tree_position, talent_position);
}

bool GUIControl::isActive(const QString tree_position, const QString talent_position) const {
    return talents->is_active(tree_position, talent_position);
}

bool GUIControl::isAvailable(const QString tree_position, const QString talent_position) const {
    return talents->is_available(tree_position, talent_position);
}

bool GUIControl::isMaxed(const QString tree_position, const QString talent_position) const {
    return talents->is_maxed(tree_position, talent_position);
}

bool GUIControl::hasTalentPointsRemaining() const {
    return talents->has_talent_points_remaining();
}

QString GUIControl::getRank(const QString tree_position, const QString talent_position) const {
    return talents->get_rank(tree_position, talent_position);
}

QString GUIControl::getMaxRank(const QString tree_position, const QString talent_position) const {
    return talents->get_max_rank(tree_position, talent_position);
}

void GUIControl::incrementRank(const QString tree_position, const QString talent_position) {
    talents->increment_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
}

void GUIControl::decrementRank(const QString tree_position, const QString talent_position) {
    talents->decrement_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
}

QString GUIControl::getRequirements(const QString tree_position, const QString talent_position) const {
    return talents->get_requirements(tree_position, talent_position);
}

QString GUIControl::getCurrentRankDescription(const QString tree_position, const QString talent_position) const {
    return talents->get_current_rank_description(tree_position, talent_position);
}

QString GUIControl::getNextRankDescription(const QString tree_position, const QString talent_position) const {
    return talents->get_next_rank_description(tree_position, talent_position);
}

int GUIControl::getTreePoints(const QString tree_position) const {
    return talents->get_tree_points(tree_position);
}

QString GUIControl::getTreeName(const QString tree_position) const {
    return talents->get_tree_name(tree_position);
}

QString GUIControl::getTalentName(const QString tree_position, const QString talent_position) const {
    return talents->get_talent_name(tree_position, talent_position);
}

void GUIControl::maxRank(const QString tree_position, const QString talent_position) {
    talents->increase_to_max_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
}
void GUIControl::minRank(const QString tree_position, const QString talent_position) {
    talents->decrease_to_min_rank(tree_position, talent_position);
    Q_EMIT talentsUpdated();
}

void GUIControl::clearTree(const QString tree_position) {
    talents->clear_tree(tree_position);
    Q_EMIT talentsUpdated();
}

int GUIControl::get_talent_points_remaining() const {
    return talents->get_talent_points_remaining();
}


