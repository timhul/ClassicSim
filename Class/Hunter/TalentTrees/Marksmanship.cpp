#include "Marksmanship.h"

#include "AimedShot.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "HuntersMark.h"
#include "HuntersMarkBuff.h"
#include "MultiShot.h"
#include "TalentStatIncrease.h"

Marksmanship::Marksmanship(Hunter* hunter) :
    TalentTree("Marksmanship", "Assets/hunter/hunter_marksmanship.jpg"), hunter(hunter), spells(static_cast<HunterSpells*>(hunter->get_spells())) {
    talent_names_to_locations = {
        {"Improved Concussive Shot", "1ML"},
        {"Efficiency", "1MR"},
        {"Improved Hunter's Mark", "2ML"},
        {"Lethal Shots", "2MR"},
        {"Aimed Shot", "3LL"},
        {"Improved Arcane Shot", "3ML"},
        {"Hawk Eye", "3RR"},
        {"Improved Serpent Sting", "4ML"},
        {"Mortal Shots", "4MR"},
        {"Scatter Shot", "5LL"},
        {"Barrage", "5ML"},
        {"Improved Scorpid Sting", "5MR"},
        {"Ranged Weapon Specialization", "6MR"},
        {"Trueshot Aura", "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(hunter, this, "Improved Concussive Shot", "1ML", "Assets/spell/Spell_frost_stun.png", 5,
                           "Gives your Concussive Shot a %1% chance to stun the target for 3 sec.", QVector<QPair<unsigned, unsigned>> {{4, 4}})}};
    add_efficiency(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {};
    add_improved_hunters_mark(tier2);
    add_lethal_shots(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3ML",
                                   new Talent(hunter, this, "Improved Arcane Shot", "3ML", "Assets/ability/Ability_impalingbolt.png", 5,
                                              "Reduces the cooldown of your Arcane Shot by %1 sec.", QVector<QPair<double, double>> {{0.2, 0.2}})},
                                  {"3RR", new Talent(hunter, this, "Hawk Eye", "3RR", "Assets/ability/Ability_townwatch.png", 3,
                                                     "Increases the range of your ranged weapons by %1 yards.",
                                                     QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_aimed_shot(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4ML", new Talent(hunter, this, "Improved Serpent Sting", "4ML", "Assets/ability/Ability_hunter_quickshot.png", 5,
                           "Increases the damage done by your Serpent Sting by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_mortal_shots(tier4);
    add_talents(tier4);

    QMap<QString, Talent*>
        tier5 {{"5LL", new Talent(hunter, this, "Scatter Shot", "5LL", "Assets/ability/Ability_golemstormbolt.png", 1,
                                  "A short-range shot that deals 50% weapon damage and disorients the target for 4 sec. Any damage caused will "
                                  "remove the effect. Turns off your attack when used.",
                                  QVector<QPair<unsigned, unsigned>>())},
               {"5MR", new Talent(hunter, this, "Improved Scorpid Sting", "5MR", "Assets/ability/Ability_hunter_criticalshot.png", 3,
                                  "Reduces the Stamina of targets affected by your Scorpid Sting by %1% of the amount of Strength reduced.",
                                  QVector<QPair<unsigned, unsigned>> {{10, 10}})}};
    add_barrage(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_ranged_weapon_specialization(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_trueshot_aura(tier7);
    add_talents(tier7);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Marksmanship::add_efficiency(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, "Efficiency", "1MR", "Assets/spell/Spell_frost_wizardmark.png", 5,
                                 "Reduces the Mana cost of your Shots and Stings by %1%", QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                 QVector<SpellRankGroup*> {
                                     spells->get_spell_rank_group_by_name("Aimed Shot"),
                                     spells->get_spell_rank_group_by_name("Multi-Shot"),
                                 });

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_improved_hunters_mark(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, "Improved Hunter's Mark", "2ML", "Assets/ability/Ability_hunter_snipershot.png", 5,
                                 "Increases the Ranged Attack Power bonus of your Hunter's Mark spell by %1%.",
                                 QVector<QPair<unsigned, unsigned>> {{3, 3}},
                                 QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name("Hunter's Mark")});

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_lethal_shots(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, "Lethal Shots", "2MR", "Assets/ability/Ability_searingarrow.png", 5,
                                         "Increases your critical strike chance with ranged weapons by %1%.",
                                         QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::RangedCrit, 100}});

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_aimed_shot(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, "Aimed Shot", "3LL", "Assets/items/Inv_spear_07.png", 1,
                                 "An aimed shot that increases ranged damage by 600.", QVector<QPair<unsigned, unsigned>> {},
                                 QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name("Aimed Shot")});

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_mortal_shots(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, "Mortal Shots", "4MR", "Assets/ability/Ability_piercedamage.png", 5,
                                 "Increases your ranged weapon critical strike damage bonus by %1%.", QVector<QPair<unsigned, unsigned>> {{6, 6}},
                                 QVector<SpellRankGroup*> {
                                     spells->get_spell_rank_group_by_name("Aimed Shot"),
                                     spells->get_spell_rank_group_by_name("Multi-Shot"),
                                 });

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_barrage(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, "Barrage", "5ML", "Assets/ability/Ability_upgrademoonglaive.png", 3,
                                 "Increases the damage done by your Multi-Shot and Volley spells by %1%.",
                                 QVector<QPair<unsigned, unsigned>> {{5, 5}},
                                 QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name("Multi-Shot")});

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_ranged_weapon_specialization(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, "Ranged Weapon Specialization", "6MR", "Assets/items/Inv_weapon_rifle_06.png", 5,
                                         "Increases the damage you deal with ranged weapons by %1%.", QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::RangedDmgMod, 1}});

    add_talent_to_tier(talent_tier, talent);
}

void Marksmanship::add_trueshot_aura(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, "Trueshot Aura", "7ML", "Assets/ability/Ability_trueshot.png", 1,
                                         "Increases the attack power of party members within 45 yards by 100. Lasts 30 min.",
                                         QVector<QPair<unsigned, unsigned>>(), QVector<QPair<TalentStat, unsigned>> {{TalentStat::AttackPower, 100}});

    add_talent_to_tier(talent_tier, talent);
}
