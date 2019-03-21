#include "Talents.h"

#include <QDebug>

#include "Utils/Check.h"

Talents::Talents() :
    current_index(0),
    talent_points_remaining(QVector<int>{51, 51, 51})
{}

Talents::~Talents() {
    for (auto & talent_tree : talent_trees) {
        QMap<QString, TalentTree*>::const_iterator it = talent_tree.constBegin();
        auto end = talent_tree.constEnd();
        while(it != end) {
            delete it.value();
            ++it;
        }
    }
}

QString Talents::get_background_image(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_background_image could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_background_image();
}

QString Talents::get_icon(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_icon could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_icon(talent_position);
}

bool Talents::show_position(const QString& tree_position, const QString& talent_position) const {
    return get_icon(tree_position, talent_position) != "";
}

bool Talents::show_bottom_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::show_bottom_arrow could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->has_bottom_child(talent_position);
}

bool Talents::show_right_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::show_right_arrow could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->has_right_child(talent_position);
}

QString Talents::get_bottom_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_bottom_arrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_bottom_arrow(talent_position);
}

QString Talents::get_right_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_right_arrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_right_arrow(talent_position);
}

bool Talents::bottom_child_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_trees[current_index][tree_position]->bottom_child_is_available(talent_position);
}

bool Talents::right_child_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_trees[current_index][tree_position]->right_child_is_available(talent_position);
}

bool Talents::bottom_child_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_trees[current_index][tree_position]->bottom_child_is_active(talent_position);
}

bool Talents::right_child_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_trees[current_index][tree_position]->right_child_is_active(talent_position);
}

bool Talents::is_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_active could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->is_active(talent_position);
}

bool Talents::is_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_available could not find tree position" << tree_position;
        return false;
    }

    if (talent_points_remaining[current_index] == 0 && !talent_trees[current_index][tree_position]->is_active(talent_position))
        return false;

    return talent_trees[current_index][tree_position]->is_available(talent_position);
}

bool Talents::is_maxed(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_maxed could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->is_maxed(talent_position);
}

bool Talents::has_talent_points_remaining() const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_points_remaining[current_index] > 0;
}

QString Talents::get_rank(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_rank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[current_index][tree_position]->get_current_rank(talent_position));
}

QString Talents::get_max_rank(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_max_rank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[current_index][tree_position]->get_max_rank(talent_position));
}

bool Talents::increment_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::increment_rank could not find tree position" << tree_position;
        return false;
    }

    check((talent_points_remaining[current_index] >= 0), "Talent points remaining must be a positive value");

    if (talent_points_remaining[current_index] == 0)
        return false;

    if (talent_trees[current_index][tree_position]->increment_rank(talent_position)) {
        --talent_points_remaining[current_index];
        return true;
    }

    return false;
}

bool Talents::decrement_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::decrement_rank could not find tree position" << tree_position;
        return false;
    }

    check((talent_points_remaining[current_index] >= 0), "Talent points remaining must be a positive value");

    if (talent_points_remaining[current_index] == 51)
        return false;

    if (talent_trees[current_index][tree_position]->decrement_rank(talent_position)) {
        ++talent_points_remaining[current_index];
        return true;
    }

    return false;
}

QString Talents::get_requirements(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_requirements could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_requirement_string(talent_position);
}

QString Talents::get_current_rank_description(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_current_rank_description could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_current_rank_description(talent_position);
}

QString Talents::get_next_rank_description(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_next_rank_description could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_next_rank_description(talent_position);
}

int Talents::get_tree_points(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_tree_points could not find tree position" << tree_position;
        return 0;
    }

    return talent_trees[current_index][tree_position]->get_total_points();
}

QString Talents::get_tree_name(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_tree_name could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_name();
}

QString Talents::get_talent_name(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_talent_name could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_talent_name(talent_position);
}

void Talents::increase_to_max_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::increase_to_max_rank could not find tree position" << tree_position;
        return;
    }

    while (talent_points_remaining[current_index] > 0 && !talent_trees[current_index][tree_position]->is_maxed(talent_position)) {
        if (talent_trees[current_index][tree_position]->increment_rank(talent_position))
            --talent_points_remaining[current_index];
        else
            break;
    }
}

void Talents::decrease_to_min_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::decrease_to_min_rank could not find tree position" << tree_position;
        return;
    }

    while (talent_points_remaining[current_index] < 51 && talent_trees[current_index][tree_position]->is_active(talent_position)) {
        if (talent_trees[current_index][tree_position]->decrement_rank(talent_position))
            ++talent_points_remaining[current_index];
        else
            break;
    }
}

void Talents::clear_tree(const QString& tree_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::clear_tree could not find tree position" << tree_position;
        return;
    }

    int points_refunded = talent_trees[current_index][tree_position]->get_total_points();
    talent_trees[current_index][tree_position]->clear_tree();
    talent_points_remaining[current_index] += points_refunded;
    check((talent_points_remaining[current_index] <= 51), "Remaining talent points exceed maximum");
}

void Talents::set_current_index(const int index) {
    if (index < 0 || index >= talent_trees.size())
        return;

    QMap<QString, TalentTree*>::const_iterator it = talent_trees[current_index].constBegin();
    auto end = talent_trees[current_index].constEnd();
    while(it != end) {
        if (it.value() != nullptr)
            it.value()->remove_rank_effects();
        ++it;
    }

    current_index = index;
    it = talent_trees[current_index].constBegin();
    end = talent_trees[current_index].constEnd();

    while(it != end) {
        if (it.value() != nullptr)
            it.value()->apply_rank_effects();
        ++it;
    }
}

void Talents::add_talent_tree(TalentTree* left_tree, TalentTree* mid_tree, TalentTree *right_tree) {
    QMap<QString, TalentTree*> map;
    map.insert("LEFT", left_tree);
    map.insert("MID", mid_tree);
    map.insert("RIGHT", right_tree);
    talent_trees.append(map);
}

int Talents::get_talent_points_remaining() const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range");
    return talent_points_remaining[current_index];
}

QVector<QPair<QString, QVector<QPair<QString, QString>>>> Talents::get_current_talent_setup() const {
    QVector<QPair<QString, QVector<QPair<QString, QString>>>> talents;
    QPair<QString, QVector<QPair<QString, QString>>> entry;

    QVector<QPair<QString, QString>> setup = talent_trees[current_index]["LEFT"]->get_talent_tree_setup();
    if (!setup.empty()) {
        entry.first = "LEFT";
        entry.second = setup;
        talents.append(entry);
    }

    setup = talent_trees[current_index]["MID"]->get_talent_tree_setup();
    if (!setup.empty()) {
        entry.first = "MID";
        entry.second = setup;
        talents.append(entry);
    }

    setup = talent_trees[current_index]["RIGHT"]->get_talent_tree_setup();
    if (!setup.empty()) {
        entry.first = "RIGHT";
        entry.second = setup;
        talents.append(entry);
    }

    return talents;
}
