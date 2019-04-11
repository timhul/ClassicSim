#include "Item.h"

#include <QDebug>
#include <utility>

#include "ArmorPenetrationBuff.h"
#include "ArmorPenetrationProc.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "DevilsaurEye.h"
#include "EnchantStatic.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingProc.h"
#include "FelstrikerProc.h"
#include "FlatWeaponDamageBuff.h"
#include "GenericChargeConsumerProc.h"
#include "GenericStatBuff.h"
#include "InstantSpellProc.h"
#include "ItemModificationRequirer.h"
#include "JomGabbar.h"
#include "ManaDrainProc.h"
#include "NoEffectBuff.h"
#include "Stats.h"
#include "Target.h"
#include "UseTrinket.h"
#include "Utils/Check.h"

Item::Item(QString name,
           int item_id,
           QMap<QString, QString> _info,
           QVector<QPair<QString, QString>> _stats,
           QVector<QMap<QString, QString>> _procs,
           QVector<QMap<QString, QString>> _use,
           QVector<QString> _spell_modifications):
    pchar(nullptr),
    name(std::move(name)),
    valid_faction(AvailableFactions::Neutral),
    info(std::move(_info)),
    procs_map(std::move(_procs)),
    use_map(std::move(_use)),
    stats_key_value_pairs(std::move(_stats)),
    spell_modifications(std::move(_spell_modifications)),
    stats(new Stats()),
    enchant(nullptr),
    slot(-1),
    item_type(-1),
    item_id(item_id)
{
    set_stats(stats_key_value_pairs);
    set_item_slot(info);
    set_item_type(info);
    set_class_restrictions(info);
    set_faction();
    this->icon = QString("Assets/items/%1").arg(info["icon"]);
}

Item::Item(const Item* item) :
    pchar(item->pchar),
    name(item->name),
    info(item->info),
    procs_map(item->procs_map),
    use_map(item->use_map),
    stats_key_value_pairs(item->stats_key_value_pairs),
    spell_modifications(item->spell_modifications),
    stats(new Stats()),
    enchant(nullptr),
    item_id(item->item_id)
{
    set_stats(stats_key_value_pairs);
    set_item_slot(info);
    set_item_type(info);
    set_class_restrictions(info);
    set_faction();
    this->icon = QString("Assets/items/%1").arg(info["icon"]);
}

Item::~Item() {
    remove_equip_effect();

    delete stats;
    delete enchant;
}

void Item::set_item_slot(const QMap<QString, QString>& info) {
    if (!info.contains("slot")) {
        return;
    }

    slot = get_slot_int(info["slot"]);
}

void Item::set_item_type(const QMap<QString, QString>& info) {
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
    check(active_procs.empty(), "Procs already active on applying equip effect");

    this->pchar = pchar;

    set_uses();
    set_procs(eq_slot);
    call_item_modifications();
}

void Item::remove_equip_effect() {
    for (auto & spell : use_spells) {
        spell->disable();
        delete spell;
    }

    for (auto & proc : active_procs) {
        proc->disable_proc();
        delete proc;
    }

    if (pchar != nullptr)
        call_item_modifications(false);
}

void Item::call_item_modifications(const bool activate) const {
    for (auto & spell_name : spell_modifications) {
        Spell* spell = pchar->get_spells()->get_spell_by_name(spell_name);
        if (spell == nullptr)
            continue;

        auto spell_modded_by_item = dynamic_cast<ItemModificationRequirer*>(spell);
        if (spell_modded_by_item == nullptr)
            continue;

        if (activate)
            spell_modded_by_item->activate_item_modification(this->item_id);
        else
            spell_modded_by_item->deactivate_item_modification(this->item_id);
    }
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

int Item::get_item_id() const {
    return this->item_id;
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

void Item::set_uses() {
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
                check(false, QString("Unsupported stat use type '%1'").arg(type).toStdString());
            }

            int duration = use["duration"].toInt();
            unsigned value = use["value"].toUInt();
            int cooldown = use["cooldown"].toInt();

            Buff* buff = new GenericStatBuff(pchar, name, icon, duration, stat_type, value);
            spell = new UseTrinket(pchar, name, icon, cooldown, buff);
        }
        else if (use_name == "DEVILSAUR_EYE") {
            Buff* buff = new DevilsaurEye(pchar);
            spell = new UseTrinket(pchar, name, icon, 120, buff);
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
            proc_sources.append(ProcInfo::Source::RangedAutoShot);
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
            proc_sources.append(ProcInfo::Source::RangedAutoShot);
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

void Item::set_procs(const int eq_slot) {
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
            add_default_proc_sources(proc_sources, eq_slot);

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
            add_default_proc_sources(proc_sources, eq_slot);

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
            add_default_proc_sources(proc_sources, eq_slot);

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
            add_default_proc_sources(proc_sources, eq_slot);

            proc = new FelstrikerProc(pchar, get_weapon_side_name(eq_slot), proc_sources, proc_rate, i["duration"].toInt());
        }

        else if (proc_name == "BLACK_GRASP_OF_THE_DESTROYER") {
            proc_sources = {
                ProcInfo::Source::MainhandSwing,
                ProcInfo::Source::MainhandSpell,
                ProcInfo::Source::OffhandSwing,
                ProcInfo::Source::OffhandSpell,
                ProcInfo::Source::RangedAutoShot,
                ProcInfo::Source::RangedSpell
            };

            proc = new ManaDrainProc(pchar, "Black Grasp of the Destroyer", "Assets/items/Inv_gauntlets_31.png",
                                     proc_sources, i["rate"].toDouble(), i["min"].toUInt(), i["max"].toUInt());
        }

        if (proc != nullptr) {
            active_procs.append(proc);
            proc->enable_proc();
        }
    }
}

void Item::add_default_proc_sources(QVector<ProcInfo::Source>& proc_sources, const int eq_slot) {
    switch (eq_slot) {
    case EquipmentSlot::MAINHAND:
        proc_sources.append(ProcInfo::Source::MainhandSwing);
        proc_sources.append(ProcInfo::Source::MainhandSpell);
        break;
    case EquipmentSlot::OFFHAND:
        proc_sources.append(ProcInfo::Source::OffhandSwing);
        proc_sources.append(ProcInfo::Source::OffhandSpell);
        break;
    case EquipmentSlot::RANGED:
        proc_sources.append(ProcInfo::Source::RangedAutoShot);
        proc_sources.append(ProcInfo::Source::RangedSpell);
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

    check(false, QString("Unknown magic school '%1'").arg(name).toStdString());
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
        this->stats->increase_strength(value.toUInt());
        base_tooltip_stats.append(QString("+%1 Strength").arg(value));
        this->item_stat_values.insert(ItemStats::Strength, value.toUInt());
    }
    else if (key == "AGILITY") {
        this->stats->increase_agility(value.toUInt());
        base_tooltip_stats.append(QString("+%1 Agility").arg(value));
        this->item_stat_values.insert(ItemStats::Agility, value.toUInt());
    }
    else if (key == "STAMINA") {
        this->stats->increase_stamina(value.toUInt());
        base_tooltip_stats.append(QString("+%1 Stamina").arg(value));
        this->item_stat_values.insert(ItemStats::Stamina, value.toUInt());
    }
    else if (key == "INTELLECT") {
        this->stats->increase_intellect(value.toUInt());
        base_tooltip_stats.append(QString("+%1 Intellect").arg(value));
        this->item_stat_values.insert(ItemStats::Intellect, value.toUInt());
    }
    else if (key == "SPIRIT") {
        this->stats->increase_spirit(value.toUInt());
        base_tooltip_stats.append(QString("+%1 Spirit").arg(value));
        this->item_stat_values.insert(ItemStats::Spirit, value.toUInt());
    }
    else if (key == "CRIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->stats->increase_melee_crit(attack_table_value);
        this->stats->increase_ranged_crit(attack_table_value);
        QString number = QString::number(display_value);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to get a critical strike by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::CritChance, display_value);
    }
    else if (key == "HIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->stats->increase_melee_hit(attack_table_value);
        this->stats->increase_ranged_hit(attack_table_value);
        QString number = QString::number(display_value);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to hit by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::HitChance, display_value);
    }
    else if (key == "ATTACK_POWER") {
        this->stats->increase_base_melee_ap(value.toUInt());
        this->stats->increase_base_ranged_ap(value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power.").arg(value));
        this->item_stat_values.insert(ItemStats::AttackPower, value.toUInt());
    }
    else if (key == "RANGED_ATTACK_POWER") {
        this->stats->increase_base_ranged_ap(value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Ranged Attack Power.").arg(value));
        this->item_stat_values.insert(ItemStats::RangedAttackPower, value.toUInt());
    }
    else if (key == "ATTACK_POWER_BEAST") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Beast, value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Beasts.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusBeast, value.toUInt());
    }
    else if (key == "ATTACK_POWER_DEMON") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Demon, value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Demons.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDemon, value.toUInt());
    }
    else if (key == "ATTACK_POWER_DRAGONKIN") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Dragonkin, value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Dragonkin.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDragonkin, value.toUInt());
    }
    else if (key == "ATTACK_POWER_UNDEAD") {
        this->stats->increase_melee_ap_against_type(Target::CreatureType::Undead, value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Undead.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusUndead, value.toUInt());
    }
    else if (key == "AXE_SKILL") {
        this->stats->increase_axe_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Axes +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillAxe, value.toUInt());
    }
    else if (key == "DAGGER_SKILL") {
        this->stats->increase_dagger_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Daggers +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillDagger, value.toUInt());
    }
    else if (key == "MACE_SKILL") {
        this->stats->increase_mace_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Maces +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillMace, value.toUInt());
    }
    else if (key == "SWORD_SKILL") {
        this->stats->increase_sword_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Swords +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillSword, value.toUInt());
    }
    else if (key == "BOW_SKILL") {
        this->stats->increase_bow_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Bows +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillBow, value.toUInt());
    }
    else if (key == "CROSSBOW_SKILL") {
        this->stats->increase_crossbow_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Crossbows +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillCrossbow, value.toUInt());
    }
    else if (key == "GUN_SKILL") {
        this->stats->increase_gun_skill(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Guns +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillGun, value.toUInt());
    }
    else if (key == "MANA_PER_5") {
        this->stats->increase_mp5(value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: Restores %1 mana per 5 sec.").arg(value));
        this->item_stat_values.insert(ItemStats::ManaPer5, value.toUInt());
    }
    else if (key == "ARMOR") {
        this->stats->increase_armor(value.toInt());
        base_tooltip_stats.append(QString("%1 Armor").arg(value));
        this->item_stat_values.insert(ItemStats::Armor, value.toUInt());
    }
    else if (key == "DEFENSE") {
        this->stats->increase_defense(value.toInt());
        equip_effects_tooltip_stats.append(QString("Equip: Increased Defense +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Defense, value.toUInt());
    }
    else if (key == "DODGE_CHANCE") {
        this->stats->increase_dodge(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to dodge an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::DodgeChance, static_cast<unsigned>(value.toDouble() * 100));
    }
    else if (key == "PARRY_CHANCE") {
        this->stats->increase_parry(value.toDouble());
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to parry an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::ParryChance, static_cast<unsigned>(value.toDouble() * 100));
    }
    else if (key == "ARCANE_RESISTANCE") {
        this->stats->increase_arcane_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Arcane Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceArcane, value.toUInt());
    }
    else if (key == "FIRE_RESISTANCE") {
        this->stats->increase_fire_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Fire Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFire, value.toUInt());
    }
    else if (key == "FROST_RESISTANCE") {
        this->stats->increase_frost_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Frost Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFrost, value.toUInt());
    }
    else if (key == "HOLY_RESISTANCE") {
        this->stats->increase_holy_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Holy Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceHoly, value.toUInt());
    }
    else if (key == "NATURE_RESISTANCE") {
        this->stats->increase_nature_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Nature Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceNature, value.toUInt());
    }
    else if (key == "SHADOW_RESISTANCE") {
        this->stats->increase_shadow_resistance(value.toInt());
        base_tooltip_stats.append(QString("+%1 Shadow Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceShadow, value.toUInt());
    }
    else
        unsupported_stat(key);
}

unsigned Item::get_stat_value_via_flag(const ItemStats item_stat_flag) const {
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
    if (slot_string == "PROJECTILE")
        return ItemSlots::PROJECTILE;

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
