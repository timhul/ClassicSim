#include "Talent.h"

#include <utility>

#include <QDebug>

#include "Buff.h"
#include "Character.h"
#include "Proc.h"
#include "SpellRankGroup.h"
#include "TalentRequirer.h"
#include "TalentTree.h"
#include "Utils/Check.h"

Talent::Talent(Character* pchar,
               TalentTree* tree,
               const QString& name,
               const QString& position,
               const QString& icon,
               const unsigned max_points,
               QMap<unsigned, QString> rank_descriptions,
               QVector<SpellRankGroup*> affected_spells_,
               QVector<Buff*> affected_buffs_,
               QVector<Proc*> affected_procs_) :
    pchar(pchar),
    tree(tree),
    name(name),
    position(position),
    icon(icon),
    max_points(max_points),
    affected_spells(std::move(affected_spells_)),
    affected_buffs(std::move(affected_buffs_)),
    affected_procs(std::move(affected_procs_)),
    parent(nullptr),
    right_child(nullptr),
    bottom_child(nullptr),
    rank_descriptions(std::move(rank_descriptions)) {
    check((max_points > 0 && max_points <= 5), "Number of talent points not possible");
}

Talent::Talent(Character* pchar,
               TalentTree* tree,
               const QString& name,
               const QString& position,
               const QString& icon,
               const unsigned max_points,
               const QString& rank_description,
               const QVector<QPair<unsigned, unsigned>>& format_values) :
    Talent(pchar, tree, name, position, icon, max_points) {
    if (!format_values.empty()) {
        initialize_rank_descriptions(rank_descriptions, rank_description, max_points, format_values);
    } else {
        rank_descriptions.insert(0, rank_description);
        rank_descriptions.insert(1, rank_description);
    }
}

Talent::Talent(Character* pchar,
               TalentTree* tree,
               const QString& name,
               const QString& position,
               const QString& icon,
               const unsigned max_points,
               const QString& rank_description,
               const QVector<QPair<double, double>>& format_values) :
    Talent(pchar, tree, name, position, icon, max_points) {
    if (!format_values.empty()) {
        initialize_rank_descriptions(rank_descriptions, rank_description, max_points, format_values);
    } else {
        rank_descriptions.insert(0, rank_description);
        rank_descriptions.insert(1, rank_description);
    }
}

void Talent::apply_rank_effect() {
    for (auto& spell_group : affected_spells) {
        for (auto& spell : spell_group->spell_group)
            dynamic_cast<TalentRequirer*>(spell)->increase_talent_rank(spell, name);
    }

    for (auto& buff : affected_buffs)
        dynamic_cast<TalentRequirer*>(buff)->increase_talent_rank(buff, name);

    for (auto& proc : affected_procs)
        dynamic_cast<TalentRequirer*>(proc)->increase_talent_rank(proc, name);
}

void Talent::remove_rank_effect() {
    for (auto& spell_group : affected_spells) {
        for (auto& spell : spell_group->spell_group)
            dynamic_cast<TalentRequirer*>(spell)->decrease_talent_rank(spell, name);
    }

    for (auto& buff : affected_buffs)
        dynamic_cast<TalentRequirer*>(buff)->decrease_talent_rank(buff, name);

    for (auto& proc : affected_procs)
        dynamic_cast<TalentRequirer*>(proc)->decrease_talent_rank(proc, name);
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
        switch (delta) {
        case 1:
            return "VERTICAL0";
        case 2:
            return "VERTICAL1";
        case 3:
            return "VERTICAL2";
        default:
            qDebug() << "Talent::get_arrow_identifier unexpected delta" << delta << "for target position" << target_position;
            return "";
        }
    } else {
        switch (delta) {
        case 0:
            return "RIGHT";
        case 1:
            return "HOOK";
        default:
            qDebug() << "Talent::get_arrow_identifier unexpected delta" << delta << "for target position" << target_position;
            return "";
        }
    }
}

unsigned Talent::get_current_rank() const {
    return curr_points;
}

unsigned Talent::get_max_rank() const {
    return max_points;
}

bool Talent::increment_rank() {
    if (curr_points == max_points)
        return false;

    if (parent != nullptr && !parent->is_maxed()) {
        return false;
    }

    curr_points++;
    apply_rank_effect();
    return true;
}

bool Talent::decrement_rank() {
    if (any_child_active())
        return false;

    if (curr_points == 0)
        return false;

    curr_points--;
    remove_rank_effect();
    return true;
}

void Talent::force_clear_rank() {
    for (; curr_points > 0;) {
        --curr_points;
        remove_rank_effect();
    }
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
    return ((right_child != nullptr && right_child->is_active()) || (bottom_child != nullptr && bottom_child->is_active()));
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

void Talent::initialize_rank_descriptions(QMap<unsigned, QString>& description_map,
                                          const QString& base_str,
                                          const unsigned format_points,
                                          const QVector<QPair<unsigned, unsigned>>& format_values) {
    for (unsigned i = 0; i < format_points; ++i) {
        QString format_str = base_str;
        for (const auto& format_value : format_values) {
            format_str = format_str.arg(format_value.first + i * format_value.second);
        }

        description_map.insert(i + 1, format_str);
    }

    description_map[0] = description_map[1];
}

void Talent::initialize_rank_descriptions(QMap<unsigned, QString>& description_map,
                                          const QString& base_str,
                                          const unsigned format_points,
                                          const QVector<QPair<double, double>>& format_values) {
    for (unsigned i = 0; i < format_points; ++i) {
        QString format_str = base_str;
        for (const auto& format_value : format_values) {
            format_str = format_str.arg(format_value.first + i * format_value.second);
        }

        description_map.insert(i + 1, format_str);
    }

    description_map[0] = description_map[1];
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
