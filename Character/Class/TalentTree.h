#ifndef TALENTTREE_H
#define TALENTTREE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>
#include <cassert>

class Character;
class Talent;


class TalentTier {
public:
    TalentTier():
        spent_points(0)
    {}

    void clear_points() {
        spent_points = 0;
    }

    void increment_point() {
        spent_points++;
    }

    void decrement_point() {
        spent_points--;
    }

    int get_points() const {
        return spent_points;
    }

private:
    int spent_points;
};

class TalentStorage {
public:
    TalentStorage(Talent* talent) :
        talent(talent),
        points_for_setup(0)
    {}

    ~TalentStorage();

    Talent* talent;
    int points_for_setup;
};


class TalentTree: public QObject {
    Q_OBJECT
public:
    TalentTree(QString name_, QString background_, QObject* parent = nullptr);
    virtual ~TalentTree() = 0;

    QString get_name() const;
    QString get_background_image() const;
    QString get_icon(const QString &position);
    QString get_right_arrow(const QString &position);
    QString get_bottom_arrow(const QString &position);

    bool bottom_child_is_available(const QString &position) const;
    bool bottom_child_is_active(const QString &position) const;
    bool right_child_is_available(const QString &position) const;
    bool right_child_is_active(const QString &position) const;

    int get_current_rank(const QString &position) const;
    int get_max_rank(const QString &position) const;
    bool increment_rank(const QString &position);
    bool decrement_rank(const QString &position);

    QString get_talent_name(const QString &position) const;
    QString get_requirement_string(const QString &position) const;
    QString get_current_rank_description(const QString &position) const;
    QString get_next_rank_description(const QString &position) const;

    bool is_active(const QString &position) const;
    bool is_maxed(const QString &position) const;
    bool is_available(const QString &position) const;
    bool has_parent(const QString &position) const;
    bool has_right_child(const QString &position) const;
    bool has_bottom_child(const QString &position) const;

    int get_total_points() const;

    void clear_tree();
    void remove_rank_effects();
    void apply_rank_effects();

    QVector<QPair<QString, QString>> get_talent_tree_setup() const;

protected:
    const QString name;
    const QString background;
    int total_spent_points;

    QMap<QString, TalentStorage*> talents;
    QVector<TalentTier*> tiers;

    void add_talents(const QMap<QString, Talent *> &new_talents);
    int get_highest_invested_rank() const;
    int get_investment_requirement_for_rank(const int rank) const;
    int get_points_spent_up_to_rank(const int rank) const;

    TalentTier* get_tier(const int tier) const;

private:
};

#endif // TALENTTREE_H
