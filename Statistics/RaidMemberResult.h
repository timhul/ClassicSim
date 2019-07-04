#pragma once

#include <QString>

class RaidMemberResult {
public:
    RaidMemberResult(const QString& player_name, const QString& class_color, const double dps, const int iterations) :
        player_name(player_name),
        class_color(class_color),
        dps(dps),
        iterations(iterations)
    {}

    const QString player_name;
    const QString class_color;
    double dps;
    int iterations;
};
