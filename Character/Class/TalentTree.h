#ifndef TALENTTREE_H
#define TALENTTREE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <assert.h>

class Character;
class Talent;

class TalentTree: public QObject {
    Q_OBJECT
public:
    TalentTree(const QString &name_, QObject* parent = 0);
    virtual ~TalentTree() = 0;

    QString get_name() const;
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
    bool has_right_child(const QString &position) const;
    bool has_bottom_child(const QString &position) const;

    int get_total_points() const;

    void clear_tree();

protected:
    const QString name;
    int total_spent_points;

    QMap<QString, Talent*> talents;
    QMap<QString, int> spent_points;


    void add_talents(const QMap<QString, Talent *> &new_talents);

    QString get_highest_invested_rank() const;
    int get_investment_requirement_for_rank(const int rank) const;
    int get_points_spent_up_to_rank(const int rank) const;

private:
};

#endif // TALENTTREE_H
