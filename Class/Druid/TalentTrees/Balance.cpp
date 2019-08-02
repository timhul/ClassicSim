#include "Balance.h"

#include "Druid.h"
#include "DruidSpells.h"
#include "Talent.h"
#include "TalentStatIncrease.h"

Balance::Balance(Druid* druid) :
    TalentTree("Balance", "Assets/druid/druid_balance.jpg"),
    druid(druid),
    spells(dynamic_cast<DruidSpells*>(druid->get_spells()))
{
    talent_names_to_locations = {
        {"Improved Wrath", "1LL"},
        {"Nature's Grasp", "1ML"},
        {"Improved Nature's Grasp", "1MR"},
        {"Improved Entangling Roots", "2LL"},
        {"Improved Moonfire", "2ML"},
        {"Natural Weapons", "2MR"},
        {"Natural Shapeshifter", "2RR"},
        {"Improved Thorns", "3LL"},
        {"Omen of Clarity", "3MR"},
        {"Nature's Reach", "3RR"},
        {"Vengeance", "4ML"},
        {"Improved Starfire", "4MR"},
        {"Nature's Grace", "5ML"},
        {"Moonglow", "5MR"},
        {"Moonfury", "6ML"},
        {"Moonkin Form", "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(druid, this, "Nature's Grasp", "1ML", "Assets/spell/Spell_nature_natureswrath.png", 1, "While active, any time an enemy strikes the caster they have a 35% chance to become afflicted by Entangling Roots (Rank 1). Only useable outdoors. 1 charge. Lasts 45 sec.", QVector<QPair<unsigned, unsigned>>())},
    };
    add_improved_wrath(tier1);
    add_improved_natures_grasp(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2LL", new Talent(druid, this, "Improved Entangling Roots", "2LL", "Assets/spell/Spell_nature_stranglevines.png", 3, "Gives you a %1% chance to avoid interruption caused by damage while casting Entangling Roots.", QVector<QPair<unsigned, unsigned>>{{40, 30}})},
        {"2RR", new Talent(druid, this, "Natural Shapeshifter", "2RR", "Assets/spell/Spell_nature_wispsplode.png", 3, "Reduces the mana cost of all shapeshifting by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
    };
    add_improved_moonfire(tier2);
    add_natural_weapons(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(druid, this, "Improved Thorns", "3LL", "Assets/spell/Spell_nature_thorns.png", 3, "Increases damage caused by your Thorns spell by %1%.", QVector<QPair<unsigned, unsigned>>{{25, 25}})},
        {"3RR", new Talent(druid, this, "Nature's Reach", "3RR", "Assets/items/Inv_misc_branch_01.png", 2, "Increases the range of your Wrath, Entangling Roots, Faerie Fire, Moonfire, Starfire, and Hurricane spells by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
    };
    add_omen_of_clarity(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {};
    add_vengeance(tier4);
    add_improved_starfire(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {};
    add_natures_grace(tier5);
    add_moonglow(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_moonfury(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(druid, this, "Moonkin Form", "7ML", "Assets/spell/Spell_nature_forceofnature.png", 1, "Transforms the Druid into Moonkin Form.  While in this form the armor contribution from items is increased by 360% and all party members within 30 yards have their spell critical chance increased by 3%. The Moonkin can only cast Balance spells while shapeshifted.\n\nThe act of shapeshifting frees the caster of Polymorph and Movement Impairing effects.", QVector<QPair<unsigned, unsigned>>())},
    };
    add_talents(tier7);

    talents["1ML"]->talent->set_right_child(talents["1MR"]->talent);
    talents["1MR"]->talent->set_parent(talents["1ML"]->talent);

    talents["2ML"]->talent->set_bottom_child(talents["4ML"]->talent);
    talents["4ML"]->talent->set_parent(talents["2ML"]->talent);

    talents["2MR"]->talent->set_bottom_child(talents["3MR"]->talent);
    talents["3MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Balance::add_improved_wrath(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Improved Wrath", "1LL", "Assets/items/Spell_nature_abolishmagic.png", 5,
                                    "Reduces the cast time of your Wrath spell by 0.%1 sec.",
                                    QVector<QPair<unsigned, unsigned>>{{1, 1}},
                                    QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Wrath")});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_natures_grasp(QMap<QString, Talent*>& talent_tier) {
    QString base_str = "Increases the chance for your Nature's Grasp to entangle an enemy by %1%.";
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(15)}, {1, base_str.arg(15)},
                                               {2, base_str.arg(30)},
                                               {3, base_str.arg(45)},
                                               {4, base_str.arg(65)}};
    Talent* talent = new Talent(druid, this, "Improved Nature's Grasp", "1MR", "Assets/spell/Spell_nature_natureswrath.png", 4,
                                rank_descriptions);

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_moonfire(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Improved Moonfire", "2ML", "Assets/spell/Spell_nature_starfall.png", 5,
                                    "Increases the damage and critical strike chance of your Moonfire spell by %1%.",
                                    QVector<QPair<unsigned, unsigned>>{{2, 2}},
                                    QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Moonfire")});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_natural_weapons(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(druid, this, "Natural Weapons", "2MR", "Assets/items/Inv_staff_01.png", 5,
                                         "Increases the damage you deal with physical attacks in all forms by %1%.",
                                         QVector<QPair<unsigned, unsigned>>{{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>>{{TalentStat::PhysicalDmgMod, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_omen_of_clarity(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Omen of Clarity", "3MR", "Assets/items/Inv_misc_orb_01.png", 1,
                                    "Imbues the Druid with natural energy. Each of the Druid's melee attacks has a chance of causing the caster to enter a Clearcasting state. The Clearcasting state reduces the Mana, Rage or Energy cost of your next damage or healing spell or offensive ability by 100%. Lasts 10 min.",
                                    QVector<QPair<unsigned, unsigned>>(), {}, {},
                                    QVector<Proc*>{spells->get_omen_of_clarity()});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_vengeance(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Vengeance", "4ML", "Assets/spell/Spell_nature_purge.png", 5,
                                    "Increases the critical strike damage bonus of your Starfire, Moonfire, and Wrath spells by %1%.",
                                    QVector<QPair<unsigned, unsigned>>{{20, 20}},
                                    QVector<SpellRankGroup*>{
                                        spells->get_spell_rank_group_by_name("Starfire"),
                                        spells->get_spell_rank_group_by_name("Moonfire"),
                                        spells->get_spell_rank_group_by_name("Wrath"),
                                    });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_starfire(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Improved Starfire", "4MR", "Assets/spell/Spell_arcane_starfire.png", 5,
                                    "Reduces the cast time of Starfire by 0.%1 sec and has a %2% chance to stun the target for 3 sec.",
                                    QVector<QPair<unsigned, unsigned>>{{1, 1}, {3, 3}},
                                    QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Starfire")});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_natures_grace(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Nature's Grace", "5ML", "Assets/spell/Spell_nature_naturesblessing.png", 1,
                                    "All spell criticals grace you with a blessing of nature, reducing the casting time of your next spell by 0.5 sec.",
                                    QVector<QPair<unsigned, unsigned>>(), {},
                                    QVector<Buff*>{spells->get_natures_grace()});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_moonglow(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Moonglow", "5MR", "Assets/spell/Spell_nature_sentinal.png", 3,
                                    "Reduces the Mana cost of your Moonfire, Starfire, Wrath, Healing Touch, Regrowth and Rejuvenation spells by %1%.",
                                    QVector<QPair<unsigned, unsigned>>{{3, 3}},
                                    QVector<SpellRankGroup*>{
                                        spells->get_spell_rank_group_by_name("Starfire"),
                                        spells->get_spell_rank_group_by_name("Moonfire"),
                                        spells->get_spell_rank_group_by_name("Wrath"),
                                    });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_moonfury(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, "Moonfury", "6ML", "Assets/spell/Spell_nature_moonglow.png", 5,
                                    "Increases the damage done by your Starfire, Moonfire and Wrath spells by %1%.",
                                    QVector<QPair<unsigned, unsigned>>{{2, 2}},
                                    QVector<SpellRankGroup*>{
                                        spells->get_spell_rank_group_by_name("Starfire"),
                                        spells->get_spell_rank_group_by_name("Moonfire"),
                                        spells->get_spell_rank_group_by_name("Wrath"),
                                    });

    add_talent_to_tier(talent_tier, talent);
}
