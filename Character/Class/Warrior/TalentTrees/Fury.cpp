
#include "Fury.h"
#include "Talent.h"
#include "Cruelty.h"
#include "BoomingVoice.h"
#include "ImprovedDemoralizingShout.h"
#include "UnbridledWrath.h"
#include "ImprovedCleave.h"
#include "ImprovedBattleShout.h"
#include "DualWieldSpecialization.h"
#include "ImprovedExecute.h"
#include "ImprovedSlam.h"
#include "DeathWish.h"
#include "ImprovedBerserkerRage.h"
#include "FlurryTalent.h"
#include "BloodthirstTalent.h"
#include "GenericTalent.h"

Fury::Fury(Character *pchar, QObject* parent) :
    TalentTree("Fury", "Assets/warrior/warrior_fury.jpg",  parent)
{
    QString base_url = "Assets/warrior/fury/";

    QMap<QString, Talent*> tier1 {{"1ML", new BoomingVoice(pchar)},
                                  {"1MR", new Cruelty(pchar)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new ImprovedDemoralizingShout(pchar)},
                                  {"2MR", new UnbridledWrath(pchar)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new ImprovedCleave(pchar)},
                                  {"3ML", new GenericTalent(pchar, "Piercing Howl", "3ML", base_url + "tier3/Spell_shadow_deathscream.png", 1, "", "Requires 10 points in Fury talents", "Causes all enemies near the warrior to be dazed, reducing movement speed by 50% for 6 sec.", 0, 0, false)},
                                  {"3MR", new GenericTalent(pchar, "Blood Craze", "3MR", base_url + "tier3/Spell_shadow_summonimp.png", 3, "", "Requires 10 points in Fury talents", "Regenerates %1% of your total Health over 6 sec after being the victim of a critical strike.", 1, 1, true)},
                                  {"3RR", new ImprovedBattleShout(pchar)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new DualWieldSpecialization(pchar)},
                                  {"4ML", new ImprovedExecute(pchar)},
                                  {"4MR", new GenericTalent(pchar, "Enrage", "4MR", base_url + "tier4/Spell_shadow_unholyfrenzy.png", 5, "", "Requires 15 points in Fury talents", "Gives you a %1% melee damage bonus for 12 sec up to a maximum of 12 swings after being the victim of a critical strike.", 5, 5, true)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new ImprovedSlam(pchar)},
                                  {"5ML", new DeathWish(pchar)},
                                  {"5RR", new GenericTalent(pchar, "Improved Intercept", "5RR", base_url + "tier5/Ability_rogue_sprint.png", 2, "", "Requires 20 points in Fury talents", "Reduces the cooldown of your Intercept ability by %1 sec.", 5, 5, true)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new ImprovedBerserkerRage(pchar)},
                                  {"6MR", new FlurryTalent(pchar)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new BloodthirstTalent(pchar)}};
    add_talents(tier7);

    talents["5ML"]->set_bottom_child(talents["7ML"]);
    talents["7ML"]->set_parent(talents["5ML"]);

    talents["4MR"]->set_bottom_child(talents["6MR"]);
    talents["6MR"]->set_parent(talents["4MR"]);
}

Fury::~Fury()
{}
