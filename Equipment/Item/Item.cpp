#include "Item.h"

#include <cmath>
#include <utility>

#include <QDebug>

#include "ArmorPenetrationBuff.h"
#include "ArmorPenetrationProc.h"
#include "Buff.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CharmOfTrickery.h"
#include "DevilsaurEye.h"
#include "EnchantStatic.h"
#include "Equipment.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingProc.h"
#include "FelstrikerProc.h"
#include "FireballInstant.h"
#include "FlatWeaponDamageBuff.h"
#include "GenericBuffProc.h"
#include "GenericChargeConsumerProc.h"
#include "GenericSpellProc.h"
#include "GenericStatBuff.h"
#include "Hunter.h"
#include "HunterPet.h"
#include "InstantSpellProc.h"
#include "ItemModificationRequirer.h"
#include "JomGabbar.h"
#include "Nightfall.h"
#include "NoEffectSelfBuff.h"
#include "RandomAffix.h"
#include "ResourceGainProc.h"
#include "SanctifiedOrb.h"
#include "SpellRankGroup.h"
#include "Stats.h"
#include "Target.h"
#include "UseItem.h"
#include "UseTrinket.h"
#include "Utils/Check.h"
#include "ZandalarianHeroCharm.h"

Item::Item(QString name,
           const int item_id,
           Content::Phase phase,
           EnchantInfo* enchant_info,
           QMap<QString, QString> _info,
           QVector<QPair<QString, QString>> _stats,
           QVector<QMap<QString, QString>> _procs,
           QVector<QMap<QString, QString>> _use,
           QVector<QString> _spell_modifications,
           QVector<QString> _special_equip_effects,
           QSet<int> _mutex_item_ids,
           QVector<int> _random_affixes) :
    PhaseRequirer(phase),
    base_name(name),
    name(name),
    item_id(item_id),
    pchar(nullptr),
    valid_faction(AvailableFactions::Neutral),
    info(std::move(_info)),
    special_equip_effects(std::move(_special_equip_effects)),
    procs_map(std::move(_procs)),
    use_map(std::move(_use)),
    stats_key_value_pairs(std::move(_stats)),
    item_modifications(std::move(_spell_modifications)),
    mutex_item_ids(std::move(_mutex_item_ids)),
    stats(new Stats()),
    enchant_info(enchant_info),
    enchant(nullptr),
    random_affix(nullptr),
    possible_random_affixes(std::move(_random_affixes)),
    slot(-1),
    item_type(-1) {
    set_stats(stats_key_value_pairs);
    set_item_slot(info);
    set_item_type(info);
    set_class_restrictions(info);
    set_faction();
    this->icon = QString("Assets/items/%1").arg(info["icon"]);
}

Item::Item(const Item* item) :
    PhaseRequirer(item->phase),
    base_name(item->base_name),
    name(item->name),
    item_id(item->item_id),
    pchar(item->pchar),
    info(item->info),
    special_equip_effects(item->special_equip_effects),
    procs_map(item->procs_map),
    use_map(item->use_map),
    stats_key_value_pairs(item->stats_key_value_pairs),
    item_modifications(item->item_modifications),
    mutex_item_ids(item->mutex_item_ids),
    stats(new Stats()),
    enchant_info(item->enchant_info),
    enchant(nullptr),
    random_affix(nullptr),
    possible_random_affixes(item->possible_random_affixes) {
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
        valid_faction = faction == "ALLIANCE" ? AvailableFactions::Alliance : AvailableFactions::Horde;
    } else
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
    clear_mutex_ids();
}

void Item::remove_equip_effect() {
    for (const auto& spell : use_spells) {
        spell->disable();
        delete spell;
    }

    for (const auto& proc : active_procs) {
        proc->disable_proc();
        delete proc;
    }

    if (pchar != nullptr)
        call_item_modifications(false);
}

void Item::enable_proc_effects() {
    for (const auto& proc : active_procs)
        proc->enable_proc();
}

void Item::disable_proc_effects() {
    for (const auto& proc : active_procs)
        proc->disable_proc();
}

void Item::call_item_modifications(const bool activate) const {
    for (const auto& name : item_modifications) {
        call_modifications_by_specific_name(name, activate);
        call_spell_modifications(name, activate);
        call_buff_modifications(name, activate);
    }
}

void Item::call_modifications_by_specific_name(const QString& name, const bool activate) const {
    if (QSet<QString>({"BEASTMASTER_HUNTER_PET"}).contains(name)) {
        if (pchar->class_name != "Hunter")
            return;
        if (activate)
            static_cast<HunterPet*>(pchar->get_pet())->activate_item_effect(this->item_id);
        else
            static_cast<HunterPet*>(pchar->get_pet())->deactivate_item_effect(this->item_id);
    }
}

void Item::call_spell_modifications(const QString& spell_name, const bool activate) const {
    SpellRankGroup* spell_group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
    if (spell_group == nullptr)
        return;

    for (auto& spell : spell_group->spell_group) {
        auto spell_modded_by_item = dynamic_cast<ItemModificationRequirer*>(spell);
        if (spell_modded_by_item == nullptr)
            return;

        if (activate)
            spell_modded_by_item->activate_item_modification(this->item_id);
        else
            spell_modded_by_item->deactivate_item_modification(this->item_id);
    }
}

void Item::call_buff_modifications(const QString& buff_name, const bool activate) const {
    Buff* buff = pchar->get_spells()->get_buff_by_name(buff_name);
    if (buff == nullptr)
        return;

    auto buff_modded_by_item = dynamic_cast<ItemModificationRequirer*>(buff);
    if (buff_modded_by_item == nullptr)
        return;

    if (activate)
        buff_modded_by_item->activate_item_modification(this->item_id);
    else
        buff_modded_by_item->deactivate_item_modification(this->item_id);
}

void Item::clear_mutex_ids() {
    for (const auto& item_id : mutex_item_ids)
        pchar->get_equipment()->clear_item_id_if_equipped_in_any_slot(item_id);
}

QString Item::get_weapon_side_name(const int eq_slot, const QString& display_name) const {
    switch (eq_slot) {
    case EquipmentSlot::MAINHAND:
        return QString("%1 %2").arg(display_name, "(MH)");
    case EquipmentSlot::OFFHAND:
        return QString("%1 %2").arg(display_name, "(OH)");
    default:
        return display_name;
    }
}

bool Item::has_enchant() const {
    return enchant != nullptr;
}

void Item::apply_enchant(EnchantName::Name enchant_name, Character* pchar) {
    if (enchant_name == EnchantName::Name::NoEnchant)
        return;

    delete enchant;
    enchant = new EnchantStatic(enchant_name, pchar, enchant_info, EnchantSlot::NON_WEAPON);
}

void Item::clear_enchant() {
    delete enchant;
    enchant = nullptr;
}

QString Item::get_enchant_effect() const {
    return enchant != nullptr ? enchant->get_effect() : "";
}

QString Item::get_enchant_unique_name() const {
    return enchant != nullptr ? enchant_info->get_unique_name(enchant->get_enum_name()) : "";
}

EnchantName::Name Item::get_enchant_enum_value() const {
    return enchant != nullptr ? enchant->get_enum_name() : EnchantName::Name::NoEnchant;
}

Enchant* Item::get_enchant() const {
    return this->enchant;
}

bool Item::can_have_random_affix() const {
    return !possible_random_affixes.empty();
}

bool Item::has_random_affix() const {
    return this->random_affix != nullptr;
}

RandomAffix* Item::get_random_affix() const {
    return this->random_affix;
}

QVector<int> Item::get_possible_random_affixes() const {
    if (this->possible_random_affixes.empty())
        return QVector<int>();

    return this->possible_random_affixes;
}

void Item::set_random_affix(RandomAffix* affix) {
    if (!possible_random_affixes.contains(static_cast<int>(affix->id))) {
        qDebug() << "Unable to set random affix" << affix << "to item" << item_id;
        return;
    }

    if (this->random_affix != nullptr)
        this->stats->remove(this->random_affix->get_stats());

    this->stats->add(affix->get_stats());
    for (const auto& stat : affix->get_stats()->get_base_tooltip()) {
        base_tooltip_stats.append(stat);
    }
    for (const auto& stat : affix->get_stats()->get_equip_effects_tooltip()) {
        equip_effects_tooltip_stats.append(stat);
    }

    QMapIterator<ItemStats, unsigned> iter(affix->get_affix_stat_values());
    while (iter.hasNext()) {
        iter.next();
        this->item_stat_values.insert(iter.key(), iter.value());
    }

    name = base_name + ' ' + affix->name;
    random_affix = affix;
}

bool Item::available_for_faction(AvailableFactions::Name faction) const {
    return valid_faction == AvailableFactions::Neutral ? true : valid_faction == faction;
}

bool Item::available_for_class(const QString& class_name) const {
    return class_restrictions.empty() || class_restrictions.contains(class_name.toUpper());
}

void Item::set_uses() {
    for (const auto& use : use_map) {
        QString use_name = use["name"];
        Spell* spell = nullptr;

        if (use_name == "GENERIC_STAT_BUFF") {
            const QString type = use["type"];
            const ItemStats stat_type = get_item_stats_from_string(type);
            const int duration = use["duration"].toInt();
            const unsigned value = use["value"].toUInt();
            const int cooldown = use["cooldown"].toInt();

            Buff* buff = new GenericStatBuff(pchar, name, icon, duration, {{stat_type, value}});

            if (slot == ItemSlots::TRINKET)
                spell = new UseTrinket(pchar, name, icon, cooldown, buff);
            else
                spell = new UseItem(pchar, name, icon, cooldown, buff);
        } else if (use_name == "EYE_OF_MOAM") {
            Buff* buff = new GenericStatBuff(pchar, name, icon, 30, {{ItemStats::SpellDamage, 50}, {ItemStats::SpellPenetration, 100}});
            spell = new UseTrinket(pchar, name, icon, 180, buff);
        } else if (use_name == "DEVILSAUR_EYE") {
            Buff* buff = new DevilsaurEye(pchar);
            spell = new UseTrinket(pchar, name, icon, 120, buff);
        } else if (use_name == "SANCTIFIED_ORB") {
            Buff* buff = new SanctifiedOrb(pchar);
            spell = new UseTrinket(pchar, name, icon, 180, buff);
        } else if (use_name == "JOM_GABBAR") {
            Buff* buff = new JomGabbar(pchar);
            spell = new UseTrinket(pchar, buff->name, buff->icon, 120, buff, nullptr);
        } else if (use_name == "CHARM_OF_TRICKERY") {
            Buff* buff = new CharmOfTrickery(pchar);
            spell = new UseTrinket(pchar, buff->name, buff->icon, 180, buff, nullptr);
        } else if (use_name == "ZANDALARIAN_HERO_MEDALLION") {
            QVector<ProcInfo::Source> proc_sources;
            proc_sources.append(ProcInfo::Source::MainhandSwing);
            proc_sources.append(ProcInfo::Source::MainhandSpell);
            proc_sources.append(ProcInfo::Source::OffhandSwing);
            proc_sources.append(ProcInfo::Source::RangedAutoShot);
            proc_sources.append(ProcInfo::Source::RangedSpell);
            Buff* buff = new FlatWeaponDamageBuff(pchar, name, icon, 20, 20, AffectedWeaponSide::All, 2);
            Proc* proc = new GenericChargeConsumerProc(pchar, name, icon, proc_sources, 1.0, buff);
            spell = new UseTrinket(pchar, name, icon, 120, buff, proc);
        } else if (use_name == "ZANDALARIAN_HERO_CHARM") {
            const QVector<ProcInfo::Source> proc_sources {ProcInfo::Source::MagicSpell};
            Buff* buff = new ZandalarianHeroCharm(pchar);
            Proc* proc = new GenericChargeConsumerProc(pchar, name, icon, proc_sources, 1.0, buff);
            spell = new UseTrinket(pchar, name, icon, 120, buff, proc);
        } else if (use_name == "BADGE_OF_THE_SWARMGUARD") {
            double proc_rate = use["value"].toDouble();
            QVector<ProcInfo::Source> proc_sources;
            proc_sources.append(ProcInfo::Source::MainhandSwing);
            proc_sources.append(ProcInfo::Source::MainhandSpell);
            proc_sources.append(ProcInfo::Source::OffhandSwing);
            proc_sources.append(ProcInfo::Source::RangedAutoShot);
            proc_sources.append(ProcInfo::Source::RangedSpell);
            auto proc = new ArmorPenetrationProc(pchar, name, icon, proc_sources, proc_rate, 200, 6, 30, REFRESH_DOES_NOT_EXTEND_DURATION);
            auto buff = new NoEffectSelfBuff(pchar, 30);
            buff->link_buff_expiration(proc->get_buff());
            proc->set_proc_requirement_buff(buff);
            spell = new UseTrinket(pchar, name, icon, 180, buff, proc);
        }

        if (spell != nullptr)
            use_spells.append(spell);
    }

    for (const auto& use : use_spells)
        use->enable();
}

void Item::set_procs(const int eq_slot) {
    for (const auto& i : procs_map) {
        const QString display_name = i.contains("display_name") ? i["display_name"] : name;
        const QString proc_name = i["name"];
        const QString instant = i["instant"].toLower();
        const int amount = QString(i["amount"]).toInt();
        const double internal_cd = QString(i["internal_cd"]).toDouble();
        const double proc_rate = QString(i["rate"]).toDouble();

        if (amount < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(name, proc_name, QString::number(amount));
            continue;
        }
        if (proc_rate < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(name, proc_name, QString::number(proc_rate, 'f', 2));
            continue;
        }
        if (internal_cd < 0) {
            qDebug() << QString("%1 proc %2 %3 < 0, skipping proc").arg(name, proc_name, QString::number(internal_cd, 'f', 2));
            continue;
        }

        const auto direct_spell_damage_procs = QSet<QString>(
            {"PHYSICAL_ATTACK", "ARCANE_ATTACK", "FIRE_ATTACK", "FROST_ATTACK", "NATURE_ATTACK", "SHADOW_ATTACK", "HOLY_ATTACK"});
        QVector<ProcInfo::Source> proc_sources;
        Proc* proc = nullptr;

        if (proc_name == "EXTRA_ATTACK") {
            add_default_proc_sources(proc_sources, eq_slot);

            if (instant == "yes") {
                proc = new ExtraAttackInstantProc(pchar, display_name, icon, proc_sources, proc_rate, amount);
            } else {
                proc = new ExtraAttackOnNextSwingProc(pchar, display_name, icon, proc_sources, proc_rate, amount);
            }
        } else if (proc_name == "ARMOR_PENETRATION") {
            add_default_proc_sources(proc_sources, eq_slot);

            int reduction = i["value"].toInt();
            int max_stacks = i["max_stacks"].toInt();
            int duration = i["duration"].toInt();

            proc = new ArmorPenetrationProc(pchar, get_weapon_side_name(eq_slot, display_name), icon, proc_sources, proc_rate, reduction, max_stacks,
                                            duration, REFRESH_EXTENDS_DURATION);
        }

        else if (direct_spell_damage_procs.contains(proc_name)) {
            add_default_proc_sources(proc_sources, eq_slot);

            const unsigned min = i["min"].toUInt();
            const unsigned max = i["max"].toUInt();
            const double coefficient = i["spell_dmg_coefficient"].toDouble();
            const unsigned innate_threat = i.value("innate_threat", 0).toUInt();

            proc = new InstantSpellProc(pchar, get_weapon_side_name(eq_slot, display_name), icon, proc_sources, proc_rate,
                                        get_magic_school(proc_name), min, max, coefficient, ConsumeCharge::No, innate_threat);
        }

        else if (proc_name == "FELSTRIKER_PROC") {
            add_default_proc_sources(proc_sources, eq_slot);

            proc = new FelstrikerProc(pchar, get_weapon_side_name(eq_slot, display_name), proc_sources, proc_rate, i["duration"].toInt());
        }

        else if (proc_name == "BLACK_GRASP_OF_THE_DESTROYER") {
            proc_sources = {ProcInfo::Source::MainhandSwing, ProcInfo::Source::MainhandSpell, ProcInfo::Source::OffhandSwing,
                            ProcInfo::Source::RangedAutoShot, ProcInfo::Source::RangedSpell};

            proc = new ResourceGainProc(pchar, "Black Grasp of the Destroyer", "Assets/items/Inv_gauntlets_31.png", proc_sources, proc_rate,
                                        ResourceType::Mana, i["min"].toUInt(), i["max"].toUInt());
        } else if (proc_name == "NIGHTFALL") {
            Buff* buff = new Nightfall(pchar);
            proc = new GenericBuffProc(pchar, "Nightfall", "Assets/items/Inv_axe_12.png",
                                       QVector<ProcInfo::Source> {ProcInfo::MainhandSpell, ProcInfo::MainhandSwing}, proc_rate, EnabledAtStart::Yes,
                                       MaintainBuffEnabled::No, buff);
        } else if (proc_name == "GENERIC_STAT_BUFF") {
            add_proc_sources_from_map(proc_sources, i, eq_slot);
            Buff* buff = new GenericStatBuff(pchar, display_name, icon, i["duration"].toInt(),
                                             {{get_item_stats_from_string(i["type"]), static_cast<unsigned>(amount)}});
            proc = new GenericBuffProc(pchar, name, icon, proc_sources, proc_rate, EnabledAtStart::Yes, MaintainBuffEnabled::Yes, buff);
        } else if (proc_name == "INSTANT_FIREBALL") {
            add_default_proc_sources(proc_sources, eq_slot);
            Spell* spell = new FireballInstant(pchar, QString(" (%1)").arg(display_name), i["min"].toUInt(), i["max"].toUInt(),
                                               i["dmg_over_duration"].toUInt(), i["duration"].toInt(), 0, 0, 0.0, 0.0, 1);
            proc = new GenericSpellProc(pchar, display_name, icon, proc_sources, proc_rate, spell);
        } else {
            qDebug() << "Unhandled proc" << proc_name;
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
        break;
    case EquipmentSlot::RANGED:
        proc_sources.append(ProcInfo::Source::RangedAutoShot);
        proc_sources.append(ProcInfo::Source::RangedSpell);
        break;
    default:
        proc_sources.append(ProcInfo::Source::MainhandSwing);
        proc_sources.append(ProcInfo::Source::MainhandSpell);
        proc_sources.append(ProcInfo::Source::OffhandSwing);
    }
}

void Item::add_proc_sources_from_map(QVector<ProcInfo::Source>& proc_sources, const QMap<QString, QString>& proc_map, const int eq_slot) {
    if (proc_map.contains("proc_magic_hit"))
        proc_sources.append(ProcInfo::Source::MagicSpell);

    if (proc_map.contains("proc_ranged_auto"))
        proc_sources.append(ProcInfo::Source::RangedAutoShot);

    if (proc_map.contains("proc_ranged_skill"))
        proc_sources.append(ProcInfo::Source::RangedSpell);

    if (proc_map.contains("proc_melee_auto")) {
        proc_sources.append(ProcInfo::Source::MainhandSwing);
        proc_sources.append(ProcInfo::Source::OffhandSwing);
    }

    if (proc_map.contains("proc_melee_skill"))
        proc_sources.append(ProcInfo::Source::MainhandSpell);

    if (proc_map.contains("proc_melee_weapon_side")) {
        switch (eq_slot) {
        case EquipmentSlot::MAINHAND:
            proc_sources.append(ProcInfo::Source::MainhandSpell);
            proc_sources.append(ProcInfo::Source::MainhandSwing);
            break;
        case EquipmentSlot::OFFHAND:
            proc_sources.append(ProcInfo::Source::OffhandSwing);
            break;
        default:
            qDebug() << "Could not add proc source for" << name;
            break;
        }
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
    for (const auto& stat : stats)
        set_stat(stat.first, stat.second);
}

QString Item::get_value(const QString& key) const {
    return info.contains(key) ? info[key] : "";
}

const Stats* Item::get_stats() const {
    return this->stats;
}

void Item::set_stat(const QString& key, const QString& value) {
    this->stats->add(key, value);

    if (key == "STRENGTH") {
        base_tooltip_stats.append(QString("+%1 Strength").arg(value));
        this->item_stat_values.insert(ItemStats::Strength, value.toUInt());
    } else if (key == "AGILITY") {
        base_tooltip_stats.append(QString("+%1 Agility").arg(value));
        this->item_stat_values.insert(ItemStats::Agility, value.toUInt());
    } else if (key == "STAMINA") {
        base_tooltip_stats.append(QString("+%1 Stamina").arg(value));
        this->item_stat_values.insert(ItemStats::Stamina, value.toUInt());
    } else if (key == "INTELLECT") {
        base_tooltip_stats.append(QString("+%1 Intellect").arg(value));
        this->item_stat_values.insert(ItemStats::Intellect, value.toUInt());
    } else if (key == "SPIRIT") {
        base_tooltip_stats.append(QString("+%1 Spirit").arg(value));
        this->item_stat_values.insert(ItemStats::Spirit, value.toUInt());
    } else if (key == "CRIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        QString number = QString::number(display_value);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to get a critical strike by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::CritChance, display_value);
    } else if (key == "HIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        QString number = QString::number(display_value);
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to hit by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::HitChance, display_value);
    } else if (key == "ATTACK_POWER") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power.").arg(value));
        this->item_stat_values.insert(ItemStats::AttackPower, value.toUInt());
    } else if (key == "FERAL_ATTACK_POWER") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power in Cat, Bear, and Dire Bear forms only.").arg(value));
        this->item_stat_values.insert(ItemStats::FeralAttackPower, value.toUInt());
    } else if (key == "RANGED_ATTACK_POWER") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Ranged Attack Power.").arg(value));
        this->item_stat_values.insert(ItemStats::RangedAttackPower, value.toUInt());
    } else if (key == "ATTACK_POWER_BEAST") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Beasts.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusBeast, value.toUInt());
    } else if (key == "ATTACK_POWER_DEMON") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Demons.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDemon, value.toUInt());
    } else if (key == "ATTACK_POWER_DRAGONKIN") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Dragonkin.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusDragonkin, value.toUInt());
    } else if (key == "ATTACK_POWER_UNDEAD") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Attack Power when fighting Undead.").arg(value));
        this->item_stat_values.insert(ItemStats::APVersusUndead, value.toUInt());
    } else if (key == "WEAPON_DAMAGE") {
        equip_effects_tooltip_stats.append(QString("Equip: +%1 Weapon Damage.").arg(value));
        this->item_stat_values.insert(ItemStats::FlatWeaponDamage, value.toUInt());
    } else if (key == "AXE_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Axes +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillAxe, value.toUInt());
    } else if (key == "DAGGER_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Daggers +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillDagger, value.toUInt());
    } else if (key == "MACE_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Maces +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillMace, value.toUInt());
    } else if (key == "SWORD_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Swords +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillSword, value.toUInt());
    } else if (key == "TWOHAND_AXE_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Two-handed Axes +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Skill2hAxe, value.toUInt());
    } else if (key == "TWOHAND_MACE_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Two-handed Maces +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Skill2hMace, value.toUInt());
    } else if (key == "TWOHAND_SWORD_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Two-handed Swords +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Skill2hSword, value.toUInt());
    } else if (key == "BOW_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Bows +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillBow, value.toUInt());
    } else if (key == "CROSSBOW_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Crossbows +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillCrossbow, value.toUInt());
    } else if (key == "GUN_SKILL") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Guns +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::SkillGun, value.toUInt());
    } else if (key == "MANA_PER_5") {
        equip_effects_tooltip_stats.append(QString("Equip: Restores %1 mana per 5 sec.").arg(value));
        this->item_stat_values.insert(ItemStats::ManaPer5, value.toUInt());
    } else if (key == "HEALTH_PER_5") {
        equip_effects_tooltip_stats.append(QString("Equip: Restores %1 health per 5 sec.").arg(value));
        this->item_stat_values.insert(ItemStats::HealthPer5, value.toUInt());
    } else if (key == "SPELL_DAMAGE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage and healing done by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamage, value.toUInt());
    } else if (key == "SPELL_DAMAGE_ARCANE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Arcane spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageArcane, value.toUInt());
    } else if (key == "SPELL_DAMAGE_FIRE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Fire spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageFire, value.toUInt());
    } else if (key == "SPELL_DAMAGE_FROST") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Frost spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageFrost, value.toUInt());
    } else if (key == "SPELL_DAMAGE_HOLY") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Holy spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageHoly, value.toUInt());
    } else if (key == "SPELL_DAMAGE_NATURE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Nature spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageNature, value.toUInt());
    } else if (key == "SPELL_DAMAGE_SHADOW") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done by Shadow spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageShadow, value.toUInt());
    } else if (key == "SPELL_DAMAGE_BEAST") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Beasts by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusBeast, value.toUInt());
    } else if (key == "SPELL_DAMAGE_DEMON") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Demons by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusDemon, value.toUInt());
    } else if (key == "SPELL_DAMAGE_DRAGONKIN") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Dragonkin by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusDragonkin, value.toUInt());
    } else if (key == "SPELL_DAMAGE_ELEMENTAL") {
        equip_effects_tooltip_stats.append(
            QString("Equip: Increases damage done to Elementals by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusElemental, value.toUInt());
    } else if (key == "SPELL_DAMAGE_GIANT") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Giants by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusGiant, value.toUInt());
    } else if (key == "SPELL_DAMAGE_HUMANOID") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Humanoids by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusHumanoid, value.toUInt());
    } else if (key == "SPELL_DAMAGE_MECHANICAL") {
        equip_effects_tooltip_stats.append(
            QString("Equip: Increases damage done to Mechanicals by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusMechanical, value.toUInt());
    } else if (key == "SPELL_DAMAGE_UNDEAD") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases damage done to Undead by magical spells and effects by up to %1.").arg(value));
        this->item_stat_values.insert(ItemStats::SpellDamageVersusUndead, value.toUInt());
    } else if (key == "SPELL_CRIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to get a critical strike with spells by %1%.").arg(display_value));
        this->item_stat_values.insert(ItemStats::SpellCrit, display_value);
    } else if (key == "SPELL_HIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        equip_effects_tooltip_stats.append(QString("Equip: Improves your chance to hit with spells by %1%.").arg(display_value));
        this->item_stat_values.insert(ItemStats::SpellHit, display_value);
    } else if (key == "SPELL_PENETRATION") {
        QString number = QString::number(value.toUInt());
        equip_effects_tooltip_stats.append(QString("Equip: Decreases the magical resistances of your spell targets by %1.").arg(number));
        this->item_stat_values.insert(ItemStats::SpellPenetration, value.toUInt());
    } else if (key == "ARMOR") {
        base_tooltip_stats.append(QString("%1 Armor").arg(value));
        this->item_stat_values.insert(ItemStats::Armor, value.toUInt());
    } else if (key == "DEFENSE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increased Defense +%1.").arg(value));
        this->item_stat_values.insert(ItemStats::Defense, value.toUInt());
    } else if (key == "BLOCK_VALUE") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases the block value of your shield by %1.").arg(value));
        this->item_stat_values.insert(ItemStats::BlockValue, value.toUInt());
    } else if (key == "BLOCK_CHANCE") {
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to block attacks with a shield by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::BlockChance, static_cast<unsigned>(value.toDouble() * 100));
    } else if (key == "DODGE_CHANCE") {
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to dodge an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::DodgeChance, static_cast<unsigned>(value.toDouble() * 100));
    } else if (key == "PARRY_CHANCE") {
        QString number = QString::number(value.toDouble() * 100);
        equip_effects_tooltip_stats.append(QString("Equip: Increases your chance to parry an attack by %1%.").arg(number));
        this->item_stat_values.insert(ItemStats::ParryChance, static_cast<unsigned>(value.toDouble() * 100));
    } else if (key == "ALL_RESISTANCE") {
        equip_effects_tooltip_stats.append(QString("+%1 All Resistances.").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceAll, value.toUInt());
    } else if (key == "ARCANE_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Arcane Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceArcane, value.toUInt());
    } else if (key == "FIRE_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Fire Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFire, value.toUInt());
    } else if (key == "FROST_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Frost Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceFrost, value.toUInt());
    } else if (key == "HOLY_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Holy Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceHoly, value.toUInt());
    } else if (key == "NATURE_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Nature Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceNature, value.toUInt());
    } else if (key == "SHADOW_RESISTANCE") {
        base_tooltip_stats.append(QString("+%1 Shadow Resistance").arg(value));
        this->item_stat_values.insert(ItemStats::ResistanceShadow, value.toUInt());
    } else if (key == "RANGED_ATTACK_SPEED") {
        equip_effects_tooltip_stats.append(QString("Equip: Increases ranged attack speed by %1%.").arg(value));
        this->item_stat_values.insert(ItemStats::RangedAttackSpeedPercent, value.toUInt());
    } else
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
    if (!equip_effects_tooltip_stats.empty() && !special_equip_effects.empty())
        return QStringList {get_tooltip(equip_effects_tooltip_stats), get_tooltip(special_equip_effects)}.join("\n");

    if (!equip_effects_tooltip_stats.empty())
        return get_tooltip(equip_effects_tooltip_stats);

    return get_tooltip(special_equip_effects);
}

QString Item::get_tooltip(const QVector<QString>& tt_strings) const {
    QString tooltip = "";
    for (const auto& tt_string : tt_strings) {
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
    if (slot_string == "QUIVER")
        return ItemSlots::QUIVER;

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
    if (type_string == "QUIVER")
        return QuiverTypes::QUIVER;
    if (type_string == "AMMO_POUCH")
        return QuiverTypes::AMMO_POUCH;

    return -1;
}

void Item::unsupported_stat(const QString& stat) {
    qDebug() << "Unsupported stat" << stat << "has no effect on created item";
}
