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
    Q_INVOKABLE void leftClickedPosition(const int tier, const QString position);

protected:
    const QString name;

    QMap<QString, Talent*> talents;

    void add_talents(const QMap<QString, Talent *> &new_talents);

private:
};

#endif // TALENTTREE_H
