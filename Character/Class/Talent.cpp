
#include "Talent.h"
#include <QDebug>

Talent::Talent(const QString &name_, const QString & position_, const QString &icon_, const int max_points_) :
    name(name_),
    position(position_),
    icon(icon_),
    max_points(max_points_),
    curr_points(0),
    parent(nullptr),
    right_child(nullptr),
    bottom_child(nullptr)
{
    assert(max_points > 0 && max_points <= 5);
}

Talent::~Talent() {
}

QString Talent::get_name() const {
    return name;
}

QString Talent::get_icon() const {
    return icon;
}

QString Talent::get_position() const {
    return position;
}

QString Talent::get_requirement_string() const {
    return "Missing override for " + get_name();
}

QString Talent::get_current_rank_description() const {
    if (!rank_descriptions.contains(curr_points))
        return "Missing description for " + get_name() + " rank " + QString::number(curr_points);

    return rank_descriptions[curr_points];
}

QString Talent::get_next_rank_description() const {
    if (!rank_descriptions.contains(curr_points + 1))
        return "Missing description for " + get_name() + " rank " + QString::number(curr_points + 1);

    return rank_descriptions[curr_points + 1];
}

QString Talent::get_right_arrow_image() const {
    QString arrow = get_arrow_identifier(right_child->get_position());
    if (arrow == "RIGHT" || arrow == "HOOK") {
        return (arrow == "RIGHT") ? "Assets/talents/arrow-horizontal-0.png" :
                                    "Assets/talents/arrow-hook.png";
    }

    return "";
}

QString Talent::get_bottom_arrow_image() const {
    QString arrow = get_arrow_identifier(right_child->get_position());
    if (arrow == "RIGHT" || arrow == "HOOK") {
        return (arrow == "RIGHT") ? "Assets/talents/arrow-horizontal-0.png" :
                                    "Assets/talents/arrow-hook.png";
    }

    return "";
}

QString Talent::get_arrow_identifier(const QString target_position) const {
    int own_row = QString(position[0]).toInt();
    int target_row = QString(target_position[0]).toInt();
    QString own_column = QString(position).remove(0, 1);
    QString target_column = QString(target_position).remove(0, 1);

    int delta = target_row - own_row;

    if (own_column == target_column) {
        switch(delta) {
        case 1:
            return "VERTICAL1";
        case 2:
            return "VERTICAL2";
        default:
            qDebug() << "Talent::get_arrow_identifier unexpected delta" << delta;
            return "";
        }
    }
    else {
        switch(delta) {
        case 0:
            return "RIGHT";
        case 1:
            return "HOOK";
        default:
            qDebug() << "Talent::get_arrow_identifier unexpected delta" << delta;
            return "";
        }
    }
}

int Talent::get_current_rank() const {
    return curr_points;
}

int Talent::get_max_rank() const {
    return max_points;
}

bool Talent::increment_rank() {
    if (curr_points == max_points)
        return false;

    if (parent != nullptr && !parent->is_maxed()) {
        return false;
    }

    curr_points++;
    return true;
}

bool Talent::decrement_rank() {
    if (any_child_active())
        return false;

    if (curr_points == 0)
        return false;

    curr_points--;
    return true;
}

bool Talent::is_active() const {
    return curr_points > 0;
}

bool Talent::is_maxed() const {
    return curr_points == max_points;
}

bool Talent::has_right_child() const {
    return right_child != nullptr;
}

bool Talent::has_bottom_child() const {
    return bottom_child != nullptr;
}

bool Talent::any_child_active() const {
    return ((right_child != nullptr && right_child->is_active())
            || (right_child != nullptr && bottom_child->is_active()));
}

Talent* Talent::get_bottom_child() const {
    return bottom_child;
}

Talent* Talent::get_right_child() const {
    return right_child;
}

void Talent::initialize_rank_descriptions(const QString &base_str, const int base_val, const int increase) {
    for (int i = 0; i < max_points; ++i) {
        rank_descriptions.insert(i + +1, base_str.arg(base_val + i * increase));
    }

    rank_descriptions[0] = rank_descriptions[1];
}
