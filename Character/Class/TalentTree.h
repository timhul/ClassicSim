#ifndef TALENTTREE_H
#define TALENTTREE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <assert.h>

class Talent;

class TalentTree: public QObject {
    Q_OBJECT
public:
    TalentTree(const QString &name_, QObject* parent = 0);
    virtual ~TalentTree() = 0;

    QString get_name() const;
    QString get_icon(const QString &position);

    int get_current_rank(const QString &position) const;
    int get_max_rank(const QString &position) const;
    bool increment_rank(const QString &position);
    bool decrement_rank(const QString &position);
    void set_rank(const QString &position, const int);

    bool is_active(const QString &position) const;
    bool is_maxed(const QString &position) const;
    bool is_available(const QString &position) const;

protected:
    const QString name;
    int spent_points;

    QMap<QString, Talent*> talents;

    void add_talents(const QMap<QString, Talent *> &new_talents);

private:
};

#endif // TALENTTREE_H
