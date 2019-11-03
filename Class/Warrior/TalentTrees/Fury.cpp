#include "Fury.h"

#include "Buff.h"
#include "Talent.h"
#include "TalentStatIncrease.h"
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Fury::Fury(Warrior* pchar) :
    TalentTree("Fury", "Assets/warrior/warrior_fury.jpg"),
    warrior(pchar),
    spells(static_cast<WarriorSpells*>(pchar->get_spells()))
{
    talent_names_to_locations = {
        {"Booming Voice", "1ML"},
        {"Cruelty", "1MR"},
        {"Improved Demoralizing Shout", "2ML"},
        {"Unbridled Wrath", "2MR"},
        {"Improved Cleave", "3LL"},
        {"Piercing Howl", "3ML"},
        {"Blood Craze", "3MR"},
        {"Improved Battle Shout", "3RR"},
        {"Enrage", "4MR"},
        {"Dual Wield Specialization", "4LL"},
        {"Improved Execute", "4ML"},
        {"Improved Slam", "5LL"},
        {"Death Wish", "5ML"},
        {"Improved Intercept", "5RR"},
        {"Improved Berserker Rage", "6LL"},
        {"Flurry", "6MR"},
        {"Bloodthirst", "7ML"},
    };

    QMap<QString, Talent*> tier1 {};
    add_cruelty(tier1);
    add_booming_voice(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent(pchar, this, "Improved Demoralizing Shout", "2ML", base_url + "ability/Ability_warrior_warcry.png", 5, "Increases the melee attack power reduction of your Demoralizing Shout by %1%.", QVector<QPair<unsigned, unsigned>>{{8, 8}})}};
    add_unbridled_wrath(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(pchar, this, "Improved Cleave", "3LL", base_url + "ability/Ability_warrior_cleave.png", 3, "Increases the bonus damage done by your Cleave ability by %1%.", QVector<QPair<unsigned, unsigned>>{{40, 40}})},
                                  {"3ML", new Talent(pchar, this, "Piercing Howl", "3ML", base_url + "spell/Spell_shadow_deathscream.png", 1, "Causes all enemies near the warrior to be dazed, reducing movement speed by 50% for 6 sec.", QVector<QPair<unsigned, unsigned>>())},
                                  {"3MR", new Talent(pchar, this, "Blood Craze", "3MR", base_url + "spell/Spell_shadow_summonimp.png", 3, "Regenerates %1% of your total Health over 6 sec after being the victim of a critical strike.", QVector<QPair<unsigned, unsigned>>{{1, 1}})}};
    add_improved_battle_shout(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4MR", new Talent(pchar, this, "Enrage", "4MR", base_url + "spell/Spell_shadow_unholyfrenzy.png", 5, "Gives you a %1% melee damage bonus for 12 sec up to a maximum of 12 swings after being the victim of a critical strike.", QVector<QPair<unsigned, unsigned>>{{5, 5}})}};
    add_dual_wield_specialization(tier4);
    add_improved_execute(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5RR", new Talent(pchar, this, "Improved Intercept", "5RR", base_url + "ability/Ability_rogue_sprint.png", 2, "Reduces the cooldown of your Intercept ability by %1 sec.", QVector<QPair<unsigned, unsigned>>{{5, 5}})}};
    add_improved_slam(tier5);
    add_death_wish(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_improved_berserker_rage(tier6);
    add_flurry_talent(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_bloodthirst(tier7);
    add_talents(tier7);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);
}

void Fury::add_booming_voice(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the area of effect and duration of your Battle Shout and Demoralizing Shout by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{10, 10}});
    Talent* talent = new Talent(warrior, this, "Booming Voice", "1ML",
                                "Assets/spell/Spell_nature_purge.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Battle Shout")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_cruelty(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(warrior, this, "Cruelty", "1MR", "Assets/ability/Ability_rogue_eviscerate.png", 5,
                                         "Increases your chance to get a critical strike with melee weapons by %1%.",
                                         QVector<QPair<unsigned, unsigned>>{{1, 1}},
                                         QVector<QPair<TalentStat, unsigned>>{{TalentStat::MeleeCrit, 100}});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_unbridled_wrath(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Gives you a %1% chance to generate an additional Rage point when you deal melee damage with a weapon.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{8, 8}});
    Talent* talent = new Talent(warrior, this, "Unbridled Wrath", "2MR",
                                "Assets/spell/Spell_nature_stoneclawtotem.png", 5, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{spells->get_unbridled_wrath()});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_improved_battle_shout(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the melee attack power bonus of your Battle Shout by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Improved Battle Shout", "3RR",
                                "Assets/ability/Ability_warrior_battleshout.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Battle Shout")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_dual_wield_specialization(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Dual Wield Specialization", "4LL",
                                "Assets/ability/Ability_dualwield.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Offhand Attack")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_improved_execute(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Reduces the rage cost of your Execute ability by %1.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 2, QVector<QPair<unsigned, unsigned>>{{2, 3}});
    Talent* talent = new Talent(warrior, this, "Improved Execute", "4ML",
                                "Assets/items/Inv_sword_48.png", 2, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Execute")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_improved_slam(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Decreases the casting time of your Slam ability by 0.%1 sec.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{1, 1}});
    Talent* talent = new Talent(warrior, this, "Improved Slam", "5LL",
                                "Assets/ability/Ability_warrior_decisivestrike.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Slam")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_death_wish(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "When activated, increases your physical damage by 20% and makes you immune to Fear effects, but lowers your armor and all resistances by 20%. Lasts 30 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(warrior, this, "Death Wish", "5ML",
                                "Assets/spell/Spell_shadow_deathpact.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Death Wish")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_improved_berserker_rage(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "The Berserker Rage ability will generate %1 rage when used.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 2, QVector<QPair<unsigned, unsigned>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Improved Berserker Rage", "6LL",
                                "Assets/spell/Spell_nature_ancestralguardian.png", 2, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Berserker Rage")});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_flurry_talent(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases your attack speed by %1% for your next 3 swings after dealing a melee critical strike.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{10, 5}});
    Talent* talent = new Talent(warrior, this, "Flurry", "6MR",
                                "Assets/ability/Ability_ghoulfrenzy.png", 5, rank_descriptions,
                                {},
                                QVector<Buff*>{spells->get_flurry()});

    add_talent_to_tier(talent_tier, talent);
}

void Fury::add_bloodthirst(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Instantly attack the target causing damage equal to 45% of your attack power. In addition, the next 5 successful melee attacks will restore 10 health. This effect lasts 8 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(warrior, this, "Bloodthirst", "7ML",
                                "Assets/spell/Spell_nature_bloodlust.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Bloodthirst")});

    add_talent_to_tier(talent_tier, talent);
}
