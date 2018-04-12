
#include "Item.h"
#include "Stats.h"
#include <QDebug>

Item::Item(QString _name, QVector<QPair<QString, QString>> _stats, QMap<QString, QString> _info):
    name(_name), info(_info)
{
    this->stats = new Stats();
    set_stats(_stats);
}

Item::~Item() {
    delete stats;
}

QString Item::get_name(void) const {
    return name;
}

void Item::set_stats(QVector<QPair<QString, QString>> stats) {
    for (int i = 0; i < stats.size(); ++i)
        set_stat(stats[i].first, stats[i].second);
}

QString Item::get_value(const QString& key) const {
    return info.contains(key) ? info[key] : "";
}

void Item::set_stat(const QString& key, const QString &value) {
    if (key == "STRENGTH") {
        this->stats->increase_str(value.toInt());
    }
    else if (key == "AGILITY") {
        this->stats->increase_agi(value.toInt());
    }
    else if (key == "STAMINA") {
        this->stats->increase_stam(value.toInt());
    }
    else if (key == "INTELLECT") {
        this->stats->increase_int(value.toInt());
    }
    else if (key == "SPIRIT") {
        this->stats->increase_spi(value.toInt());
    }
    else if (key == "CRIT_CHANCE") {
        this->stats->increase_crit(value.toFloat());
    }
    else if (key == "HIT_CHANCE") {
        this->stats->increase_hit(value.toFloat());
    }
    else if (key == "ATTACK_POWER") {
        this->stats->increase_base_melee_ap(value.toInt());
    }
    else
        unsupported_stat(key);
}

void Item::unsupported_stat(const QString& stat) {
    qDebug() << "Unsupported stat" << stat << "has no effect on created item";
}
