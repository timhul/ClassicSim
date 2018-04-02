
#include "Statistics.h"
#include <QDebug>

int Statistics::get_int(QString key) {
    if (int_stats.find(key) != int_stats.end())
        return int_stats[key];
    int_stats[key] = 0;
    return 0;
}

void Statistics::set_int(QString key, int val) {
    int_stats[key] = val;
}

int Statistics::add(QString key, int val) {
    if (int_stats.find(key) != int_stats.end()) {
        return int_stats[key] += val;
    }

    set_int(key, val);
    return val;
}

int Statistics::increment(QString key) {
    if (int_stats.find(key) != int_stats.end()) {
        return ++int_stats[key];
    }

    set_int(key, 1);
    return 1;
}

void Statistics::average(QString key, int next_val) {
    int curr_sum = add(key + " SUM", next_val);
    int curr_n = increment(key + " TRIES");
    set_float(key + " AVG", float(curr_sum)/float(curr_n));
}

float Statistics::get_float(QString key) {
    if (float_stats.find(key) != float_stats.end())
        return float_stats[key];

    set_float(key, 0.0);
    return 0.0;
}

void Statistics::set_float(QString key, float val) {
    float_stats[key] = val;
}

int Statistics::get_total_damage() {
    if (int_stats.find("Total Damage") != int_stats.end())
        return int_stats["Total Damage"];

    return 0;
}

void Statistics::dump(void) {
    QMap<QString, int>::const_iterator i = int_stats.constBegin();
    while (i != int_stats.constEnd()) {
        qDebug() << i.key() << "=>" << i.value();
        ++i;
    }

    QMap<QString, float>::const_iterator j = float_stats.constBegin();
    while (j != float_stats.constEnd()) {
        qDebug() << j.key() << "=>" << j.value();
        ++j;
    }

    // TODO: Remove hardcoded fight length of 300 seconds.
    qDebug() << "Total DPS: " << get_total_damage() / 300;
}

void Statistics::clear() {
    qDebug() << "Clearing statistics";
    float_stats.clear();
    int_stats.clear();
}
