#include "Fury.h"

#include "BloodthirstTalent.h"
#include "BoomingVoice.h"
#include "Cruelty.h"
#include "DeathWishTalent.h"
#include "DualWieldSpecialization.h"
#include "FlurryTalent.h"
#include "GenericTalent.h"
#include "ImprovedBattleShout.h"
#include "ImprovedBerserkerRage.h"
#include "ImprovedCleave.h"
#include "ImprovedDemoralizingShout.h"
#include "ImprovedExecute.h"
#include "ImprovedSlam.h"
#include "Talent.h"
#include "UnbridledWrathTalent.h"

Fury::Fury(Character *pchar) :
    TalentTree("Fury", "Assets/warrior/warrior_fury.jpg")
{
    QString base_url = "Assets/warrior/fury/";

    QMap<QString, Talent*> tier1 {{"1ML", new BoomingVoice(pchar, this)},
                                  {"1MR", new Cruelty(pchar, this)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new ImprovedDemoralizingShout(pchar, this)},
                                  {"2MR", new UnbridledWrathTalent(pchar, this)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new ImprovedCleave(pchar, this)},
                                  {"3ML", new GenericTalent(pchar, this, "Piercing Howl", "3ML", base_url + "tier3/Spell_shadow_deathscream.png", 1, "Causes all enemies near the warrior to be dazed, reducing movement speed by 50% for 6 sec.", QVector<QPair<int, int>>())},
                                  {"3MR", new GenericTalent(pchar, this, "Blood Craze", "3MR", base_url + "tier3/Spell_shadow_summonimp.png", 3, "Regenerates %1% of your total Health over 6 sec after being the victim of a critical strike.", QVector<QPair<int, int>>{{1, 1}})},
                                  {"3RR", new ImprovedBattleShout(pchar, this)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new DualWieldSpecialization(pchar, this)},
                                  {"4ML", new ImprovedExecute(pchar, this)},
                                  {"4MR", new GenericTalent(pchar, this, "Enrage", "4MR", base_url + "tier4/Spell_shadow_unholyfrenzy.png", 5, "Gives you a %1% melee damage bonus for 12 sec up to a maximum of 12 swings after being the victim of a critical strike.", QVector<QPair<int, int>>{{5, 5}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new ImprovedSlam(pchar, this)},
                                  {"5ML", new DeathWishTalent(pchar, this)},
                                  {"5RR", new GenericTalent(pchar, this, "Improved Intercept", "5RR", base_url + "tier5/Ability_rogue_sprint.png", 2, "Reduces the cooldown of your Intercept ability by %1 sec.", QVector<QPair<int, int>>{{5, 5}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new ImprovedBerserkerRage(pchar, this)},
                                  {"6MR", new FlurryTalent(pchar, this)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new BloodthirstTalent(pchar, this)}};
    add_talents(tier7);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);
}

Fury::~Fury() = default;
