#ifndef TALENTTREE_H
#define TALENTTREE_H

#include <QMap>
#include <QString>
#include <QVector>

class Buff;
class Character;
class Proc;
class Spell;
class SpellRankGroup;
class Talent;

class TalentTier {
public:
    void clear_points() {
        spent_points = 0;
    }

    void increment_point() {
        spent_points++;
    }

    void decrement_point() {
        spent_points--;
    }

    unsigned get_points() const {
        return spent_points;
    }

private:
    unsigned spent_points {0};
};

class TalentStorage {
public:
    TalentStorage(Talent* talent) :
        talent(talent)
    {}

    ~TalentStorage();

    Talent* talent;
    unsigned points_for_setup {0};
};


class TalentTree {
public:
    TalentTree(QString name_, QString background_);
    virtual ~TalentTree() = 0;

    QString get_name() const;
    QString get_background_image() const;
    QString get_icon(const QString& position);
    QString get_right_arrow(const QString& position);
    QString get_bottom_arrow(const QString& position);

    bool bottom_child_is_available(const QString& position) const;
    bool bottom_child_is_active(const QString& position) const;
    bool right_child_is_available(const QString& position) const;
    bool right_child_is_active(const QString& position) const;

    unsigned get_current_rank(const QString& position) const;
    unsigned get_max_rank(const QString& position) const;
    bool increment_rank(const QString& position);
    bool decrement_rank(const QString& position);

    QString get_talent_name(const QString& position) const;
    QString get_requirement_string(const QString& position) const;
    QString get_current_rank_description(const QString& position) const;
    QString get_next_rank_description(const QString& position) const;

    bool is_active(const QString& position) const;
    bool is_maxed(const QString& position) const;
    bool is_available(const QString& position) const;
    bool has_parent(const QString& position) const;
    bool has_right_child(const QString& position) const;
    bool has_bottom_child(const QString& position) const;

    int get_total_points() const;

    void clear_tree();
    void remove_rank_effects();
    void apply_rank_effects();

    QVector<QPair<QString, QString>> get_talent_tree_setup() const;

protected:
    const QString name;
    const QString background;
    const QString base_url;
    int total_spent_points;

    QMap<QString, TalentStorage*> talents;
    QVector<TalentTier*> tiers;

    void add_talents(const QMap<QString, Talent *> &new_talents);
    int get_highest_invested_tier() const;
    int get_investment_requirement_for_tier(const int tier) const;
    int get_points_spent_up_to_tier(const int tier) const;

    TalentTier* get_tier(const int tier) const;

    Talent* get_new_talent(Character* pchar, const QString& name, const QString& location, const QString& icon,
                           const unsigned max_points, const QString& rank_str,
                           const QVector<QPair<unsigned, unsigned>>& format_values,
                           const QVector<SpellRankGroup*> &affected_spells = {},
                           const QVector<Buff*>& affected_buffs = {},
                           const QVector<Proc*>& affected_procs = {}
                           );

    Talent* get_new_talent(Character* pchar, const QString& name, const QString& location, const QString& icon,
                           const unsigned max_points, const QString& rank_str,
                           const QVector<QPair<double, double>>& format_values,
                           const QVector<SpellRankGroup*> &affected_spells = {},
                           const QVector<Buff*>& affected_buffs = {},
                           const QVector<Proc*>& affected_procs = {}
                           );

private:
};

#endif // TALENTTREE_H
