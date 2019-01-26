#include "Fury.h"

#include "BattleShoutBuff.h"
#include "BerserkerRage.h"
#include "Bloodthirst.h"
#include "Cruelty.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Execute.h"
#include "Flurry.h"
#include "GenericTalent.h"
#include "OffhandAttackWarrior.h"
#include "Slam.h"
#include "Talent.h"
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Fury::Fury(Warrior* pchar) :
    TalentTree("Fury", "Assets/warrior/warrior_fury.jpg"),
    warrior(pchar),
    spells(dynamic_cast<WarriorSpells*>(pchar->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1ML", get_booming_voice()},
                                  {"1MR", new Cruelty(pchar, this)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new GenericTalent(pchar, this, "Improved Demoralizing Shout", "2ML", base_url + "ability/Ability_warrior_warcry.png", 5, "Increases the melee attack power reduction of your Demoralizing Shout by %1%.", QVector<QPair<int, int>>{{8, 8}})},
                                  {"2MR", get_unbridled_wrath()}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new GenericTalent(pchar, this, "Improved Cleave", "3LL", base_url + "ability/Ability_warrior_cleave.png", 3, "Increases the bonus damage done by your Cleave ability by %1%.", QVector<QPair<int, int>>{{40, 40}})},
                                  {"3ML", new GenericTalent(pchar, this, "Piercing Howl", "3ML", base_url + "spell/Spell_shadow_deathscream.png", 1, "Causes all enemies near the warrior to be dazed, reducing movement speed by 50% for 6 sec.", QVector<QPair<int, int>>())},
                                  {"3MR", new GenericTalent(pchar, this, "Blood Craze", "3MR", base_url + "spell/Spell_shadow_summonimp.png", 3, "Regenerates %1% of your total Health over 6 sec after being the victim of a critical strike.", QVector<QPair<int, int>>{{1, 1}})},
                                  {"3RR", get_improved_battle_shout()}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", get_dual_wield_specialization()},
                                  {"4ML", get_improved_execute()},
                                  {"4MR", new GenericTalent(pchar, this, "Enrage", "4MR", base_url + "spell/Spell_shadow_unholyfrenzy.png", 5, "Gives you a %1% melee damage bonus for 12 sec up to a maximum of 12 swings after being the victim of a critical strike.", QVector<QPair<int, int>>{{5, 5}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", get_improved_slam()},
                                  {"5ML", get_death_wish()},
                                  {"5RR", new GenericTalent(pchar, this, "Improved Intercept", "5RR", base_url + "ability/Ability_rogue_sprint.png", 2, "Reduces the cooldown of your Intercept ability by %1 sec.", QVector<QPair<int, int>>{{5, 5}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", get_improved_berserker_rage()},
                                  {"6MR", get_flurry_talent()}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", get_bloodthirst()}};
    add_talents(tier7);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);
}

Talent* Fury::get_booming_voice() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Increases the area of effect and duration of your Battle Shout and Demoralizing Shout by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{10, 10}});
    Talent* talent = new Talent(warrior, this, "Booming Voice", "1ML",
                                "Assets/spell/Spell_nature_purge.png", 5, rank_descriptions,
                                {},
                                QVector<Buff*>{warrior->get_battle_shout_buff()});

    return talent;
}

Talent* Fury::get_unbridled_wrath() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Gives you a %1% chance to generate an additional Rage point when you deal melee damage with a weapon.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{8, 8}});
    Talent* talent = new Talent(warrior, this, "Unbridled Wrath", "2MR",
                                "Assets/spell/Spell_nature_stoneclawtotem.png", 5, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{warrior->get_unbridled_wrath()});

    return talent;
}

Talent* Fury::get_improved_battle_shout() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Increases the melee attack power bonus of your Battle Shout by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Improved Battle Shout", "3RR",
                                "Assets/ability/Ability_warrior_battleshout.png", 5, rank_descriptions,
                                {},
                                QVector<Buff*>{warrior->get_battle_shout_buff()});

    return talent;
}

Talent* Fury::get_dual_wield_specialization() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Increases the damage done by your offhand weapon by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Dual Wield Specialization", "4LL",
                                "Assets/ability/Ability_dualwield.png", 5, rank_descriptions,
                                QVector<Spell*>{spells->get_oh_attack_warrior()});

    return talent;
}

Talent* Fury::get_improved_execute() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Reduces the rage cost of your Execute ability by %1.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 2, QVector<QPair<int, int>>{{2, 3}});
    Talent* talent = new Talent(warrior, this, "Improved Execute", "4ML",
                                "Assets/items/Inv_sword_48.png", 2, rank_descriptions,
                                QVector<Spell*>{spells->get_execute()});

    return talent;
}

Talent* Fury::get_improved_slam() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Decreases the casting time of your Slam ability by 0.%1 sec.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{1, 1}});
    Talent* talent = new Talent(warrior, this, "Improved Slam", "5LL",
                                "Assets/ability/Ability_warrior_decisivestrike.png", 5, rank_descriptions,
                                QVector<Spell*>{spells->get_slam()});

    return talent;
}

Talent* Fury::get_death_wish() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "When activated, increases your physical damage by 20% and makes you immune to Fear effects, but lowers your armor and all resistances by 20%. Lasts 30 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(warrior, this, "Death Wish", "5ML",
                                "Assets/spell/Spell_shadow_deathpact.png", 1, rank_descriptions,
                                QVector<Spell*>{spells->get_death_wish()},
                                QVector<Buff*>{warrior->get_death_wish_buff()});

    return talent;
}

Talent* Fury::get_improved_berserker_rage() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "The Berserker Rage ability will generate %1 rage when used.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 2, QVector<QPair<int, int>>{{5, 5}});
    Talent* talent = new Talent(warrior, this, "Improved Berserker Rage", "6LL",
                                "Assets/spell/Spell_nature_ancestralguardian.png", 2, rank_descriptions,
                                QVector<Spell*>{spells->get_berserker_rage()});

    return talent;
}

Talent* Fury::get_flurry_talent() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Increases your attack speed by %1% for your next 3 swings after dealing a melee critical strike.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{10, 5}});
    Talent* talent = new Talent(warrior, this, "Flurry", "6MR",
                                "Assets/ability/Ability_ghoulfrenzy.png", 5, rank_descriptions,
                                {},
                                QVector<Buff*>{warrior->get_flurry()});

    return talent;
}

Talent* Fury::get_bloodthirst() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Instantly attack the target causing damage equal to 45% of your attack power. In addition, the next 5 successful melee attacks will restore 10 health. This effect lasts 8 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(warrior, this, "Bloodthirst", "7ML",
                                "Assets/spell/Spell_nature_bloodlust.png", 1, rank_descriptions,
                                QVector<Spell*>{spells->get_bloodthirst()});

    return talent;
}
