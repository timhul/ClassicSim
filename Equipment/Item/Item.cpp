
#include "Item.h"
#include "Stats.h"
#include "Target.h"
#include <QDebug>

Item::Item(QString _name, QVector<QPair<QString, QString>> _stats, QMap<QString, QString> _info):
    name(_name), info(_info)
{
    this->stats = new Stats();
    set_stats(_stats);
    set_item_slot(info);
}

Item::~Item() {
    delete stats;
}

void Item::set_item_slot(const QMap<QString, QString>& info) {
    slot = -1;
    if (!info.contains("slot")) {
        return;
    }

    slot = get_slot_int(info["slot"]);
}

int Item::get_item_slot(void) const {
    return slot;
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

const Stats* Item::get_stats() const {
    return this->stats;
}

void Item::set_stat(const QString& key, const QString &value) {
    if (key == "STRENGTH") {
        this->stats->increase_str(value.toInt());
        base_tooltip_stats.append(QString("+%1 Strength").arg(value));
    }
    else if (key == "AGILITY") {
        this->stats->increase_agi(value.toInt());
        base_tooltip_stats.append(QString("+%1 Agility").arg(value));
    }
    else if (key == "STAMINA") {
        this->stats->increase_stam(value.toInt());
        base_tooltip_stats.append(QString("+%1 Stamina").arg(value));
    }
    else if (key == "INTELLECT") {
        this->stats->increase_int(value.toInt());
        base_tooltip_stats.append(QString("+%1 Intellect").arg(value));
    }
    else if (key == "SPIRIT") {
        this->stats->increase_spi(value.toInt());
        base_tooltip_stats.append(QString("+%1 Spirit").arg(value));
    }
    else if (key == "CRIT_CHANCE") {
        this->stats->increase_crit(value.toFloat());
        QString number = QString::number(value.toFloat() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to get a critical strike by %1%.").arg(number));
    }
    else if (key == "HIT_CHANCE") {
        this->stats->increase_hit(value.toFloat());
        QString number = QString::number(value.toFloat() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to hit by %1%.").arg(number));
    }
    else if (key == "ATTACK_POWER") {
        this->stats->increase_base_melee_ap(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power.").arg(value));
    }
    else if (key == "ATTACK_POWER_BEAST") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Beast, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Beasts.").arg(value));
    }
    else if (key == "ATTACK_POWER_DEMON") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Demon, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Demons.").arg(value));
    }
    else if (key == "ATTACK_POWER_DRAGONKIN") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Dragonkin, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Dragonkin.").arg(value));
    }
    else if (key == "ATTACK_POWER_UNDEAD") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Undead, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Undead.").arg(value));
    }
    else if (key == "AXE_SKILL") {
        this->stats->increase_axe_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Axes +%1.").arg(value));
    }
    else if (key == "DAGGER_SKILL") {
        this->stats->increase_dagger_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Daggers +%1.").arg(value));
    }
    else if (key == "MACE_SKILL") {
        this->stats->increase_mace_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Maces +%1.").arg(value));
    }
    else if (key == "SWORD_SKILL") {
        this->stats->increase_sword_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Swords +%1.").arg(value));
    }
    else if (key == "ARMOR") {
        this->stats->increase_armor(value.toInt());
        base_tooltip_stats.append(QString("%1 Armor").arg(value));
    }
    else if (key == "DEFENSE") {
        this->stats->increase_defense(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Defense +%1.").arg(value));
    }
    else if (key == "DODGE_CHANCE") {
        this->stats->increase_dodge(value.toFloat());
        QString number = QString::number(value.toFloat() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to dodge an attack by %1%.").arg(number));
    }
    else if (key == "PARRY_CHANCE") {
        this->stats->increase_parry(value.toFloat());
        QString number = QString::number(value.toFloat() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to parry an attack by %1%.").arg(number));
    }
    else if (key == "ARCANE_RESISTANCE") {
        this->stats->increase_arcane_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Arcane Resistance").arg(value));
    }
    else if (key == "FIRE_RESISTANCE") {
        this->stats->increase_fire_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Fire Resistance").arg(value));
    }
    else if (key == "FROST_RESISTANCE") {
        this->stats->increase_frost_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Frost Resistance").arg(value));
    }
    else if (key == "HOLY_RESISTANCE") {
        this->stats->increase_holy_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Holy Resistance").arg(value));
    }
    else if (key == "NATURE_RESISTANCE") {
        this->stats->increase_nature_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Nature Resistance").arg(value));
    }
    else if (key == "SHADOW_RESISTANCE") {
        this->stats->increase_shadow_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Shadow Resistance").arg(value));
    }
    else
        unsupported_stat(key);
}

QString Item::get_base_stat_tooltip() const {
    return get_tooltip(base_tooltip_stats);
}

QString Item::get_equip_effect_tooltip() const {
    return get_tooltip(equip_effects_tooltip_stats);
}

QString Item::get_tooltip(const QVector<QString>& tt_strings) const {
    QString tooltip = "";
    for (int i = 0; i < tt_strings.size(); ++i) {
        if (tooltip != "")
            tooltip += "\n";
        tooltip += tt_strings[i];
    }

    return tooltip;
}

int get_slot_int(const QString& slot_string) {
    if (slot_string == "MAINHAND")
        return ItemSlots::MAINHAND;
    else if (slot_string == "OFFHAND")
        return ItemSlots::OFFHAND;
    else if (slot_string == "RANGED")
        return ItemSlots::RANGED;
    else if (slot_string == "HEAD")
        return ItemSlots::HEAD;
    else if (slot_string == "NECK")
        return ItemSlots::NECK;
    else if (slot_string == "SHOULDERS")
        return ItemSlots::SHOULDERS;
    else if (slot_string == "BACK")
        return ItemSlots::BACK;
    else if (slot_string == "CHEST")
        return ItemSlots::CHEST;
    else if (slot_string == "WRIST")
        return ItemSlots::WRIST;
    else if (slot_string == "GLOVES")
        return ItemSlots::GLOVES;
    else if (slot_string == "BELT")
        return ItemSlots::BELT;
    else if (slot_string == "LEGS")
        return ItemSlots::LEGS;
    else if (slot_string == "BOOTS")
        return ItemSlots::BOOTS;
    else if (slot_string == "RING")
        return ItemSlots::RING;
    else if (slot_string == "RING1")
        return ItemSlots::RING;
    else if (slot_string == "RING2")
        return ItemSlots::RING;
    else if (slot_string == "TRINKET")
        return ItemSlots::TRINKET;
    else if (slot_string == "TRINKET1")
        return ItemSlots::TRINKET;
    else if (slot_string == "TRINKET2")
        return ItemSlots::TRINKET;
    else if (slot_string == "CASTER_OFFHAND")
        return ItemSlots::CASTER_OFFHAND;
    else if (slot_string == "RELIC")
        return ItemSlots::RELIC;

    return -1;
}

void Item::unsupported_stat(const QString& stat) {
    qDebug() << "Unsupported stat" << stat << "has no effect on created item";
}
