
#include "Fury.h"
#include "Talent.h"
#include <QDebug>

Fury::Fury(QObject* parent) :
    TalentTree("Fury", parent)
{
    QString base_url = "Assets/warrior/fury/";

    QMap<QString, Talent*> tier1 {{"1ML", new Talent("Booming Voice", base_url + "tier1/Spell_nature_purge.png", 5)},
                                  {"1MR", new Talent("Cruelty", base_url + "tier1/Ability_rogue_eviscerate.png", 5)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent("Improved Demoralizing Shout", base_url + "tier2/Ability_warrior_warcry.png", 5)},
                                  {"2MR", new Talent("Unbridled Wrath", base_url + "tier2/Spell_nature_stoneclawtotem.png", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent("Improved Cleave", base_url + "tier3/Ability_warrior_cleave.png", 3)},
                                  {"3ML", new Talent("Piercing Howl", base_url + "tier3/Spell_shadow_deathscream.png", 1)},
                                  {"3MR", new Talent("Blood Craze", base_url + "tier3/Spell_shadow_summonimp.png", 3)},
                                  {"3RR", new Talent("Improved Battle Shout", base_url + "tier3/Ability_warrior_battleshout.png", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent("Dual Wield Specialization", base_url + "tier4/Ability_dualwield.png", 5)},
                                  {"4ML", new Talent("Improved Execute", base_url + "tier4/Inv_sword_48.png", 2)},
                                  {"4MR", new Talent("Enrage", base_url + "tier4/Spell_shadow_unholyfrenzy.png", 5)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent("Improved Slam", base_url + "tier5/Ability_warrior_decisivestrike.png", 5)},
                                  {"5ML", new Talent("Death Wish", base_url + "tier5/Spell_shadow_deathpact.png", 1)},
                                  {"5RR", new Talent("Improved Intercept", base_url + "tier5/Ability_rogue_sprint.png", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent("Improved Berserker Rage", base_url + "tier6/Spell_nature_ancestralguardian.png", 2)},
                                  {"6MR", new Talent("Flurry", base_url + "tier6/Ability_ghoulfrenzy.png", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent("Bloodthirst", base_url + "tier7/Spell_nature_bloodlust.png", 1)}};
    add_talents(tier7);
}

Fury::~Fury()
{}
