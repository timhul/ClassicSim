
#include "Statistics.h"
#include <QDebug>

int Statistics::get_int(QString key) {
    if (int_stats.find(key) != int_stats.end())
        return int_stats.at(key);
    int_stats.insert(std::pair<QString, int>(key, 0));
    return int_stats.at(key);
}

void Statistics::set_int(QString key, int val) {
    if (int_stats.find(key) != int_stats.end())
        int_stats.at(key) = val;
    else
        int_stats.insert(std::pair<QString, int>(key, val));
}

int Statistics::add(QString key, int val) {
    if (int_stats.find(key) != int_stats.end()) {
        return int_stats.at(key) += val;
    }
    int_stats.insert(std::pair<QString, int>(key, val));
    return int_stats.at(key);
}

int Statistics::increment(QString key) {
    if (int_stats.find(key) != int_stats.end()) {
        return ++int_stats.at(key);
    }
    int_stats.insert(std::pair<QString, int>(key, 1));
    return int_stats.at(key);
}

void Statistics::average(QString key, int next_val) {
    int curr_sum = add(key + " SUM", next_val);
    int curr_n = increment(key + " TRIES");
    set_float(key + " AVG", float(curr_sum)/float(curr_n));
}

float Statistics::get_float(QString key) {
    if (float_stats.find(key) != float_stats.end())
        return float_stats.at(key);
    float_stats.insert(std::pair<QString, float>(key, 0.0));
    return float_stats.at(key);
}

void Statistics::set_float(QString key, float val) {
    if (float_stats.find(key) != float_stats.end())
        float_stats.at(key) = val;
    else
        float_stats.insert(std::pair<QString, float>(key, val));
}

void Statistics::dump(void) {
    for (auto it = int_stats.begin(); it != int_stats.end(); ++it) {
        qDebug() << it->first << " => " << it->second;
    }

    for (auto it = float_stats.begin(); it != float_stats.end(); ++it) {
        qDebug() << it->first << " => " << it->second;
    }

    if (int_stats.find("Total Damage") != int_stats.end())
        qDebug() << "Total DPS: " << float(int_stats.at("Total Damage")) / 300;
}
