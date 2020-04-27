#include "ExternalBuff.h"

#include <utility>

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "DragonbreathChili.h"
#include "Target.h"
#include "Utils/Check.h"

ExternalBuff::ExternalBuff(Character* pchar,
                           const QString& name,
                           const int dur,
                           const int base_charges,
                           ExternalBuffName buff_name,
                           AvailableFactions::Name faction,
                           QString icon,
                           QString description) :
    SelfBuff(pchar, name, icon, dur, base_charges), buff_name(buff_name), faction(faction), description(std::move(description)) {
    this->enabled = true;
    this->hidden = true;
}

ExternalBuff::~ExternalBuff() {
    if (this->is_active())
        cancel_buff();
}

QString ExternalBuff::get_description() const {
    return this->description;
}

bool ExternalBuff::valid_for_faction(AvailableFactions::Name faction) const {
    if (this->faction == AvailableFactions::Neutral)
        return true;

    return this->faction == faction;
}

void ExternalBuff::buff_effect_when_applied() {
    switch (buff_name) {
    case ExternalBuffName::BattleShout:
        pchar->get_stats()->increase_melee_ap(232);
        break;
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        pchar->get_stats()->increase_spell_crit(1000);
        pchar->get_stats()->increase_ranged_crit(500);
        pchar->get_stats()->increase_melee_aura_crit(500);
        pchar->get_stats()->increase_melee_ap(140);
        break;
    case ExternalBuffName::SpiritOfZandalar:
        pchar->get_stats()->add_total_stat_mod(15);
        break;
    case ExternalBuffName::SongflowerSerenade:
        pchar->get_stats()->increase_melee_aura_crit(500);
        pchar->get_stats()->increase_spell_crit(500);
        pchar->get_stats()->increase_ranged_crit(500);
        pchar->get_stats()->increase_agility(15);
        pchar->get_stats()->increase_strength(15);
        pchar->get_stats()->increase_stamina(15);
        pchar->get_stats()->increase_intellect(15);
        pchar->get_stats()->increase_spirit(15);
        break;
    case ExternalBuffName::ElixirOfTheMongoose:
        pchar->get_stats()->increase_agility(25);
        pchar->get_stats()->increase_melee_aura_crit(200);
        pchar->get_stats()->increase_ranged_crit(200);
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
    case ExternalBuffName::ROIDS:
        pchar->get_stats()->increase_strength(25);
        break;
    case ExternalBuffName::BlessingOfKings:
        pchar->get_stats()->add_total_stat_mod(10);
        break;
    case ExternalBuffName::BlessingOfMight:
        pchar->get_stats()->increase_melee_ap(185);
        break;
    case ExternalBuffName::BlessingOfWisdom:
        pchar->get_stats()->increase_mp5(33);
        break;
    case ExternalBuffName::TotemStrengthOfEarth:
        pchar->get_stats()->increase_strength(77);
        break;
    case ExternalBuffName::TotemManaSpring:
        pchar->get_stats()->increase_mp5(25);
        break;
    case ExternalBuffName::Annihilator:
        pchar->get_target()->decrease_armor(600);
        break;
    case ExternalBuffName::CurseOfRecklessness:
        pchar->get_target()->decrease_armor(640);
        break;
    case ExternalBuffName::CerebralCortexCompound:
        pchar->get_stats()->increase_intellect(25);
        break;
    case ExternalBuffName::FaerieFire:
        pchar->get_target()->decrease_armor(505);
        break;
    case ExternalBuffName::SunderArmor:
        pchar->get_target()->decrease_armor(2250);
        break;
    case ExternalBuffName::GrilledSquid:
        pchar->get_stats()->increase_agility(10);
        break;
    case ExternalBuffName::RunnTumTuberSurprise:
        pchar->get_stats()->increase_intellect(10);
        break;
    case ExternalBuffName::MagebloodPotion:
        pchar->get_stats()->increase_mp5(12);
        break;
    case ExternalBuffName::FlaskOfDistilledWisdom:
        pchar->increase_base_mana(2000);
        break;
    case ExternalBuffName::FlaskOfSupremePower:
        pchar->get_stats()->increase_base_spell_damage(150);
        break;
    case ExternalBuffName::FengusFerocity:
        pchar->get_stats()->increase_melee_ap(200);
        break;
    case ExternalBuffName::BattleSquawk:
        pchar->get_stats()->increase_melee_attack_speed(5);
        break;
    case ExternalBuffName::GreaterArcaneElixir:
        pchar->get_stats()->increase_base_spell_damage(35);
        break;
    case ExternalBuffName::GroundScorpokAssay:
        pchar->get_stats()->increase_agility(25);
        break;
    case ExternalBuffName::JujuMight:
        pchar->get_stats()->increase_melee_ap(40);
        break;
    case ExternalBuffName::SlipkiksSavvy:
        pchar->get_stats()->increase_spell_crit(300);
        break;
    case ExternalBuffName::SaygesDarkFortuneOfDamage:
        pchar->get_stats()->increase_total_phys_dmg_mod(10);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Arcane);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Fire);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Frost);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Holy);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Nature);
        pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Shadow);
        break;
    case ExternalBuffName::NightfinSoup:
        pchar->get_stats()->increase_mp5(8);
        break;
    case ExternalBuffName::TrueshotAura:
        pchar->get_stats()->increase_melee_ap(100);
        pchar->get_stats()->increase_ranged_ap(100);
        break;
    case ExternalBuffName::ImprovedShadowBolt:
        pchar->get_stats()->increase_magic_school_damage_mod(20, MagicSchool::Shadow);
        break;
    case ExternalBuffName::DragonbreathChili:
        pchar->get_spells()->get_dragonbreath_chili()->enable();
        pchar->get_spells()->get_dragonbreath_chili()->enable_proc();
        break;
    case ExternalBuffName::FireVulnerability:
        pchar->get_stats()->increase_magic_school_damage_mod(15, MagicSchool::Fire);
        break;
    case ExternalBuffName::ElixirOfGreaterAgility:
        pchar->get_stats()->increase_agility(25);
        break;
    case ExternalBuffName::CurseOfTheElements:
        pchar->get_target()->increase_magic_school_damage_mod(10, MagicSchool::Fire);
        pchar->get_target()->increase_magic_school_damage_mod(10, MagicSchool::Frost);
        pchar->get_target()->decrease_resistance(MagicSchool::Fire, 75);
        pchar->get_target()->decrease_resistance(MagicSchool::Frost, 75);
        break;
    case ExternalBuffName::CurseOfShadow:
        pchar->get_target()->increase_magic_school_damage_mod(10, MagicSchool::Arcane);
        pchar->get_target()->increase_magic_school_damage_mod(10, MagicSchool::Shadow);
        pchar->get_target()->decrease_resistance(MagicSchool::Arcane, 75);
        pchar->get_target()->decrease_resistance(MagicSchool::Shadow, 75);
        break;
    case ExternalBuffName::ShadowWeaving:
        pchar->get_target()->increase_magic_school_damage_mod(15, MagicSchool::Shadow);
        break;
    case ExternalBuffName::BlessedSunfruit:
        pchar->get_stats()->increase_strength(10);
        break;
    case ExternalBuffName::WarchiefsBlessing:
        pchar->get_stats()->increase_melee_attack_speed(15);
        pchar->get_stats()->increase_mp5(10);
        break;
    }
}

void ExternalBuff::buff_effect_when_removed() {
    switch (buff_name) {
    case ExternalBuffName::BattleShout:
        pchar->get_stats()->decrease_melee_ap(232);
        break;
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        pchar->get_stats()->decrease_spell_crit(1000);
        pchar->get_stats()->decrease_ranged_crit(500);
        pchar->get_stats()->decrease_melee_aura_crit(500);
        pchar->get_stats()->decrease_melee_ap(140);
        break;
    case ExternalBuffName::SpiritOfZandalar:
        pchar->get_stats()->remove_total_stat_mod(15);
        break;
    case ExternalBuffName::SongflowerSerenade:
        pchar->get_stats()->decrease_melee_aura_crit(500);
        pchar->get_stats()->decrease_spell_crit(500);
        pchar->get_stats()->decrease_ranged_crit(500);
        pchar->get_stats()->decrease_agility(15);
        pchar->get_stats()->decrease_strength(15);
        pchar->get_stats()->decrease_stamina(15);
        pchar->get_stats()->decrease_intellect(15);
        pchar->get_stats()->decrease_spirit(15);
        break;
    case ExternalBuffName::ElixirOfTheMongoose:
        pchar->get_stats()->decrease_agility(25);
        pchar->get_stats()->decrease_melee_aura_crit(200);
        pchar->get_stats()->decrease_ranged_crit(200);
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
    case ExternalBuffName::ROIDS:
        pchar->get_stats()->decrease_strength(25);
        break;
    case ExternalBuffName::BlessingOfKings:
        pchar->get_stats()->remove_total_stat_mod(10);
        break;
    case ExternalBuffName::BlessingOfMight:
        pchar->get_stats()->decrease_melee_ap(185);
        break;
    case ExternalBuffName::BlessingOfWisdom:
        pchar->get_stats()->decrease_mp5(33);
        break;
    case ExternalBuffName::TotemStrengthOfEarth:
        pchar->get_stats()->decrease_strength(77);
        break;
    case ExternalBuffName::TotemManaSpring:
        pchar->get_stats()->decrease_mp5(25);
        break;
    case ExternalBuffName::Annihilator:
        pchar->get_target()->increase_armor(600);
        break;
    case ExternalBuffName::CurseOfRecklessness:
        pchar->get_target()->increase_armor(640);
        break;
    case ExternalBuffName::CerebralCortexCompound:
        pchar->get_stats()->decrease_intellect(25);
        break;
    case ExternalBuffName::FaerieFire:
        pchar->get_target()->increase_armor(505);
        break;
    case ExternalBuffName::SunderArmor:
        pchar->get_target()->increase_armor(2250);
        break;
    case ExternalBuffName::GrilledSquid:
        pchar->get_stats()->decrease_agility(10);
        break;
    case ExternalBuffName::RunnTumTuberSurprise:
        pchar->get_stats()->decrease_intellect(10);
        break;
    case ExternalBuffName::MagebloodPotion:
        pchar->get_stats()->decrease_mp5(12);
        break;
    case ExternalBuffName::FlaskOfDistilledWisdom:
        pchar->decrease_base_mana(2000);
        break;
    case ExternalBuffName::FlaskOfSupremePower:
        pchar->get_stats()->decrease_base_spell_damage(150);
        break;
    case ExternalBuffName::FengusFerocity:
        pchar->get_stats()->decrease_melee_ap(200);
        break;
    case ExternalBuffName::BattleSquawk:
        pchar->get_stats()->decrease_melee_attack_speed(5);
        break;
    case ExternalBuffName::GreaterArcaneElixir:
        pchar->get_stats()->decrease_base_spell_damage(35);
        break;
    case ExternalBuffName::GroundScorpokAssay:
        pchar->get_stats()->decrease_agility(25);
        break;
    case ExternalBuffName::JujuMight:
        pchar->get_stats()->decrease_melee_ap(40);
        break;
    case ExternalBuffName::SlipkiksSavvy:
        pchar->get_stats()->decrease_spell_crit(300);
        break;
    case ExternalBuffName::SaygesDarkFortuneOfDamage:
        pchar->get_stats()->decrease_total_phys_dmg_mod(10);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Arcane);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Fire);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Frost);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Holy);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Nature);
        pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Shadow);
        break;
    case ExternalBuffName::NightfinSoup:
        pchar->get_stats()->decrease_mp5(8);
        break;
    case ExternalBuffName::TrueshotAura:
        pchar->get_stats()->decrease_melee_ap(100);
        pchar->get_stats()->decrease_ranged_ap(100);
        break;
    case ExternalBuffName::ImprovedShadowBolt:
        pchar->get_stats()->decrease_magic_school_damage_mod(20, MagicSchool::Shadow);
        break;
    case ExternalBuffName::DragonbreathChili:
        pchar->get_spells()->get_dragonbreath_chili()->disable_proc();
        pchar->get_spells()->get_dragonbreath_chili()->disable();
        break;
    case ExternalBuffName::FireVulnerability:
        pchar->get_stats()->decrease_magic_school_damage_mod(15, MagicSchool::Fire);
        break;
    case ExternalBuffName::ElixirOfGreaterAgility:
        pchar->get_stats()->decrease_agility(25);
        break;
    case ExternalBuffName::CurseOfTheElements:
        pchar->get_target()->decrease_magic_school_damage_mod(10, MagicSchool::Fire);
        pchar->get_target()->decrease_magic_school_damage_mod(10, MagicSchool::Frost);
        pchar->get_target()->increase_resistance(MagicSchool::Fire, 75);
        pchar->get_target()->increase_resistance(MagicSchool::Frost, 75);
        break;
    case ExternalBuffName::CurseOfShadow:
        pchar->get_target()->decrease_magic_school_damage_mod(10, MagicSchool::Arcane);
        pchar->get_target()->decrease_magic_school_damage_mod(10, MagicSchool::Shadow);
        pchar->get_target()->increase_resistance(MagicSchool::Arcane, 75);
        pchar->get_target()->increase_resistance(MagicSchool::Shadow, 75);
        break;
    case ExternalBuffName::ShadowWeaving:
        pchar->get_target()->decrease_magic_school_damage_mod(15, MagicSchool::Shadow);
        break;
    case ExternalBuffName::BlessedSunfruit:
        pchar->get_stats()->decrease_strength(10);
        break;
    case ExternalBuffName::WarchiefsBlessing:
        pchar->get_stats()->decrease_melee_attack_speed(15);
        pchar->get_stats()->decrease_mp5(10);
        break;
    }
}

ExternalBuff* get_external_buff_by_name(const ExternalBuffName name, Character* pchar) {
    switch (name) {
    case ExternalBuffName::BattleShout:
        return new ExternalBuff(pchar, "Improved Battle Shout", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/ability/Ability_warrior_battleshout.png", "+232 attack power");
    case ExternalBuffName::RallyingCryOfTheDragonslayer:
        return new ExternalBuff(pchar, "Rallying Cry of the Dragonslayer", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_head_dragon_01.png", "+10% Spell crit, +5% melee/ranged crit, +140 attack power");
    case ExternalBuffName::SpiritOfZandalar:
        return new ExternalBuff(pchar, "Spirit of Zandalar", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/ability/Ability_creature_poison_05.png", "Increases movement speed by 10% and all stats by 15%");
    case ExternalBuffName::SongflowerSerenade:
        return new ExternalBuff(pchar, "Songflower Serenade", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_holy_mindvision.png", "+5% Crit, +15 all attributes");
    case ExternalBuffName::ElixirOfTheMongoose:
        return new ExternalBuff(pchar, "Elixir of the Mongoose", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_32.png", "+25 Agility, +%2 Critical Strike");
    case ExternalBuffName::ElixirOfBruteForce:
        return new ExternalBuff(pchar, "Elixir of Brute Force", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_40.png", "+18 Strength and Stamina");
    case ExternalBuffName::ElixirOfGiants:
        return new ExternalBuff(pchar, "Elixir of Giants", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_61.png", "+25 Strength");
    case ExternalBuffName::WinterfallFirewater:
        return new ExternalBuff(pchar, "Winterfall Firewater", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_92.png", "+35 Melee attack power");
    case ExternalBuffName::JujuPower:
        return new ExternalBuff(pchar, "Juju Power", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_monsterscales_11.png", "+30 Strength");
    case ExternalBuffName::MarkOfTheWild:
        return new ExternalBuff(pchar, "Mark of the Wild", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_nature_regeneration.png", "+16 all attributes, +384 armor, +27 all resistances");
    case ExternalBuffName::ScrollOfStrengthIV:
        return new ExternalBuff(pchar, "Scroll of Strength IV", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_scroll_02.png", "+17 Strength");
    case ExternalBuffName::SmokedDesertDumplings:
        return new ExternalBuff(pchar, "Smoked Desert Dumplings", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_food_64.png", "+20 Strength");
    case ExternalBuffName::ROIDS:
        return new ExternalBuff(pchar, "R.O.I.D.S", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral, "Assets/misc/Inv_stone_15.png",
                                "+25 Strength");
    case ExternalBuffName::BlessingOfKings:
        return new ExternalBuff(pchar, "Greater Blessing of Kings", BuffDuration::PERMANENT, 0, name, AvailableFactions::Alliance,
                                "Assets/spell/Spell_magic_greaterblessingofkings.png", "Increases total stats by 10%");
    case ExternalBuffName::BlessingOfMight:
        return new ExternalBuff(pchar, "Greater Blessing of Might", BuffDuration::PERMANENT, 0, name, AvailableFactions::Alliance,
                                "Assets/spell/Spell_holy_greaterblessingofkings.png", "Increases melee attack power by 185");
    case ExternalBuffName::BlessingOfWisdom:
        return new ExternalBuff(pchar, "Greater Blessing of Wisdom", BuffDuration::PERMANENT, 0, name, AvailableFactions::Alliance,
                                "Assets/spell/Spell_holy_greaterblessingofwisdom.png", "Restores 33 mana every 5 seconds.");
    case ExternalBuffName::TotemStrengthOfEarth:
        return new ExternalBuff(pchar, "Strength of Earth Totem", BuffDuration::PERMANENT, 0, name, AvailableFactions::Horde,
                                "Assets/spell/Spell_nature_earthbindtotem.png", "+77 Strength");
    case ExternalBuffName::TotemManaSpring:
        return new ExternalBuff(pchar, "Mana Spring Totem", BuffDuration::PERMANENT, 0, name, AvailableFactions::Horde,
                                "Assets/spell/Spell_nature_manaregentotem.png", "Restores 10 mana every 2 seconds.");
    case ExternalBuffName::Annihilator:
        return new ExternalBuff(pchar, "Annihilator Proc", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/items/Inv_axe_12.png", "Reduces target armor by 600.");
    case ExternalBuffName::CurseOfRecklessness:
        return new ExternalBuff(pchar, "Curse of Recklessness", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_shadow_unholystrength.png", "Reduces target armor by 640.");
    case ExternalBuffName::CerebralCortexCompound:
        return new ExternalBuff(pchar, "Cerebral Cortex Compound", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_32.png", "+25 Intellect");
    case ExternalBuffName::FaerieFire:
        return new ExternalBuff(pchar, "Faerie Fire", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_nature_faeriefire.png", "Reduces target armor by 505.");
    case ExternalBuffName::SunderArmor:
        return new ExternalBuff(pchar, "Sunder Armor", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/ability/Ability_warrior_sunder.png", "Reduces target armor by 2250.");
    case ExternalBuffName::GrilledSquid:
        return new ExternalBuff(pchar, "Grilled Squid", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_fish_13.png", "+10 Agility");
    case ExternalBuffName::RunnTumTuberSurprise:
        return new ExternalBuff(pchar, "Runn Tum Tuber Surprise", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_food_63.png", "+10 Intellect");
    case ExternalBuffName::MagebloodPotion:
        return new ExternalBuff(pchar, "Mageblood Potion", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_45.png", "Regenerate 12 mana per 5 sec");
    case ExternalBuffName::FlaskOfDistilledWisdom:
        return new ExternalBuff(pchar, "Flask of Distilled Wisdom", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_97.png", "Increases maximum mana by 2000");
    case ExternalBuffName::FlaskOfSupremePower:
        return new ExternalBuff(pchar, "Flask of Supreme Power", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_41.png", "+150 Spell Damage");
    case ExternalBuffName::FengusFerocity:
        return new ExternalBuff(pchar, "Fengus' Ferocity", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_nature_undyingstrength.png", "Melee Attack power increased by 200");
    case ExternalBuffName::BattleSquawk:
        return new ExternalBuff(pchar, "Battle Squawk", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_birdbeck_01.png", "Melee Attack speed increased by 5%");
    case ExternalBuffName::GreaterArcaneElixir:
        return new ExternalBuff(pchar, "Greater Arcane Elixir", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/items/Inv_potion_25.png", "35 Spell Damage");
    case ExternalBuffName::GroundScorpokAssay:
        return new ExternalBuff(pchar, "Ground Scorpok Assay", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_dust_02.png", "+25 Agility");
    case ExternalBuffName::JujuMight:
        return new ExternalBuff(pchar, "Juju Might", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_monsterscales_07.png", "+40 Attack Power");
    case ExternalBuffName::SlipkiksSavvy:
        return new ExternalBuff(pchar, "Slip'kik's Savvy", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_holy_lesserheal02.png", "3% Spell Crit");
    case ExternalBuffName::SaygesDarkFortuneOfDamage:
        return new ExternalBuff(pchar, "Sayge's Dark Fortune of Damage", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_orb_02.png", "Increases damage by 10%");
    case ExternalBuffName::NightfinSoup:
        return new ExternalBuff(pchar, "Nightfin Soup", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral, "Assets/misc/Inv_drink_17.png",
                                "Restores 8 mana per 5 sec");
    case ExternalBuffName::TrueshotAura:
        return new ExternalBuff(pchar, "Trueshot Aura", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/ability/Ability_trueshot.png", "+100 Attack Power");
    case ExternalBuffName::ImprovedShadowBolt:
        return new ExternalBuff(pchar, "Improved Shadow Bolt", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_shadow_shadowbolt.png", "20% Shadow Damage");
    case ExternalBuffName::DragonbreathChili:
        return new ExternalBuff(pchar, "Dragonbreath Chili", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_drink_17.png", "Occasionally belch flames");
    case ExternalBuffName::FireVulnerability:
        return new ExternalBuff(pchar, "Fire Vulnerability", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_fire_soulburn.png", "15% Fire Damage");
    case ExternalBuffName::ElixirOfGreaterAgility:
        return new ExternalBuff(pchar, "Elixir of Greater Agility", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_potion_94.png", "+25 Agility");
    case ExternalBuffName::CurseOfTheElements:
        return new ExternalBuff(pchar, "Curse of the Elements", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_shadow_chilltouch.png", "10% Fire/Frost damage,\n-75 Fire/Frost resistances");
    case ExternalBuffName::CurseOfShadow:
        return new ExternalBuff(pchar, "Curse of Shadow", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_shadow_curseofachimonde.png", "10% Arcane/Shadow damage,\n-75 Arcane/Shadow resistances");
    case ExternalBuffName::ShadowWeaving:
        return new ExternalBuff(pchar, "Shadow Weaving", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_shadow_blackplague.png", "15% Shadow Damage");
    case ExternalBuffName::BlessedSunfruit:
        return new ExternalBuff(pchar, "Blessed Sunfruit", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/misc/Inv_misc_food_41.png", "+10 Strength");
    case ExternalBuffName::WarchiefsBlessing:
        return new ExternalBuff(pchar, "Warchief's Blessing", BuffDuration::PERMANENT, 0, name, AvailableFactions::Neutral,
                                "Assets/spell/Spell_arcane_teleportorgrimmar.png", "+300 hitpoints, 15% melee haste, +10 mp5");
    }

    return nullptr;
}
