#include "BeastMastery.h"

#include "AspectOfTheHawk.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "ImprovedAspectOfTheHawkProc.h"
#include "TalentStatIncrease.h"

BeastMastery::BeastMastery(Hunter* hunter) :
    TalentTree("Beast Mastery", "Assets/hunter/hunter_beastmastery.jpg"),
    hunter(hunter),
    spells(dynamic_cast<HunterSpells*>(hunter->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1ML", get_improved_aspect_of_the_hawk()},
                                  {"1MR", new Talent(hunter, this, "Endurance Training", "1MR", "Assets/spell/Spell_nature_reincarnation.png", 5, "Increases the Health of your pets by %1%.", QVector<QPair<int, int>>{{3, 3}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(hunter, this, "Improved Eyes of the Beast", "2LL", "Assets/ability/Ability_eyeoftheowl", 2, "Increases the duration of your Eyes of the Beast by %1 sec.", QVector<QPair<int, int>>{{30, 30}})},
                                  {"2ML", new Talent(hunter, this, "Improved Aspect of the Monkey", "2ML", "Assets/ability/Ability_hunter_aspectofthemonkey.png", 5, "Increases the Dodge bonus of your Aspect of the Monkey by %1%.", QVector<QPair<int, int>>{{1, 1}})},
                                  {"2MR", new Talent(hunter, this, "Thick Hide", "2MR", "Assets/items/Inv_misc_pelt_bear_03.png", 3, "Increases the Armor rating of your pets by %1%.", QVector<QPair<int, int>>{{10, 10}})},
                                  {"2RR", new Talent(hunter, this, "Improved Revive Pet", "2RR", "Assets/ability/Ability_hunter_beastsoothe.png", 2, "Revive Pet's casting time is reduced by %1 sec, mana cost is reduced by %2%, and increases the health your pet returns with by an additional %3%", QVector<QPair<int, int>>{{3, 3}, {20, 20}, {15, 15}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(hunter, this, "Pathfinding", "3LL", "Assets/ability/Ability_mount_jungletiger.png", 2, "Increases the speed bonus of your Aspect of the Cheetah and Aspect of the Pack by %1%.", QVector<QPair<int, int>>{{3, 3}})},
                                  {"3ML", new Talent(hunter, this, "Bestial Swiftness", "3ML", "Assets/ability/Ability_druid_dash.png", 1, "Increases the outdoor movement speed of your pets by 30%.", QVector<QPair<int, int>>())},
                                  {"3MR", get_unleashed_fury()}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent(hunter, this, "Improved Mend Pet", "4ML", "Assets/ability/Ability_hunter_mendpet.png", 2, "Gives the Mend Pet spell a %1% chance of cleansing 1 Curse, Disease, Magic or Poison effect from the pet each tick.", QVector<QPair<int, int>>{{15, 35}})},
                                  {"4MR", new Talent(hunter, this, "Ferocity", "4MR", "Assets/items/Inv_misc_monsterclaw_04.png", 5, "Increases the critical strike chance of your pets by %1%.", QVector<QPair<int, int>>{{3, 3}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(hunter, this, "Spirit Bond", "5LL", "Assets/ability/Ability_druid_demoralizingroar.png", 2, "While your pet is active, you and your pet will regenerate %1% of total health every 10 sec.", QVector<QPair<int, int>>{{1, 1}})},
                                  {"5ML", new Talent(hunter, this, "Intimidation", "5ML", "Assets/ability/Ability_devour.png", 1, "Command your pet to intimidate the target on the next successful melee attack, causing a high amount of threat and stunning the target for 3 sec.", QVector<QPair<int, int>>())},
                                  {"5RR", new Talent(hunter, this, "Bestial Discipline", "5RR", "Assets/items/Spell_nature_abolishmagic.png", 2, "Increases the Focus regeneration of your pets by %1%.", QVector<QPair<int, int>>{{10, 10}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent(hunter, this, "Frenzy", "6MR", "Assets/items/Inv_misc_monsterclaw_03.png", 5, "Gives your pet a %1% chance to gain a 30% attack speed increase for 8 sec after dealing a critical strike.", QVector<QPair<int, int>>{{20, 20}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(hunter, this, "Bestial Wrath", "7ML", "Assets/ability/Ability_druid_ferociousbite.png", 1, "Send your pet into a rage causing 50% additional damage for 18 sec. While enraged, the beast does not feel pity or remorse or fear and it cannot be stopped unless killed.", QVector<QPair<int, int>>())}};
    add_talents(tier7);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* BeastMastery::get_improved_aspect_of_the_hawk() {
    return get_new_talent(hunter, "Improved Aspect of the Hawk", "1ML", "Assets/spell/Spell_nature_ravenform.png",
                          5, "While Aspect of the Hawk is active, all normal ranged attacks have a %1% chance of increasing ranged attack speed by 30% for 12 sec.",
                          QVector<QPair<int, int>>{{1, 1}},
                          {},
                          {},
                          QVector<Proc*>{spells->get_aspect_of_the_hawk()->get_improved_aspect_of_the_hawk_proc()});
}

Talent *BeastMastery::get_unleashed_fury() {
    return new TalentStatIncrease(hunter, this, "Unleashed Fury", "3MR", "Assets/ability/Ability_bullrush.png",
                                  5, "Increases the damage done by your pets by %1%.", QVector<QPair<int, int>>{{4, 4}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::PetDmgMod, 4}});
}
