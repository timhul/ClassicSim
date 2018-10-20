
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
        return new ExternalBuff(pchar, "Rallying Cry of the Dragonslayer", BuffDuration::PERMANENT, 1,
                                ExternalBuffName::RallyingCryOfTheDragonslayer,
                                "Assets/buffs/Inv_misc_head_dragon_01.png",
                                "+10% Spell crit, +5% melee/ranged crit, +140 attack power",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SongflowerSerenade:
        return new ExternalBuff(pchar, "Songflower Serenade", BuffDuration::PERMANENT, 1,
                                ExternalBuffName::SongflowerSerenade,
                                "Assets/buffs/Spell_holy_mindvision.png",
                                "+5% Crit, +15 all attributes",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfTheMongoose:
        return new ExternalBuff(pchar, "Elixir of the Mongoose", BuffDuration::PERMANENT, 1,
                                ExternalBuffName::ElixirOfTheMongoose,
                                "Assets/buffs/Inv_potion_32.png",
                                "+25 Agility, +%2 Critical Strike",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfBruteForce:
        return new ExternalBuff(pchar, "Elixir of Brute Force", BuffDuration::PERMANENT, 1,
                                ExternalBuffName::ElixirOfBruteForce,
                                "Assets/buffs/Inv_potion_40.png",
                                "+18 Strength and Stamina",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::ElixirOfGiants:
        return new ExternalBuff(pchar, "Elixir of Giants", BuffDuration::PERMANENT, 1,
                                ExternalBuffName::ElixirOfGiants,
                                "Assets/buffs/Inv_potion_61.png",
                                "+25 Strength",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::Annihilator:
        return new ExternalBuff(pchar, "Annihilator Proc", BuffDuration::PERMANENT, 0,
                                ExternalBuffName::Annihilator,
                                "Assets/items/Inv_axe_12.png",
                                "Reduces target armor by 600.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::CurseOfRecklessness:
        return new ExternalBuff(pchar, "Curse of Recklessness", BuffDuration::PERMANENT, 0,
                                ExternalBuffName::CurseOfRecklessness,
                                "Assets/buffs/Spell_shadow_unholystrength.png",
                                "Reduces target armor by 640.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::FaerieFire:
        return new ExternalBuff(pchar, "Faerie Fire", BuffDuration::PERMANENT, 0,
                                ExternalBuffName::FaerieFire,
                                "Assets/buffs/Spell_nature_faeriefire.png",
                                "Reduces target armor by 505.",
                                QVersionNumber::fromString("1.0.0"));
    case ExternalBuffName::SunderArmor:
        return new ExternalBuff(pchar, "Sunder Armor", BuffDuration::PERMANENT, 0,
                                ExternalBuffName::SunderArmor,
                                "Assets/warrior/protection/tier4/Ability_warrior_sunder.png",
                                "Reduces target armor by 2250.",
                                QVersionNumber::fromString("1.0.0"));
    }

    return nullptr;
}
