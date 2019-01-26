#ifndef TALENT_H
#define TALENT_H

#include <QMap>
#include <QString>
#include <QVector>
#include <assert.h>

class Buff;
class Character;
class Proc;
class Spell;
class TalentRequirer;
class TalentTree;

class Talent {
public:
    Talent(Character* pchar_,
           TalentTree *tree_,
           QString name_,
           QString position_,
           QString icon_,
           const int max_points_,
           QMap<int, QString> rank_descriptions = {},
           QVector<Spell*> affected_spells = {},
           QVector<Buff*> affected_buffs = {},
           QVector<Proc*> affected_procs = {}
           );
    virtual ~Talent();

    QString get_name() const;
    QString get_icon() const;
    QString get_position() const;
    QString get_right_arrow_image() const;
    QString get_bottom_arrow_image() const;

    QString get_requirement_string() const;
    QString get_current_rank_description() const;
    QString get_next_rank_description() const;
    int get_current_rank() const;
    int get_max_rank() const;
    bool increment_rank();
    bool decrement_rank();

    void force_clear_rank();

    bool is_active() const;
    bool is_maxed() const;

    bool has_parent() const;
    bool has_right_child() const;
    bool has_bottom_child() const;
    Talent* get_parent() const;
    Talent* get_bottom_child() const;
    Talent* get_right_child() const;

    void set_parent(Talent*);
    void set_bottom_child(Talent*);
    void set_right_child(Talent*);

    static void initialize_rank_descriptions(QMap<int, QString>& description_map, const QString &base_str, const int format_points, const QVector<QPair<int, int> > &format_values);
    static void initialize_rank_descriptions(QMap<int, QString>& description_map, const QString &base_str, const int format_points, const QVector<QPair<double, double> > &format_values);

protected:
    Character* pchar;
    TalentTree* tree;
    const QString name;
    const QString position;
    const QString icon;
    const int max_points;
    int curr_points;
    QVector<Spell*> affected_spells;
    QVector<Buff*> affected_buffs;
    QVector<Proc*> affected_procs;

    Talent* parent;
    Talent* right_child;
    Talent* bottom_child;

    QMap<int, QString> rank_descriptions;

    bool any_child_active() const;
    QString get_arrow_identifier(const QString& target_position) const;

    virtual void apply_rank_effect();
    virtual void remove_rank_effect();

private:

};


#endif // TALENT_H
