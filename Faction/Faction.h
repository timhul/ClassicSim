#pragma once

#include <QVector>
#include <QString>

#include "AvailableFactions.h"

class Race;


class Faction {
public:
    Faction(Race*);

    int get_faction() const;
    AvailableFactions::Name get_faction_as_enum() const;
    void switch_faction();

    const QVector<QString>& get_faction_races() const;

    bool is_alliance() const;
    bool is_horde() const;

private:
    AvailableFactions::Name current_faction;
    const QVector<QString> alliance_races;
    const QVector<QString> horde_races;

    const QVector<QString> alliance_classes;
    const QVector<QString> horde_classes;
};
