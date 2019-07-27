#include "CharacterTalents.h"

#include <QDebug>

#include "Utils/Check.h"

CharacterTalents::CharacterTalents() :
    current_index(0),
    talent_points_remaining(QVector<int>{51, 51, 51})
{}

CharacterTalents::~CharacterTalents() {
    for (const auto & talent_tree : talent_trees) {
        for (const auto & i : talent_tree)
            delete i;
    }
}

QString CharacterTalents::get_background_image(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 1");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_background_image could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_background_image();
}

QString CharacterTalents::get_icon(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 2");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_icon could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_icon(talent_position);
}

bool CharacterTalents::show_position(const QString& tree_position, const QString& talent_position) const {
    return get_icon(tree_position, talent_position) != "";
}

bool CharacterTalents::show_bottom_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 3");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::show_bottom_arrow could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->has_bottom_child(talent_position);
}

bool CharacterTalents::show_right_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 4");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::show_right_arrow could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->has_right_child(talent_position);
}

QString CharacterTalents::get_bottom_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 5");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_bottom_arrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_bottom_arrow(talent_position);
}

QString CharacterTalents::get_right_arrow(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 6");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_right_arrow could not find tree position" << tree_position;
        return "";
    }

    return talent_trees[current_index][tree_position]->get_right_arrow(talent_position);
}

bool CharacterTalents::bottom_child_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 7");
    return talent_trees[current_index][tree_position]->bottom_child_is_available(talent_position);
}

bool CharacterTalents::right_child_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 8");
    return talent_trees[current_index][tree_position]->right_child_is_available(talent_position);
}

bool CharacterTalents::bottom_child_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 9");
    return talent_trees[current_index][tree_position]->bottom_child_is_active(talent_position);
}

bool CharacterTalents::right_child_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 10");
    return talent_trees[current_index][tree_position]->right_child_is_active(talent_position);
}

bool CharacterTalents::is_active(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 11");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_active could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->is_active(talent_position);
}

bool CharacterTalents::is_available(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 12");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_available could not find tree position" << tree_position;
        return false;
    }

    if (talent_points_remaining[current_index] == 0 && !talent_trees[current_index][tree_position]->is_active(talent_position))
        return false;

    return talent_trees[current_index][tree_position]->is_available(talent_position);
}

bool CharacterTalents::is_maxed(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 13");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::is_maxed could not find tree position" << tree_position;
        return false;
    }

    return talent_trees[current_index][tree_position]->is_maxed(talent_position);
}

bool CharacterTalents::has_talent_points_remaining() const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 14");
    return talent_points_remaining[current_index] > 0;
}

QString CharacterTalents::get_rank(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 15");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_rank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[current_index][tree_position]->get_current_rank(talent_position));
}

QString CharacterTalents::get_max_rank(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 16");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_max_rank could not find tree position" << tree_position;
        return "0";
    }

    return QString::number(talent_trees[current_index][tree_position]->get_max_rank(talent_position));
}

bool CharacterTalents::increment_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 17");
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

bool CharacterTalents::decrement_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 18");
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

QString CharacterTalents::get_requirements(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 19");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_requirements could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_requirement_string(talent_position);
}

QString CharacterTalents::get_current_rank_description(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 20");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_current_rank_description could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_current_rank_description(talent_position);
}

QString CharacterTalents::get_next_rank_description(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 21");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_next_rank_description could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_next_rank_description(talent_position);
}

int CharacterTalents::get_tree_points(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 22");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_tree_points could not find tree position" << tree_position;
        return 0;
    }

    return talent_trees[current_index][tree_position]->get_total_points();
}

QString CharacterTalents::get_tree_name(const QString& tree_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 23");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_tree_name could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_name();
}

QString CharacterTalents::get_talent_name(const QString& tree_position, const QString& talent_position) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 24");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::get_talent_name could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_talent_name(talent_position);
}

QString CharacterTalents::get_talent_position(const QString& tree_position, const QString& talent_name) const {
    check((current_index >= 0 && current_index < talent_trees.size()), "CharacterTalents::get_talent_position() Index out of range");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "CharacterTalents::get_talent_position() could not find tree position" << tree_position;
        return "Missing tree!";
    }

    return talent_trees[current_index][tree_position]->get_position_from_talent_name(talent_name);
}

void CharacterTalents::increase_to_max_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 25");
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

void CharacterTalents::decrease_to_min_rank(const QString& tree_position, const QString& talent_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 26");
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

void CharacterTalents::clear_tree(const QString& tree_position) {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 27");
    if (!talent_trees[current_index].contains(tree_position)) {
        qDebug() << "Talents::clear_tree could not find tree position" << tree_position;
        return;
    }

    int points_refunded = talent_trees[current_index][tree_position]->get_total_points();
    talent_trees[current_index][tree_position]->clear_tree();
    talent_points_remaining[current_index] += points_refunded;
    check((talent_points_remaining[current_index] <= 51), "Remaining talent points exceed maximum");
}

void CharacterTalents::set_current_index(const int index) {
    if (index < 0 || index >= talent_trees.size())
        return;

    for (const auto & tree : talent_trees[current_index])
            tree->remove_rank_effects();

    current_index = index;

    for (const auto & tree : talent_trees[current_index])
            tree->apply_rank_effects();
}

void CharacterTalents::add_talent_tree(TalentTree* left_tree, TalentTree* mid_tree, TalentTree *right_tree) {
    QMap<QString, TalentTree*> map;
    map.insert("LEFT", left_tree);
    map.insert("MID", mid_tree);
    map.insert("RIGHT", right_tree);
    talent_trees.append(map);
}

int CharacterTalents::get_talent_points_remaining() const {
    check((current_index >= 0 && current_index < talent_trees.size()), "Index out of range 28");
    return talent_points_remaining[current_index];
}

QVector<QPair<QString, QVector<QPair<QString, QString>>>> CharacterTalents::get_current_talent_setup() const {
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
