
#include "ExternalBuff.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Target.h"

#include <utility>

ExternalBuff::ExternalBuff(Character* pchar,
                           const QString& name,
                           const int dur,
                           const int base_charges,
                           ExternalBuffName buff_name,
                           QString icon,
                           QString description,
                           QVersionNumber min_patch):
    Buff(pchar, name, dur, base_charges),
    buff_name(buff_name),
    icon(std::move(icon)),
    description(std::move(description)),
    min_patch(std::move(min_patch))
{
    this->enabled = true;
}

ExternalBuff::~ExternalBuff() = default;

QString ExternalBuff::get_icon() const {
    return this->icon;
}

QString ExternalBuff::get_description() const {
    return this->description;
}

bool ExternalBuff::valid_for_patch(const QString& patch) const {
    QVersionNumber new_version = QVersionNumber::fromString(patch);

    return min_patch <= new_version;
}

void ExternalBuff::buff_effect_when_applied() {
    switch (buff_name) {
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        pchar->get_stats()->increase_spell_crit(0.10);
        pchar->get_stats()->increase_crit(0.05);
        pchar->get_stats()->increase_melee_ap(140);
        break;
    case ExternalBuffName::SpiritOfZandalar:
        pchar->get_stats()->add_total_stat_mod(15);
        break;
    case ExternalBuffName::SongflowerSerenade:
        pchar->get_stats()->increase_crit(0.05);
        pchar->get_stats()->increase_agility(15);
        pchar->get_stats()->increase_strength(15);
        pchar->get_stats()->increase_stamina(15);
        pchar->get_stats()->increase_intellect(15);
        pchar->get_stats()->increase_spirit(15);
        break;
    case ExternalBuffName::ElixirOfTheMongoose:
        pchar->get_stats()->increase_agility(25);
        pchar->get_stats()->increase_crit(0.02);
        break;
    case ExternalBuffName::ElixirOfBruteForce:
        pchar->get_stats()->increase_strength(18);
        pchar->get_stats()->increase_stamina(18);
        break;
    case ExternalBuffName::ElixirOfGiants:
        pchar->get_stats()->increase_strength(25);
        break;
    case ExternalBuffName::WinterfallFirewater:
        pchar->get_stats()->increase_melee_ap(35);
        break;
    case ExternalBuffName::JujuPower:
        pchar->get_stats()->increase_strength(30);
        break;
    case ExternalBuffName::MarkOfTheWild:
        pchar->get_stats()->increase_agility(16);
        pchar->get_stats()->increase_strength(16);
        pchar->get_stats()->increase_stamina(16);
        pchar->get_stats()->increase_intellect(16);
        pchar->get_stats()->increase_spirit(16);
        break;
    case ExternalBuffName::ScrollOfStrengthIV:
        pchar->get_stats()->increase_strength(17);
        break;
    case ExternalBuffName::SmokedDesertDumplings:
        pchar->get_stats()->increase_strength(20);
        break;
    case ExternalBuffName::Annihilator:
        pchar->get_target()->decrease_armor(600);
        break;
    case ExternalBuffName::CurseOfRecklessness:
        pchar->get_target()->decrease_armor(640);
        break;
    case ExternalBuffName::FaerieFire:
        pchar->get_target()->decrease_armor(505);
        break;
    case ExternalBuffName::SunderArmor:
        pchar->get_target()->decrease_armor(2250);
        break;
    }
}

void ExternalBuff::buff_effect_when_removed() {
    switch (buff_name) {
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        pchar->get_stats()->decrease_spell_crit(0.10);
        pchar->get_stats()->decrease_crit(0.05);
        pchar->get_stats()->decrease_melee_ap(140);
        break;
    case ExternalBuffName::SpiritOfZandalar:
        pchar->get_stats()->remove_total_stat_mod(15);
        break;
    case ExternalBuffName::SongflowerSerenade:
        pchar->get_stats()->decrease_crit(0.05);
        pchar->get_stats()->decrease_agility(15);
        pchar->get_stats()->decrease_strength(15);
        pchar->get_stats()->decrease_stamina(15);
        pchar->get_stats()->decrease_intellect(15);
        pchar->get_stats()->decrease_spirit(15);
        break;
    case ExternalBuffName::ElixirOfTheMongoose:
        pchar->get_stats()->decrease_agility(25);
        pchar->get_stats()->decrease_crit(0.02);
        break;
    case ExternalBuffName::ElixirOfBruteForce:
        pchar->get_stats()->decrease_strength(18);
        pchar->get_stats()->decrease_stamina(18);
        break;
    case ExternalBuffName::ElixirOfGiants:
        pchar->get_stats()->decrease_strength(25);
        break;
    case ExternalBuffName::WinterfallFirewater:
        pchar->get_stats()->decrease_melee_ap(35);
        break;
    case ExternalBuffName::JujuPower:
        pchar->get_stats()->decrease_strength(30);
        break;
    case ExternalBuffName::MarkOfTheWild:
        pchar->get_stats()->decrease_agility(16);
        pchar->get_stats()->decrease_strength(16);
        pchar->get_stats()->decrease_stamina(16);
        pchar->get_stats()->decrease_intellect(16);
        pchar->get_stats()->decrease_spirit(16);
        break;
    case ExternalBuffName::ScrollOfStrengthIV:
        pchar->get_stats()->decrease_strength(17);
        break;
    case ExternalBuffName::SmokedDesertDumplings:
        pchar->get_stats()->decrease_strength(20);
        break;
    case ExternalBuffName::Annihilator:
        pchar->get_target()->increase_armor(600);
        break;
    case ExternalBuffName::CurseOfRecklessness:
        pchar->get_target()->increase_armor(640);
        break;
    case ExternalBuffName::FaerieFire:
        pchar->get_target()->increase_armor(505);
        break;
    case ExternalBuffName::SunderArmor:
        pchar->get_target()->increase_armor(2250);
        break;
    }
}

ExternalBuff* get_external_buff_by_name(const ExternalBuffName name, Character* pchar) {
    switch (name) {
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        return new ExternalBuff(pchar, "Rallying Cry of the Dragonslayer", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_misc_head_dragon_01.png",
                                "+10% Spell crit, +5% melee/ranged crit, +140 attack power",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SpiritOfZandalar:
        return new ExternalBuff(pchar, "Spirit of Zandalar", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Ability_creature_poison_05.png",
                                "Increases movement speed by 10% and all stats by 15%",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SongflowerSerenade:
        return new ExternalBuff(pchar, "Songflower Serenade", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Spell_holy_mindvision.png",
                                "+5% Crit, +15 all attributes",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfTheMongoose:
        return new ExternalBuff(pchar, "Elixir of the Mongoose", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_potion_32.png",
                                "+25 Agility, +%2 Critical Strike",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfBruteForce:
        return new ExternalBuff(pchar, "Elixir of Brute Force", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_potion_40.png",
                                "+18 Strength and Stamina",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfGiants:
        return new ExternalBuff(pchar, "Elixir of Giants", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_potion_61.png",
                                "+25 Strength",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::WinterfallFirewater:
        return new ExternalBuff(pchar, "Winterfall Firewater", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_potion_92.png",
                                "+35 Melee attack power",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::JujuPower:
        return new ExternalBuff(pchar, "Juju Power", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_misc_monsterscales_11.png",
                                "+30 Strength",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::MarkOfTheWild:
        return new ExternalBuff(pchar, "Mark of the Wild", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Spell_nature_regeneration.png",
                                "+16 all attributes, +384 armor, +27 all resistances",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ScrollOfStrengthIV:
        return new ExternalBuff(pchar, "Scroll of Strength IV", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_scroll_02.png",
                                "+17 Strength",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SmokedDesertDumplings:
        return new ExternalBuff(pchar, "Smoked Desert Dumplings", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Inv_misc_food_64.png",
                                "+20 Strength",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::Annihilator:
        return new ExternalBuff(pchar, "Annihilator Proc", BuffDuration::PERMANENT, 0,
                                name, "Assets/items/Inv_axe_12.png",
                                "Reduces target armor by 600.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::CurseOfRecklessness:
        return new ExternalBuff(pchar, "Curse of Recklessness", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Spell_shadow_unholystrength.png",
                                "Reduces target armor by 640.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::FaerieFire:
        return new ExternalBuff(pchar, "Faerie Fire", BuffDuration::PERMANENT, 0,
                                name, "Assets/buffs/Spell_nature_faeriefire.png",
                                "Reduces target armor by 505.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SunderArmor:
        return new ExternalBuff(pchar, "Sunder Armor", BuffDuration::PERMANENT, 0,
                                name, "Assets/warrior/protection/tier4/Ability_warrior_sunder.png",
                                "Reduces target armor by 2250.",
                                QVersionNumber::fromString("1.0.0"));
    }

    return nullptr;
}
