#include "Survival.h"

#include "Hunter.h"
#include "HunterSpells.h"
#include "TalentStatIncrease.h"

Survival::Survival(Hunter* pchar) :
    TalentTree("Survival", "Assets/hunter/hunter_survival.jpg"),
    hunter(pchar),
    spells(dynamic_cast<HunterSpells*>(hunter->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1LL", get_monster_slaying()},
                                  {"1ML", get_humanoid_slaying()},
                                  {"1MR", new Talent(pchar, this, "Deflection", "1MR", "Assets/ability/Ability_parry.png", 5, "Increases your Parry chance by %1%.", QVector<QPair<unsigned, unsigned>>{{1, 1}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(pchar, this, "Entrapment", "2LL", "Assets/spell/Spell_nature_stranglevines.png", 5, "Gives your Immolation Trap, Frost Trap, and Explosive Trap a %1% chance to entrap the target, preventing them from moving for 5 sec.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"2ML", new Talent(pchar, this, "Savage Strikes", "2ML", "Assets/ability/Ability_racial_bloodrage.png", 2, "Increases the critical strike chance of Raptor Strike and Mongoose Bite by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})},
                                  {"2MR", new Talent(pchar, this, "Improved Wing Clip", "2MR", "Assets/ability/Ability_rogue_trip.png", 5, "Gives your Wing Clip ability a %1% chance to immobilize the target for 5 sec.", QVector<QPair<unsigned, unsigned>>{{4, 4}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(pchar, this, "Clever Traps", "3LL", "Assets/spell/Spell_nature_timestop.png", 2, "Increases the duration of Freezing and Frost trap effects by %1% and the damage of Immolation and Explosive trap effects by %2%.", QVector<QPair<unsigned, unsigned>>{{15, 15}, {15, 15}})},
                                  {"3ML", new Talent(pchar, this, "Survivalist", "3ML", "Assets/spell/Spell_shadow_twilight.png", 5, "Increases total health by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"3MR", new Talent(pchar, this, "Deterrence", "3MR", "Assets/ability/Ability_whirlwind.png", 1, "When activated, increases your Dodge and Parry chance by 25% for 10 sec.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(pchar, this, "Trap Mastery", "4LL", "Assets/ability/Ability_ensnare.png", 2, "Decreases the chance enemies will resist trap effects by %1%.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"4ML", get_surefooted()},
                                  {"4RR", new Talent(pchar, this, "Improved Feign Death", "4RR", "Assets/ability/Ability_rogue_feigndeath.png", 2, "Reduces the chance your Feign Death ability will be resisted by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", get_killer_instinct()},
                                  {"5MR", new Talent(pchar, this, "Counterattack", "5MR", "Assets/ability/Ability_warrior_challange.png", 1, "A strike that becomes active after parrying an opponent's attack. This attack deals 40 damage and immobilizes the target for 5 sec. Counterattack cannot be blocked, dodged, or parried.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", get_lightning_reflexes()}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(pchar, this, "Wyvern Sting", "7ML", "Assets/items/Inv_spear_02.png", 1, "A stinging shot that puts the target to sleep for 12 sec. Any damage will cancel the effect. When the target wakes up, the Sting causes (100.2% of Spell Power) Nature damage over 12 sec. Only usable out of combat. Only one Sting per Hunter can be active on the target at a time.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* Survival::get_monster_slaying() {
    return new TalentStatIncrease(hunter, this, "Monster Slaying", "1LL", "Assets/items/Inv_misc_head_dragon_black.png",
                                  3, "Increases all damage caused against Beasts, Giants and Dragonkin targets by %1% and increases critical damage caused against Beasts, Giants and Dragonkin targets by an additional %2%.",
                                  QVector<QPair<unsigned, unsigned>>{{1, 1}, {1, 1}},
                                  QVector<QPair<TalentStat, unsigned>>{
                                      {TalentStat::DmgModAgainstBeast, 1},
                                      {TalentStat::CritDmgModAgainstBeast, 1},
                                      {TalentStat::DmgModAgainstGiant, 1},
                                      {TalentStat::CritDmgModAgainstGiant, 1},
                                      {TalentStat::DmgModAgainstDragonkin, 1},
                                      {TalentStat::CritDmgModAgainstDragonkin, 1},
                                  });
}

Talent* Survival::get_humanoid_slaying() {
    return new TalentStatIncrease(hunter, this, "Humanoid Slaying", "1ML", "Assets/spell/Spell_holy_prayerofhealing.png",
                                  3, "Increases all damage caused against Humanoid targets by %1% and increases critical damage caused against Humanoid targets by an additional %2%.",
                                  QVector<QPair<unsigned, unsigned>>{{1, 1}, {1, 1}},
                                  QVector<QPair<TalentStat, unsigned>>{
                                      {TalentStat::DmgModAgainstHumanoid, 1},
                                      {TalentStat::CritDmgModAgainstHumanoid, 1},
                                  });
}

Talent* Survival::get_surefooted() {
    return new TalentStatIncrease(hunter, this, "Surefooted", "4ML", "Assets/ability/Ability_kick.png",
                                  3, "Increases hit chance by %1% and increases the chance movement impairing effects will be resisted by an additional %2%.",
                                  QVector<QPair<unsigned, unsigned>>{{1, 1}, {5, 5}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::MeleeHit, 100}, {TalentStat::RangedHit, 100}});
}

Talent* Survival::get_killer_instinct() {
    return new TalentStatIncrease(hunter, this, "Killer Instinct", "5ML", "Assets/spell/Spell_holy_blessingofstamina.png",
                                  3, "Increases your critical strike chance with all attacks by %1%.",
                                  QVector<QPair<unsigned, unsigned>>{{1, 1}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::MeleeCrit, 100}, {TalentStat::RangedCrit, 100}});
}

Talent* Survival::get_lightning_reflexes() {
    return new TalentStatIncrease(hunter, this, "Lightning Reflexes", "6MR", "Assets/spell/Spell_nature_invisibility.png",
                                  5, "Increases your Agility by %1%.", QVector<QPair<unsigned, unsigned>>{{3, 3}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::AgilityMod, 3}});
}
