#include <QDebug>
#include <utility>

#include "ArmorPenetrationBuff.h"
#include "ArmorPenetrationProc.h"
#include "Character.h"
#include "EnchantStatic.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingProc.h"
#include "FelstrikerProc.h"
#include "FlatWeaponDamageBuff.h"
#include "GenericStatBuff.h"
#include "GenericChargeConsumerProc.h"
#include "InstantSpellProc.h"
#include "Item.h"
#include "NoEffectBuff.h"
#include "JomGabbar.h"
#include "Stats.h"
#include "Target.h"
#include "UseTrinket.h"

Item::Item(QString _name,
           QVector<QPair<QString, QString>> _stats,
           QMap<QString, QString> _info,
           QVector<QMap<QString, QString>> _procs,
           QVector<QMap<QString, QString>> _use):
    name(std::move(_name)),
    info(std::move(_info)),
    procs_map(std::move(_procs)),
    use_map(std::move(_use)),
    stats_key_value_pairs(std::move(std::move(_stats))),
    stats(new Stats()),
    enchant(nullptr)
{
    set_stats(stats_key_value_pairs);
    set_item_slot(info);
    set_item_type(info);
    set_class_restrictions(info);
    set_faction();
    this->icon = QString("Assets/items/%1").arg(info["icon"]);
}

Item::Item(const Item* item) :
    name(item->name),
    info(item->info),
    procs_map(item->procs_map),
    use_map(item->use_map),
    stats_key_value_pairs(item->stats_key_value_pairs),
    stats(new Stats()),
    enchant(nullptr)
{
    set_stats(stats_key_value_pairs);
    set_item_slot(info);
    set_item_type(info);
    set_class_restrictions(info);
    set_faction();
    this->icon = QString("Assets/items/%1").arg(info["icon"]);
}

Item::~Item() {
    for (auto & proc : active_procs) {
        proc->disable_proc();
        delete proc;
    }

    delete stats;
    delete enchant;
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

void Item::set_faction() {
    QString faction = get_value("faction");
    if (faction != "") {
        if (faction != "ALLIANCE" && faction != "HORDE")
            qDebug() << name << "has incorrect faction value" << faction;
        valid_faction = faction == "ALLIANCE" ? AvailableFactions::Alliance :
                                                AvailableFactions::Horde;
    }
    else
        valid_faction = AvailableFactions::Neutral;
}

void Item::set_class_restrictions(const QMap<QString, QString>& info) {
    QString base_str = "RESTRICTED_TO_%1";
    if (info.contains(base_str.arg("DRUID")))
        class_restrictions.insert("DRUID");
    if (info.contains(base_str.arg("HUNTER")))
        class_restrictions.insert("HUNTER");
    if (info.contains(base_str.arg("MAGE")))
        class_restrictions.insert("MAGE");
    if (info.contains(base_str.arg("PALADIN")))
        class_restrictions.insert("PALADIN");
    if (info.contains(base_str.arg("PRIEST")))
        class_restrictions.insert("PRIEST");
    if (info.contains(base_str.arg("ROGUE")))
        class_restrictions.insert("ROGUE");
    if (info.contains(base_str.arg("SHAMAN")))
        class_restrictions.insert("SHAMAN");
    if (info.contains(base_str.arg("WARLOCK")))
        class_restrictions.insert("WARLOCK");
    if (info.contains(base_str.arg("WARRIOR")))
        class_restrictions.insert("WARRIOR");
}

int Item::get_item_slot() const {
    return slot;
}

int Item::get_item_type() const {
    return this->item_type;
}

int Item::get_weapon_slot() const {
    return WeaponSlots::NON_WEAPON;
}

void Item::apply_equip_effect(Character* pchar, const int eq_slot) {
    assert(active_procs.empty());

    set_uses(pchar);
    set_procs(pchar, eq_slot);
}

void Item::remove_equip_effect() {
    for (auto & spell : use_spells) {
        spell->disable();
        delete spell;
    }

    use_spells.clear();

    for (auto & proc : active_procs) {
        proc->disable_proc();
        delete proc;
    }

    active_procs.clear();
}

QString Item::get_name() const {
    return name;
}

QString Item::get_weapon_side_name(const int eq_slot) const {
    switch (eq_slot) {
    case EquipmentSlot::MAINHAND:
        return QString("%1 %2").arg(name, "(MH)");
    case EquipmentSlot::OFFHAND:
        return QString("%1 %2").arg(name, "(OH)");
    default:
        return name;
    }
}

bool Item::has_enchant() const {
    return enchant != nullptr;
}

void Item::apply_enchant(EnchantName::Name enchant_name, Character* pchar) {
    if (enchant_name == EnchantName::NoEnchant)
        return;

    delete enchant;
    enchant = new EnchantStatic(enchant_name, pchar, EnchantSlot::NON_WEAPON);
}

void Item::clear_enchant() {
    delete enchant;
    enchant = nullptr;
}

QString Item::get_enchant_name() const {
    return enchant != nullptr ? enchant->get_name() : "";
}

QString Item::get_enchant_effect() const {
    return enchant != nullptr ? enchant->get_effect() : "";
}

EnchantName::Name Item::get_enchant_enum_value() const {
    return enchant != nullptr ? enchant->get_enum_name() : EnchantName::NoEnchant;
}

bool Item::available_for_faction(AvailableFactions::Name faction) const {
    return valid_faction == AvailableFactions::Neutral ? true :
                                                         valid_faction == faction;
}

bool Item::available_for_class(const QString& class_name) const {
    return class_restrictions.empty() || class_restrictions.contains(class_name.toUpper());
}

void Item::set_uses(Character *pchar) {
    for (auto & use : use_map) {
        QString use_name = use["name"];
        Spell* spell = nullptr;

        if (use_name == "GENERIC_STAT_BUFF") {
            QString type = use["type"];
            ItemStats stat_type;
            if (type == "ATTACK_SPEED")
                stat_type = ItemStats::AttackSpeedPercent;
            else if (type == "ATTACK_POWER")
                stat_type = ItemStats::AttackPower;
            else if (type == "STRENGTH")
                stat_type = ItemStats::Strength;
            else {
                stat_type = ItemStats::Armor;
                qDebug() << "unsupported stat use type" << type;
                assert(false);
            }

            int duration = use["duration"].toInt();
            int value = use["value"].toInt();
            int cooldown = use["cooldown"].toInt();

            Buff* buff = new GenericStatBuff(pchar, name, icon, duration, stat_type, value);
            spell = new UseTrinket(pchar, name, icon, cooldown, buff);
        }
        else if (use_name == "JOM_GABBAR") {
            Buff* buff = new JomGabbar(pchar);
            spell = new UseTrinket(pchar, buff->get_name(), buff->get_icon(), 120, buff, nullptr);
        }
        else if (use_name == "ZANDALARIAN_HERO_MEDALLION") {
            QVector<ProcInfo::Source> proc_sources;
            proc_sources.append(ProcInfo::Source::MainhandSwing);
            proc_sources.append(ProcInfo::Source::MainhandSpell);
            proc_sources.append(ProcInfo::Source::OffhandSwing);
            proc_sources.append(ProcInfo::Source::OffhandSpell);
            proc_sources.append(ProcInfo::Source::RangedAutoShoot);
            proc_sources.append(ProcInfo::Source::RangedSpell);
            Buff* buff = new FlatWeaponDamageBuff(pchar, name, icon, 20, 20, AffectedWeaponSide::All, 2);
            Proc* proc = new GenericChargeConsumerProc(pchar, name, icon, proc_sources, 1.0, buff);
            spell = new UseTrinket(pchar, name, icon, 120, buff, proc);
        }
        else if (use_name == "BADGE_OF_THE_SWARMGUARD") {
            double proc_rate = use["value"].toDouble();
            QVector<ProcInfo::Source> proc_sources;
            proc_sources.append(ProcInfo::Source::MainhandSwing);
            proc_sources.append(ProcInfo::Source::MainhandSpell);
            proc_sources.append(ProcInfo::Source::OffhandSwing);
            proc_sources.append(ProcInfo::Source::OffhandSpell);
            proc_sources.append(ProcInfo::Source::RangedAutoShoot);
            proc_sources.append(ProcInfo::Source::RangedSpell);
            auto* proc = new ArmorPenetrationProc(pchar, name, icon, proc_sources, proc_rate, 200, 6, 30, REFRESH_DOES_NOT_EXTEND_DURATION);
            auto* buff = new NoEffectBuff(pchar, 30);
            buff->link_buff_expiration(proc->get_buff());
            proc->set_proc_requirement_buff(buff);
            spell = new UseTrinket(pchar, name, icon, 180, buff, proc);
        }

        if (spell != nullptr)
            use_spells.append(spell);
    }

    for (auto & use: use_spells)
        use->enable();
}

void Item::set_procs(Character* pchar, const int eq_slot) {
    for (auto & i : procs_map) {
        QString proc_name = i["name"];
        QString instant = i["instant"].toLower();
        int amount = QString(i["amount"]).toInt();
        double internal_cd = QString(i["internal_cd"]).toDouble();
        double proc_rate = QString(i["rate"]).toDouble();

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

        auto direct_spell_damage_procs = QSet<QString>({"PHYSICAL_ATTACK",
                                                        "ARCANE_ATTACK",
                                                        "FIRE_ATTACK",
                                                        "FROST_ATTACK",
                                                        "NATURE_ATTACK",
                                                        "SHADOW_ATTACK",
                                                        "HOLY_ATTACK"});
        QVector<ProcInfo::Source> proc_sources;
        Proc* proc = nullptr;

        if (proc_name == "EXTRA_ATTACK") {
            add_default_melee_proc_sources(proc_sources, eq_slot);

            if (instant == "yes") {
                proc = new ExtraAttackInstantProc(pchar,
                                                  get_name(),
                                                  icon,
                                                  proc_sources,
                                                  proc_rate,
                                                  amount);
            }
            else {
                proc = new ExtraAttackOnNextSwingProc(pchar,
                                                      get_name(),
                                                      icon,
                                                      proc_sources,
                                                      proc_rate,
                                                      amount);
            }
        }
        else if (proc_name == "ARMOR_PENETRATION") {
            add_default_melee_proc_sources(proc_sources, eq_slot);

            int reduction = i["value"].toInt();
            int max_stacks = i["max_stacks"].toInt();
            int duration = i["duration"].toInt();

            proc = new ArmorPenetrationProc(pchar,
                                            get_weapon_side_name(eq_slot),
                                            icon, proc_sources,
                                            proc_rate,
                                            reduction,
                                            max_stacks,
                                            duration,
                                            REFRESH_EXTENDS_DURATION);
        }

        else if (direct_spell_damage_procs.contains(proc_name)) {
            add_default_melee_proc_sources(proc_sources, eq_slot);

            unsigned min = i["min"].toUInt();
            unsigned max = i["max"].toUInt();

            proc = new InstantSpellProc(pchar,
                                        get_weapon_side_name(eq_slot),
                                        icon,
                                        proc_sources,
                                        proc_rate,
                                        get_magic_school(proc_name),
                                        min, max);
        }

        else if (proc_name == "FELSTRIKER_PROC") {
            add_default_melee_proc_sources(proc_sources, eq_slot);

            proc = new FelstrikerProc(pchar, get_weapon_side_name(eq_slot), proc_sources, proc_rate, i["duration"].toInt());
        }

        if (proc != nullptr) {
            active_procs.append(proc);
            proc->enable_proc();
        }
    }
}

void Item::add_default_melee_proc_sources(QVector<ProcInfo::Source>& proc_sources, const int eq_slot) {
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
    }
}

MagicSchool Item::get_magic_school(const QString& name) {
    if (name.startsWith("PHYSICAL_"))
        return MagicSchool::Physical;
    if (name.startsWith("ARCANE_"))
        return MagicSchool::Arcane;
    if (name.startsWith("FIRE_"))
        return MagicSchool::Fire;
    if (name.startsWith("FROST_"))
        return MagicSchool::Frost;
    if (name.startsWith("NATURE_"))
        return MagicSchool::Nature;
    if (name.startsWith("SHADOW_"))
        return MagicSchool::Shadow;
    if (name.startsWith("HOLY_"))
        return MagicSchool::Holy;

    assert(false);
    return MagicSchool::Physical;
}

void Item::set_stats(const QVector<QPair<QString, QString>>& stats) {
    for (auto & stat : stats)
        set_stat(stat.first, stat.second);
}

QString Item::get_value(const QString& key) const {
    return info.contains(key) ? info[key] : "";
}

const Stats* Item::get_stats() const {
    return this->stats;
}

void Item::set_stat(const QString& key, const QString &value) {
    if (key == "STRENGTH") {
        this->stats->increase_strength(value.toInt());
        base_tooltip_stats.append(QString("+%1 Strength").arg(value));
        this->item_stat_values.insert(ItemStats::Strength, value.toInt());
    }
    else if (key == "AGILITY") {
        this->stats->increase_agility(value.toInt());
        base_tooltip_stats.append(QString("+%1 Agility").arg(value));
        this->item_stat_values.insert(ItemStats::Agility, value.toInt());
    }
    else if (key == "STAMINA") {
        this->stats->increase_stamina(value.toInt());
        base_tooltip_stats.append(QString("+%1 Stamina").arg(value));
        this->item_stat_values.insert(ItemStats::Stamina, value.toInt());
    }
    else if (key == "INTELLECT") {
        this->stats->increase_intellect(value.toInt());
        base_tooltip_stats.append(QString("+%1 Intellect").arg(value));
        this->item_stat_values.insert(ItemStats::Intellect, value.toInt());
    }
    else if (key == "SPIRIT") {
        this->stats->increase_spirit(value.toInt());
        base_tooltip_stats.append(QString("+%1 Spirit").arg(value));
        this->item_stat_values.insert(ItemStats::Spirit, value.toInt());
    }
    else if (key == "CRIT_CHANCE") {
        this->stats->increase_crit(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to get a critical strike by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::CritChance, static_cast<int>(value.toDouble() * 100));
    }
    else if (key == "HIT_CHANCE") {
        this->stats->increase_hit(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to hit by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::HitChance, static_cast<int>(value.toDouble() * 100));
    }
    else if (key == "ATTACK_POWER") {
        this->stats->increase_base_melee_ap(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power.").arg(value));
        this->item_stat_values.insert(ItemStats::AttackPower, value.toInt());
    }
    else if (key == "ATTACK_POWER_BEAST") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Beast, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Beasts.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusBeast, value.toInt());
    }
    else if (key == "ATTACK_POWER_DEMON") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Demon, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Demons.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDemon, value.toInt());
    }
    else if (key == "ATTACK_POWER_DRAGONKIN") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Dragonkin, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Dragonkin.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDragonkin, value.toInt());
    }
    else if (key == "ATTACK_POWER_UNDEAD") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Undead, value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Undead.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusUndead, value.toInt());
    }
    else if (key == "AXE_SKILL") {
        this->stats->increase_axe_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Axes +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillAxe, value.toInt());
    }
    else if (key == "DAGGER_SKILL") {
        this->stats->increase_dagger_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Daggers +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillDagger, value.toInt());
    }
    else if (key == "MACE_SKILL") {
        this->stats->increase_mace_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Maces +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillMace, value.toInt());
    }
    else if (key == "SWORD_SKILL") {
        this->stats->increase_sword_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Swords +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillSword, value.toInt());
    }
    else if (key == "ARMOR") {
        this->stats->increase_armor(value.toInt());
        base_tooltip_stats.append(QString("%1 Armor").arg(value));
        this->item_stat_values.insert(ItemStats::Armor, value.toInt());
    }
    else if (key == "DEFENSE") {
        this->stats->increase_defense(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Defense +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Defense, value.toInt());
    }
    else if (key == "DODGE_CHANCE") {
        this->stats->increase_dodge(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to dodge an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::DodgeChance, static_cast<int>(value.toDouble() * 100));
    }
    else if (key == "PARRY_CHANCE") {
        this->stats->increase_parry(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to parry an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::ParryChance, static_cast<int>(value.toDouble() * 100));
    }
    else if (key == "ARCANE_RESISTANCE") {
        this->stats->increase_arcane_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Arcane Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceArcane, value.toInt());
    }
    else if (key == "FIRE_RESISTANCE") {
        this->stats->increase_fire_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Fire Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFire, value.toInt());
    }
    else if (key == "FROST_RESISTANCE") {
        this->stats->increase_frost_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Frost Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFrost, value.toInt());
    }
    else if (key == "HOLY_RESISTANCE") {
        this->stats->increase_holy_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Holy Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceHoly, value.toInt());
    }
    else if (key == "NATURE_RESISTANCE") {
        this->stats->increase_nature_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Nature Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceNature, value.toInt());
    }
    else if (key == "SHADOW_RESISTANCE") {
        this->stats->increase_shadow_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Shadow Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceShadow, value.toInt());
    }
    else
        unsupported_stat(key);
}

int Item::get_stat_value_via_flag(const ItemStats item_stat_flag) const {
    if (!item_stat_values.contains(item_stat_flag))
        return 0;

    return item_stat_values[item_stat_flag];
}

QString Item::get_base_stat_tooltip() const {
    return get_tooltip(base_tooltip_stats);
}

QString Item::get_equip_effect_tooltip() const {
    return get_tooltip(equip_effects_tooltip_stats);
}

QString Item::get_tooltip(const QVector<QString>& tt_strings) const {
    QString tooltip = "";
    for (const auto & tt_string : tt_strings) {
        if (tooltip != "")
            tooltip += "\n";
        tooltip += tt_string;
    }

    return tooltip;
}

int get_slot_int(const QString& slot_string) {
    if (slot_string == "MAINHAND")
        return ItemSlots::MAINHAND;
    if (slot_string == "OFFHAND")
        return ItemSlots::OFFHAND;
    if (slot_string == "RANGED")
        return ItemSlots::RANGED;
    if (slot_string == "HEAD")
        return ItemSlots::HEAD;
    if (slot_string == "NECK")
        return ItemSlots::NECK;
    if (slot_string == "SHOULDERS")
        return ItemSlots::SHOULDERS;
    if (slot_string == "BACK")
        return ItemSlots::BACK;
    if (slot_string == "CHEST")
        return ItemSlots::CHEST;
    if (slot_string == "WRIST")
        return ItemSlots::WRIST;
    if (slot_string == "GLOVES")
        return ItemSlots::GLOVES;
    if (slot_string == "BELT")
        return ItemSlots::BELT;
    if (slot_string == "LEGS")
        return ItemSlots::LEGS;
    if (slot_string == "BOOTS")
        return ItemSlots::BOOTS;
    if (slot_string == "RING")
        return ItemSlots::RING;
    if (slot_string == "RING1")
        return ItemSlots::RING;
    if (slot_string == "RING2")
        return ItemSlots::RING;
    if (slot_string == "TRINKET")
        return ItemSlots::TRINKET;
    if (slot_string == "TRINKET1")
        return ItemSlots::TRINKET;
    if (slot_string == "TRINKET2")
        return ItemSlots::TRINKET;
    if (slot_string == "CASTER_OFFHAND")
        return ItemSlots::CASTER_OFFHAND;
    if (slot_string == "RELIC")
        return ItemSlots::RELIC;

    return -1;
}

int Item::get_type_int(const QString& type_string) {
    if (type_string == "AXE")
        return WeaponTypes::AXE;
    if (type_string == "DAGGER")
        return WeaponTypes::DAGGER;
    if (type_string == "FIST")
        return WeaponTypes::FIST;
    if (type_string == "MACE")
        return WeaponTypes::MACE;
    if (type_string == "POLEARM")
        return WeaponTypes::POLEARM;
    if (type_string == "STAFF")
        return WeaponTypes::STAFF;
    if (type_string == "SWORD")
        return WeaponTypes::SWORD;
    if (type_string == "BOW")
        return WeaponTypes::BOW;
    if (type_string == "CROSSBOW")
        return WeaponTypes::CROSSBOW;
    if (type_string == "GUN")
        return WeaponTypes::GUN;
    if (type_string == "THROWN")
        return WeaponTypes::THROWN;
    if (type_string == "WAND")
        return WeaponTypes::WAND;
    if (type_string == "IDOL")
        return WeaponTypes::IDOL;
    if (type_string == "LIBRAM")
        return WeaponTypes::LIBRAM;
    if (type_string == "TOTEM")
        return WeaponTypes::TOTEM;
    if (type_string == "SHIELD")
        return WeaponTypes::SHIELD;
    if (type_string == "CASTER_OFFHAND")
        return WeaponTypes::CASTER_OFFHAND;
    if (type_string == "TWOHAND_AXE")
        return WeaponTypes::TWOHAND_AXE;
    if (type_string == "TWOHAND_MACE")
        return WeaponTypes::TWOHAND_MACE;
    if (type_string == "TWOHAND_SWORD")
        return WeaponTypes::TWOHAND_SWORD;
    if (type_string == "CLOTH")
        return ArmorTypes::CLOTH;
    if (type_string == "LEATHER")
        return ArmorTypes::LEATHER;
    if (type_string == "MAIL")
        return ArmorTypes::MAIL;
    if (type_string == "PLATE")
        return ArmorTypes::PLATE;

    return -1;
}

void Item::unsupported_stat(const QString& stat) {
    qDebug() << "Unsupported stat" << stat << "has no effect on created item";
}
