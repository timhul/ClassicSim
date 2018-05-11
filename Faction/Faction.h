#ifndef FACTION_H
#define FACTION_H

#include <QVector>
#include <QString>

class Faction {
public:
    Faction();

    bool get_faction() const;
    void switch_faction();

    const QVector<QString>& get_faction_races() const;
    const QVector<QString>& get_faction_classes() const;

    bool is_alliance() const;
    bool is_horde() const;

private:
    bool faction;
    const QVector<QString> alliance_races;
    const QVector<QString> horde_races;

    const QVector<QString> alliance_classes;
    const QVector<QString> horde_classes;
};

#endif // FACTION_H
