#include "FeralCombat.h"

#include "Druid.h"
#include "DruidSpells.h"
#include "Talent.h"

FeralCombat::FeralCombat(Druid* druid) :
    TalentTree("Feral Combat", "Assets/druid/druid_feral.jpg"),
    druid(druid),
    spells(dynamic_cast<DruidSpells*>(druid->get_spells()))
{
    talent_names_to_locations = {
        {"Ferocity", "1ML"},
        {"Feral Aggression", "1MR"},
        {"Feral Instinct", "2LL"},
        {"Brutal Impact", "2ML"},
        {"Thick Hide", "2MR"},
        {"Feline Swiftness", "3LL"},
        {"Feral Charge", "3ML"},
        {"Sharpened Claws", "3MR"},
        {"Improved Shred", "4LL"},
        {"Predatory Strikes", "4ML"},
        {"Blood Frenzy", "4MR"},
        {"Primal Fury", "4RR"},
        {"Savage Fury", "5LL"},
        {"Faerie Fire (Feral)", "5MR"},
        {"Heart of the Wild", "6ML"},
        {"Leader of the Pack", "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(druid, this, "Ferocity", "1ML", "Assets/ability/Ability_hunter_pet_hyena.png", 5, "Reduces the cost of your Maul, Swipe, Claw, and Rake abilities by %1 Rage or Energy.", QVector<QPair<unsigned, unsigned>>{{1, 1}})},
    };
    add_feral_aggression(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2LL", new Talent(druid, this, "Feral Instinct", "2LL", "Assets/ability/Ability_ambush.png", 5, "Increases threat caused in Bear and Dire Bear Form by %1% and reduces the chance enemies have to detect you while Prowling.", QVector<QPair<unsigned, unsigned>>{{3, 3}})},
        {"2ML", new Talent(druid, this, "Brutal Impact", "2ML", "Assets/ability/Ability_druid_bash.png", 2, "Increases the stun duration of your Bash and Pounce abilities by %1 sec.", QVector<QPair<double, double>>{{0.5, 0.5}})},
        {"2MR", new Talent(druid, this, "Thick Hide", "2MR", "Assets/items/Inv_misc_pelt_bear_03.png", 5, "Increases your Armor contribution from items by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
    };
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(druid, this, "Feline Swiftness", "3LL", "Assets/spell/Spell_nature_spiritwolf.png", 2, "Increases your movement speed by %1% while outdoors in Cat Form and increases your chance to dodge while in Cat Form by %2%.", QVector<QPair<unsigned, unsigned>>{{15, 15}, {2, 2}})},
        {"3ML", new Talent(druid, this, "Feral Charge", "3ML", "Assets/ability/Ability_hunter_pet_bear.png", 1, "Causes you to charge an enemy, immobilizing and interrupting any spell being cast for 4 sec.", QVector<QPair<unsigned, unsigned>>())},
    };
    add_sharpened_claws(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4RR", new Talent(druid, this, "Primal Fury", "4RR", "Assets/ability/Ability_racial_cannibalize.png", 2, "Gives you a %1% chance to gain an additional 5 Rage anytime you get a critical strike while in Bear and Dire Bear Form.", QVector<QPair<unsigned, unsigned>>{{50, 50}})},
    };
    add_improved_shred(tier4);
    add_predatory_strikes(tier4);
    add_blood_frenzy(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {
        {"5LL", new Talent(druid, this, "Savage Fury", "5LL", "Assets/ability/Ability_druid_ravage.png", 2, "Increases the damage caused by your Claw, Rake, Maul and Swipe abilities by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
        {"5MR", new Talent(druid, this, "Faerie Fire (Feral)", "5MR", "Assets/spell/Spell_nature_faeriefire.png", 1, "Decrease the armor of the target by 175 for 40 sec. While affected, the target cannot stealth or turn invisible.", QVector<QPair<unsigned, unsigned>>())},
    };
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_heart_of_the_wild(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_leader_of_the_pack(tier7);
    add_talents(tier7);

    talents["3MR"]->talent->set_right_child(talents["4RR"]->talent);
    talents["3MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["3MR"]->talent);
    talents["4RR"]->talent->set_parent(talents["3MR"]->talent);

    talents["4ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["4ML"]->talent);
}

void FeralCombat::add_feral_aggression(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Feral Aggression", "1MR", "Assets/ability/Ability_druid_demoralizingroar2.png", 5,
                                    "Increases the Attack Power reduction of your Demoralizing Roar by %1% and the damage caused by your Ferocious Bite by %2%.",
                                    QVector<QPair<unsigned, unsigned>>{{8, 8}, {3, 3}},
                                    QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Ferocious Bite")});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_sharpened_claws(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Sharpened Claws", "3MR", "Assets/items/Inv_misc_monsterclaw_04.png", 3,
                                    "Increases your critical strike chance while in Bear, Dire Bear or Cat Form by %1%.",
                                    QVector<QPair<unsigned, unsigned>>{{2, 2}}, {},
                                    QVector<Buff*>{spells->get_cat_form_buff()});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_improved_shred(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Improved Shred", "4LL", "Assets/spell/Spell_shadow_vampiricaura.png", 2,
                                    "Reduces the Energy cost of your Shred ability by %1.",
                                    QVector<QPair<unsigned, unsigned>>{{6, 6}},
                                    QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Shred")});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_predatory_strikes(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Predatory Strikes", "4ML", "Assets/ability/Ability_hunter_pet_cat.png", 3,
                                    "Increases your melee attack power in Cat, Bear and Dire Bear Forms by %1% of your level.",
                                    QVector<QPair<unsigned, unsigned>>{{50, 50}}, {},
                                    QVector<Buff*>{spells->get_cat_form_buff()});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_blood_frenzy(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Blood Frenzy", "4MR", "Assets/ability/Ability_ghoulfrenzy.png", 2,
                                    "Your critical strikes from Cat Form abilities that add combo points have a %1% chance to add an additional combo point.",
                                    QVector<QPair<unsigned, unsigned>>{{50, 50}}, {}, {},
                                    QVector<Proc*>{spells->get_blood_frenzy()});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_heart_of_the_wild(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Heart of the Wild", "6ML", "Assets/spell/Spell_holy_blessingofagility.png", 5,
                                    "Increases your Intellect by %1%. In addition, while in Bear or Dire Bear Form your Stamina is increased by %2% and while in Cat Form your Strength is increased by %3%.",
                                    QVector<QPair<unsigned, unsigned>>{{4, 4}, {4, 4}, {4, 4}}, {},
                                    QVector<Buff*>{spells->get_cat_form_buff()});

    add_talent_to_tier(talent_tier, talent);
}

void FeralCombat::add_leader_of_the_pack(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Leader of the Pack", "7ML", "Assets/spell/Spell_nature_unyeildingstamina.png", 1,
                                    "While in Cat, Bear or Dire Bear Form, the Leader of the Pack increases ranged and melee critical chance of all party members within 45 yards by 3%.",
                                    QVector<QPair<unsigned, unsigned>>(), {},
                                    QVector<Buff*>{spells->get_cat_form_buff()});

    add_talent_to_tier(talent_tier, talent);
}
