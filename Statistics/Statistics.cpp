
#include "Statistics.h"

int Statistics::get_int(std::string key) {
    if (int_stats.find(key) != int_stats.end())
        return int_stats.at(key);
    int_stats.insert(std::pair<std::string, int>(key, 0));
    return int_stats.at(key);
}

void Statistics::set_int(std::string key, int val) {
    if (int_stats.find(key) != int_stats.end())
        int_stats.at(key) = val;
    else
        int_stats.insert(std::pair<std::string, int>(key, val));
}

int Statistics::add(std::string key, int val) {
    if (int_stats.find(key) != int_stats.end()) {
        return int_stats.at(key) += val;
    }
    int_stats.insert(std::pair<std::string, int>(key, val));
    return int_stats.at(key);
}

int Statistics::increment(std::string key) {
    if (int_stats.find(key) != int_stats.end()) {
        return ++int_stats.at(key);
    }
    int_stats.insert(std::pair<std::string, int>(key, 1));
    return int_stats.at(key);
}

void Statistics::average(std::string key, int next_val) {
    int curr_sum = add(key + " SUM", next_val);
    int curr_n = increment(key + " TRIES");
    set_float(key + " AVG", float(curr_sum)/float(curr_n));
}

float Statistics::get_float(std::string key) {
    if (float_stats.find(key) != float_stats.end())
        return float_stats.at(key);
    float_stats.insert(std::pair<std::string, float>(key, 0.0));
    return float_stats.at(key);
}

void Statistics::set_float(std::string key, float val) {
    if (float_stats.find(key) != float_stats.end())
        float_stats.at(key) = val;
    else
        float_stats.insert(std::pair<std::string, float>(key, val));
}

void Statistics::dump(void) {
    for (auto it = int_stats.begin(); it != int_stats.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    for (auto it = float_stats.begin(); it != float_stats.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    if (int_stats.find("Total Damage") != int_stats.end())
        std::cout << "Total DPS: " << std::fixed << std::setprecision(1) << float(int_stats.at("Total Damage")) / 300 << "\n";
}
