#include "TalentTree.h"

#include <utility>

#include "Talent.h"
#include "Utils/Check.h"

TalentStorage::~TalentStorage() {
    delete talent;
}

TalentTree::TalentTree(QString name_, QString background_) :
    name(std::move(name_)),
    background(std::move(background_)),
    base_url("Assets/"),
    total_spent_points(0),
    talents(QMap<QString, TalentStorage*>())
{
    for (int i = 0; i < 7; ++i) {
        tiers.append(new TalentTier());
    }
}

TalentTree::~TalentTree() {
    for (const auto & talent_storage : talents)
        delete talent_storage;

    for (const auto & tier :  tiers) {
        delete tier;
    }
}

QString TalentTree::get_name() const {
    return name;
}

QString TalentTree::get_background_image() const {
    return background;
}

QString TalentTree::get_talent_name(const QString& position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->talent->get_name();
}

QString TalentTree::get_requirement_string(const QString& position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->talent->get_requirement_string();
}

QString TalentTree::get_current_rank_description(const QString& position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->talent->get_current_rank_description();
}

QString TalentTree::get_next_rank_description(const QString& position) const {
    if (!talents.contains(position))
        return "Missing talent!";

    return talents[position]->talent->get_next_rank_description();
}

void TalentTree::add_talents(const QMap<QString, Talent*> &new_talents) {
    for (const auto & it : new_talents.toStdMap()) {
        check(!talents.contains(it.first), "Attempted to insert talent twice");
        talents.insert(it.first, new TalentStorage(it.second));
    }
}

QString TalentTree::get_icon(const QString& position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->talent->get_icon();
}

QString TalentTree::get_right_arrow(const QString& position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->talent->get_right_arrow_image();
}

QString TalentTree::get_bottom_arrow(const QString& position) {
    if (!talents.contains(position))
        return "";

    return talents[position]->talent->get_bottom_arrow_image();
}

bool TalentTree::bottom_child_is_available(const QString& position) const {
    if (!talents.contains(position) || !talents[position]->talent->has_bottom_child() || !is_maxed(position)) {
        return false;
    }

    QString child_pos = talents[position]->talent->get_bottom_child()->get_position();

    return total_spent_points >= (QString(child_pos[0]).toInt() - 1) * 5;
}

bool TalentTree::bottom_child_is_active(const QString& position) const {
    if (!talents.contains(position) || !talents[position]->talent->has_bottom_child()) {
        return false;
    }

    return talents[position]->talent->get_bottom_child()->is_active();
}

bool TalentTree::right_child_is_available(const QString& position) const {
    if (!talents.contains(position) || !talents[position]->talent->has_right_child() || !is_maxed(position))
        return false;

    QString child_pos = talents[position]->talent->get_right_child()->get_position();

    return total_spent_points >= (QString(child_pos[0]).toInt() - 1) * 5;
}

bool TalentTree::right_child_is_active(const QString& position) const {
    if (!talents.contains(position) || !talents[position]->talent->has_right_child()) {
        return false;
    }

    return talents[position]->talent->get_right_child()->is_active();
}

unsigned TalentTree::get_current_rank(const QString& position) const {
    if (!talents.contains(position))
        return 0;

    return talents[position]->talent->get_current_rank();
}

unsigned TalentTree::get_max_rank(const QString& position) const {
    if (!talents.contains(position))
        return 0;

    return talents[position]->talent->get_max_rank();
}

bool TalentTree::increment_rank(const QString& position) {
    if (!talents.contains(position) || !is_available(position))
        return false;

    if (talents[position]->talent->increment_rank()) {
        ++total_spent_points;
        get_tier(QString(position[0]).toInt() - 1)->increment_point();
        return true;
    }

    return false;
}

bool TalentTree::decrement_rank(const QString& position) {
    if (!talents.contains(position))
        return false;

    if (bottom_child_is_active(position) || right_child_is_active(position))
        return false;

    int tier_under_investigation = get_highest_invested_tier();
    int tier_to_be_decremented = QString(position[0]).toInt();

    while (tier_under_investigation > tier_to_be_decremented) {
        int attempted_decrement = get_points_spent_up_to_tier(tier_under_investigation) - 1;
        int minimum_requirement = get_investment_requirement_for_tier(tier_under_investigation);

        if (attempted_decrement < minimum_requirement) {
            return false;
        }

        --tier_under_investigation;
    }

    if (talents[position]->talent->decrement_rank()) {
        --total_spent_points;
        get_tier(QString(position[0]).toInt() - 1)->decrement_point();
        return true;
    }

    return false;
}

bool TalentTree::is_active(const QString& position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->talent->is_active();
}

bool TalentTree::is_maxed(const QString& position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->talent->is_maxed();
}

bool TalentTree::is_available(const QString& position) const {
    if (!talents.contains(position))
        return false;

    if (has_parent(position) && !talents[position]->talent->get_parent()->is_maxed())
        return false;

    return total_spent_points >= (QString(position[0]).toInt() - 1) * 5;
}

bool TalentTree::has_parent(const QString& position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->talent->has_parent();
}

bool TalentTree::has_right_child(const QString& position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->talent->has_right_child();
}

bool TalentTree::has_bottom_child(const QString& position) const {
    if (!talents.contains(position))
        return false;

    return talents[position]->talent->has_bottom_child();
}

int TalentTree::get_highest_invested_tier() const {
    if (get_tier(6)->get_points() > 0)
        return 7;
    if (get_tier(5)->get_points() > 0)
        return 6;
    if (get_tier(4)->get_points() > 0)
        return 5;
    if (get_tier(3)->get_points() > 0)
        return 4;
    if (get_tier(2)->get_points() > 0)
        return 3;
    if (get_tier(1)->get_points() > 0)
        return 2;
    if (get_tier(0)->get_points() > 0)
        return 1;
    return 0;
}

int TalentTree::get_investment_requirement_for_tier(const int tier) const {
    return (tier - 1) * 5;
}

int TalentTree::get_points_spent_up_to_tier(const int tier) const {
    int invested_below_rank = 0;

    switch (tier) {
    case 7:
        invested_below_rank += get_tier(5)->get_points();
        // C++17 [[clang::fallthrough]];
    case 6:
        invested_below_rank += get_tier(4)->get_points();
        // C++17 [[clang::fallthrough]];
    case 5:
        invested_below_rank += get_tier(3)->get_points();
        // C++17 [[clang::fallthrough]];
    case 4:
        invested_below_rank += get_tier(2)->get_points();
        // C++17 [[clang::fallthrough]];
    case 3:
        invested_below_rank += get_tier(1)->get_points();
        // C++17 [[clang::fallthrough]];
    case 2:
        invested_below_rank += get_tier(0)->get_points();
    }

    return invested_below_rank;
}

int TalentTree::get_total_points() const {
    return total_spent_points;
}

void TalentTree::clear_tree() {
    for (const auto & talent_storage : talents)
        talent_storage->talent->force_clear_rank();

    for (const auto & tier : tiers) {
        tier->clear_points();
    }

    total_spent_points = 0;
}

void TalentTree::remove_rank_effects() {
    for (const auto & talent_storage : talents) {
        talent_storage->points_for_setup = talent_storage->talent->get_current_rank();
        for (unsigned i = 0; i < talent_storage->points_for_setup; ++i)
            talent_storage->talent->force_clear_rank();
    }
}

void TalentTree::apply_rank_effects() {
    for (const auto & talent_storage : talents) {
        for (unsigned i = 0; i < talent_storage->points_for_setup; ++i) {
            talent_storage->talent->increment_rank();
        }
    }
}

TalentTier* TalentTree::get_tier(const int tier) const {
    if (tier < 0 || tier >= tiers.size())
        return nullptr;
    return tiers[tier];
}

QVector<QPair<QString, QString>> TalentTree::get_talent_tree_setup() const {
    QVector<QString> suffixes = {"LL", "ML", "MR", "RR"};
    QVector<QPair<QString, QString>> talent_tree_setup;

    for (int tier = 0; tier < 7; ++tier) {
        for (const auto & suffix : suffixes) {
            QString position = QString("%1%2").arg(QString::number(tier + 1), suffix);

            if (!talents.contains(position) || !talents[position]->talent->is_active())
                continue;

            talent_tree_setup.append(QPair<QString, QString>(position, QString::number(talents[position]->talent->get_current_rank())));
        }
    }

    return talent_tree_setup;
}

Talent* TalentTree::get_new_talent(Character* pchar, const QString& name, const QString& location,
                                   const QString& icon, const unsigned max_points, const QString& rank_str,
                                   const QVector<QPair<unsigned, unsigned>>& format_values,
                                   const QVector<SpellRankGroup*>& affected_spells,
                                   const QVector<Buff*>& affected_buffs,
                                   const QVector<Proc*>& affected_procs
                                   )
{
    QMap<unsigned, QString> rank_descriptions;
    if (max_points > 1)
        Talent::initialize_rank_descriptions(rank_descriptions, rank_str, max_points, format_values);
    else {
        rank_descriptions.insert(0, rank_str);
        rank_descriptions.insert(1, rank_str);
    }
    return new Talent(pchar, this, name, location, icon, max_points, rank_descriptions,
                      affected_spells, affected_buffs, affected_procs);
}

Talent* TalentTree::get_new_talent(Character* pchar, const QString& name, const QString& location,
                                   const QString& icon, const unsigned max_points, const QString& rank_str,
                                   const QVector<QPair<double, double>>& format_values,
                                   const QVector<SpellRankGroup*>& affected_spells,
                                   const QVector<Buff*>& affected_buffs,
                                   const QVector<Proc*>& affected_procs
                                   )
{
    QMap<unsigned, QString> rank_descriptions;
    if (max_points > 1)
        Talent::initialize_rank_descriptions(rank_descriptions, rank_str, max_points, format_values);
    else {
        rank_descriptions.insert(0, rank_str);
        rank_descriptions.insert(1, rank_str);
    }
    return new Talent(pchar, this, name, location, icon, max_points, rank_descriptions,
                      affected_spells, affected_buffs, affected_procs);
}
