
#include "Item.h"
#include "Stats.h"
#include "Target.h"
#include "Character.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingProc.h"
#include <QDebug>

Item::Item(QString _name, QVector<QPair<QString, QString>> _stats, QMap<QString, QString> _info,
           QVector<QMap<QString, QString>> _procs):
    name(_name), info(_info), procs_map(_procs)
{
    this->stats = new Stats();
    set_stats(_stats);
    set_item_slot(info);
    set_item_type(info);
}

Item::~Item() {
    for (auto it : proc_map.keys()) {
        QVector<Proc*> procs_ = proc_map.value(it);
        for (int i = 0; i < procs_.size(); ++i) {
            procs_[i]->disable_proc();
            delete procs_[i];
        }
    }

    delete stats;
}

void Item::set_item_slot(const QMap<QString, QString>& info) {
    slot = -1;
    if (!info.contains("slot")) {
        return;
    }

    slot = get_slot_int(info["slot"]);
}

void Item::set_item_type(const QMap<QString, QString>& info) {
    item_type = -1;
    if (!info.contains("type")) {
        return;
    }

    item_type = get_type_int(info["type"]);
}

int Item::get_item_slot(void) const {
    return slot;
}

int Item::get_item_type(void) const {
    return this->item_type;
}

void Item::apply_equip_effect(Character* pchar, const int eq_slot) {
    if (pchar == nullptr)
        return;

    if (proc_map.contains(eq_slot))
        assert(proc_map.empty());

    set_procs(procs_map, pchar, eq_slot);
}

void Item::remove_equip_effect(Character* pchar, const int eq_slot) {
    if (pchar == nullptr || !proc_map.contains(eq_slot)) {
        if (proc_map.contains(eq_slot))
            assert(proc_map.empty());
        return;
    }

    QVector<Proc*> procs_ = proc_map.take(eq_slot);

    for (int i = 0; i < procs_.size(); ++i) {
        procs_[i]->disable_proc();
        delete procs_[i];
    }

    assert(!proc_map.contains(eq_slot));
}

QString Item::get_name(void) const {
    return name;
}

void Item::set_procs(QVector<QMap<QString, QString>>& procs, Character* pchar, const int eq_slot) {
    QVector<Proc*> procs_;
    for (int i = 0; i < procs.size(); ++i) {
        if (!proc_info_complete(procs[i])) {
            qDebug() << "Missing proc info for item" << get_name();
            continue;
        }

        QString proc_name = procs[i]["name"];
        QString instant = procs[i]["instant"].toLower();
        // TODO: Support recursive
        // QString recursive = procs[i]["recursive"];
        int amount = QString(procs[i]["amount"]).toInt();
        float internal_cd = QString(procs[i]["internal_cd"]).toFloat();
        float proc_rate = QString(procs[i]["rate"]).toFloat();

        if (amount < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(get_name(), proc_name, QString::number(amount));
            continue;
        }
        if (proc_rate < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(get_name(), proc_name, QString::number(proc_rate, 'f', 2));
            continue;
        }
        if (internal_cd < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(get_name(), proc_name, QString::number(internal_cd, 'f', 2));
            continue;
        }

        QVector<ProcInfo::Source> proc_sources;
        Proc* proc = nullptr;

        if (proc_name == "EXTRA_ATTACK") {
            switch (eq_slot) {
            case EquipmentSlot::MAINHAND:
                proc_sources.append(ProcInfo::Source::MainhandSwing);
                proc_sources.append(ProcInfo::Source::MainhandSpell);
                break;
            case EquipmentSlot::OFFHAND:
                proc_sources.append(ProcInfo::Source::OffhandSwing);
                proc_sources.append(ProcInfo::Source::OffhandSpell);
                break;
            default:
                proc_sources.append(ProcInfo::Source::MainhandSwing);
                proc_sources.append(ProcInfo::Source::MainhandSpell);
                proc_sources.append(ProcInfo::Source::OffhandSwing);
                proc_sources.append(ProcInfo::Source::OffhandSpell);
                break;
            }

            if (instant == "yes") {
                proc = new ExtraAttackInstantProc(pchar->get_engine(),
                                                  pchar,
                                                  pchar->get_combat_roll(),
                                                  get_name(),
                                                  proc_sources,
                                                  proc_rate,
                                                  amount);
            }
            else {
                proc = new ExtraAttackOnNextSwingProc(pchar->get_engine(),
                                                      pchar,
                                                      pchar->get_combat_roll(),
                                                      get_name(),
                                                      proc_sources,
                                                      proc_rate,
                                                      amount);
            }
        }

        if (proc != nullptr) {
            procs_.append(proc);
            proc->enable_proc();
        }
    }

    if (!procs_.empty())
        this->proc_map.insert(eq_slot, procs_);
}

bool Item::proc_info_complete(QMap<QString, QString> & proc) {
    QVector<QString> expected_keys = {"name", "instant", "recursive", "amount", "internal_cd",
                                     "rate"};
    QVector<QString> missing_keys;
    for (int i = 0; i < expected_keys.size(); ++i) {
        if (!proc.contains(expected_keys[i]))
            missing_keys.append(expected_keys[i]);
    }

    if (missing_keys.size() > 0) {
        qDebug() << "Missing proc info keys" << missing_keys;
        return false;
    }

    return true;
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

int Item::get_type_int(const QString& type_string) {
    if (type_string == "AXE")
        return WeaponTypes::AXE;
    else if (type_string == "DAGGER")
        return WeaponTypes::DAGGER;
    else if (type_string == "FIST")
        return WeaponTypes::FIST;
    else if (type_string == "MACE")
        return WeaponTypes::MACE;
    else if (type_string == "POLEARM")
        return WeaponTypes::POLEARM;
    else if (type_string == "STAFF")
        return WeaponTypes::STAFF;
    else if (type_string == "SWORD")
        return WeaponTypes::SWORD;
    else if (type_string == "BOW")
        return WeaponTypes::BOW;
    else if (type_string == "CROSSBOW")
        return WeaponTypes::CROSSBOW;
    else if (type_string == "GUN")
        return WeaponTypes::GUN;
    else if (type_string == "THROWN")
        return WeaponTypes::THROWN;
    else if (type_string == "WAND")
        return WeaponTypes::WAND;
    else if (type_string == "IDOL")
        return WeaponTypes::IDOL;
    else if (type_string == "LIBRAM")
        return WeaponTypes::LIBRAM;
    else if (type_string == "TOTEM")
        return WeaponTypes::TOTEM;
    else if (type_string == "SHIELD")
        return WeaponTypes::SHIELD;
    else if (type_string == "CASTER_OFFHAND")
        return WeaponTypes::CASTER_OFFHAND;
    else if (type_string == "TWOHAND_AXE")
        return WeaponTypes::TWOHAND_AXE;
    else if (type_string == "TWOHAND_MACE")
        return WeaponTypes::TWOHAND_MACE;
    else if (type_string == "TWOHAND_SWORD")
        return WeaponTypes::TWOHAND_SWORD;
    else if (type_string == "CLOTH")
        return ArmorTypes::CLOTH;
    else if (type_string == "LEATHER")
        return ArmorTypes::LEATHER;
    else if (type_string == "MAIL")
        return ArmorTypes::MAIL;
    else if (type_string == "PLATE")
        return ArmorTypes::PLATE;

    return -1;
}

void Item::unsupported_stat(const QString& stat) {
    qDebug() << "Unsupported stat" << stat << "has no effect on created item";
}
