
#include "Fury.h"
#include "Talent.h"
#include "Cruelty.h"
#include <QDebug>

Fury::Fury(Character *pchar, QObject* parent) :
    TalentTree("Fury", parent)
{
    QString base_url = "Assets/warrior/fury/";

    QMap<QString, Talent*> tier1 {{"1ML", new Talent(pchar, "Booming Voice", "1ML", base_url + "tier1/Spell_nature_purge.png", 5)},
                                  {"1MR", new Cruelty(pchar)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent(pchar, "Improved Demoralizing Shout", "2ML", base_url + "tier2/Ability_warrior_warcry.png", 5)},
                                  {"2MR", new Talent(pchar, "Unbridled Wrath", "2MR", base_url + "tier2/Spell_nature_stoneclawtotem.png", 5)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(pchar, "Improved Cleave", "3LL", base_url + "tier3/Ability_warrior_cleave.png", 3)},
                                  {"3ML", new Talent(pchar, "Piercing Howl", "3ML", base_url + "tier3/Spell_shadow_deathscream.png", 1)},
                                  {"3MR", new Talent(pchar, "Blood Craze", "3MR", base_url + "tier3/Spell_shadow_summonimp.png", 3)},
                                  {"3RR", new Talent(pchar, "Improved Battle Shout", "3RR", base_url + "tier3/Ability_warrior_battleshout.png", 5)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(pchar, "Dual Wield Specialization", "4LL", base_url + "tier4/Ability_dualwield.png", 5)},
                                  {"4ML", new Talent(pchar, "Improved Execute", "4ML", base_url + "tier4/Inv_sword_48.png", 2)},
                                  {"4MR", new Talent(pchar, "Enrage", "4MR", base_url + "tier4/Spell_shadow_unholyfrenzy.png", 5)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(pchar, "Improved Slam", "5LL", base_url + "tier5/Ability_warrior_decisivestrike.png", 5)},
                                  {"5ML", new Talent(pchar, "Death Wish", "5ML", base_url + "tier5/Spell_shadow_deathpact.png", 1)},
                                  {"5RR", new Talent(pchar, "Improved Intercept", "5RR", base_url + "tier5/Ability_rogue_sprint.png", 2)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent(pchar, "Improved Berserker Rage", "6LL", base_url + "tier6/Spell_nature_ancestralguardian.png", 2)},
                                  {"6MR", new Talent(pchar, "Flurry", "6MR", base_url + "tier6/Ability_ghoulfrenzy.png", 5)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(pchar, "Bloodthirst", "7ML", base_url + "tier7/Spell_nature_bloodlust.png", 1)}};
    add_talents(tier7);
}

Fury::~Fury()
{}
