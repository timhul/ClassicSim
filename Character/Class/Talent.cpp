
#include "Talent.h"
#include <QDebug>
#include <utility>
#include "Character.h"
#include "TalentTree.h"

Talent::Talent(Character *pchar_, TalentTree *tree_, QString name_, QString  position_, QString icon_, const int max_points_) :
    pchar(pchar_),
    tree(tree_),
    name(std::move(name_)),
    position(std::move(position_)),
    icon(std::move(icon_)),
    max_points(max_points_),
    curr_points(0),
    parent(nullptr),
    right_child(nullptr),
    bottom_child(nullptr)
{
    assert(max_points > 0 && max_points <= 5);
}

Talent::~Talent() = default;

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
    QString req_string = "";
    if (parent != nullptr && !parent->is_maxed()) {
        QString max_rank = QString::number(parent->get_max_rank());
        QString point = parent->get_max_rank() > 1 ? "points" : "point";
        req_string += QString("Requires %1 %2 in %3").arg(max_rank, point, parent->get_name());
    }

    int own_row = QString(position[0]).toInt();
    int point_investment = (own_row - 1) * 5;

    if (point_investment > tree->get_total_points()) {
        if (req_string != "")
            req_string += "\n";

        req_string += QString("Requires %1 points in %2 Talents").arg(QString::number(point_investment), tree->get_name());
    }

    return req_string;
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
    if (!has_right_child())
        return "";

    return get_arrow_identifier(right_child->get_position());
}

QString Talent::get_bottom_arrow_image() const {
    if (!has_bottom_child())
        return "";

    return get_arrow_identifier(bottom_child->get_position());
}

QString Talent::get_arrow_identifier(const QString& target_position) const {
    int own_row = QString(position[0]).toInt();
    int target_row = QString(target_position[0]).toInt();
    QString own_column = QString(position).remove(0, 1);
    QString target_column = QString(target_position).remove(0, 1);

    int delta = target_row - own_row;

    if (own_column == target_column) {
        switch(delta) {
        case 1:
            return "VERTICAL0";
        case 2:
            return "VERTICAL1";
        case 3:
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

    apply_rank_effect();
    curr_points++;
    return true;
}

bool Talent::decrement_rank() {
    if (any_child_active())
        return false;

    if (curr_points == 0)
        return false;

    remove_rank_effect();
    curr_points--;
    return true;
}

void Talent::force_clear_rank() {
    for (int i = 0; i < curr_points; ++i) {
        remove_rank_effect();
    }

    curr_points = 0;
}

bool Talent::is_active() const {
    return curr_points > 0;
}

bool Talent::is_maxed() const {
    return curr_points == max_points;
}

bool Talent::has_parent() const {
    return parent != nullptr;
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

Talent* Talent::get_parent() const {
    return parent;
}

Talent* Talent::get_bottom_child() const {
    return bottom_child;
}

Talent* Talent::get_right_child() const {
    return right_child;
}

void Talent::initialize_rank_descriptions(const QString &base_str, const int base_value, const int increase) {
    for (int i = 0; i < max_points; ++i) {
        rank_descriptions.insert(i + 1, base_str.arg(base_value + i * increase));
    }

    rank_descriptions[0] = rank_descriptions[1];
}

void Talent::initialize_rank_descriptions(const QString &base_str, const QVector<QPair<int, int>> &format_values) {
    for (int i = 0; i < max_points; ++i) {
        QString format_str = base_str;
        for (auto format_value : format_values) {
            format_str = format_str.arg(format_value.first + i * format_value.second);
        }

        rank_descriptions.insert(i + 1, format_str);
    }

    rank_descriptions[0] = rank_descriptions[1];
}

void Talent::set_parent(Talent* parent) {
    this->parent = parent;
}

void Talent::set_bottom_child(Talent* bottom_child) {
    this->bottom_child = bottom_child;
}

void Talent::set_right_child(Talent* right_child) {
    this->right_child = right_child;
}
