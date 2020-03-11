#pragma once

#include <QString>

class RaidMemberResult {
public:
    RaidMemberResult(const QString& player_name, const QString& class_color, const double dps, const double tps, const int iterations) :
        player_name(player_name), class_color(class_color), dps(dps), tps(tps), iterations(iterations) {}

    const QString player_name;
    const QString class_color;
    double dps;
    double tps;
    int iterations;
};
