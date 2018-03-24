#ifndef TALENTTREE_H
#define TALENTTREE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <assert.h>

class Talent;

class TalentTree {
public:
    TalentTree(const QString& name_);
    virtual ~TalentTree();

    QString get_name() const;
    Q_INVOKABLE void leftClickedPosition(const int tier, const QString position);

protected:
    const QString name;

    const QVector<QVector<Talent*>> matrix;

private:
};

#endif // TALENTTREE_H
