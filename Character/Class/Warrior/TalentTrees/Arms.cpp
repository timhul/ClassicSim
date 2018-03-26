
#include "Arms.h"
#include "Talent.h"
#include "ImprovedRend.h"
#include "DeepWounds.h"
#include "Impale.h"
#include <QDebug>

Arms::Arms(Character *pchar, QObject* parent) :
    TalentTree("Arms", parent)
{
    QString base_url = "Assets/warrior/arms/";

    QMap<QString, Talent*> tier1 {{"1LL", new Talent(pchar, "Improved Heroic Strike", "1LL", base_url + "tier1/Ability_rogue_ambush.png", 3)},
                                  {"1ML", new Talent(pchar, "Deflection", "1ML", base_url + "tier1/Ability_parry.png", 5)},
                                  {"1MR", new ImprovedRend(pchar)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(pchar, "Improved Charge", "2LL", base_url + "tier2/Ability_warrior_charge.png", 2)},
                                  {"2ML", new Talent(pchar, "Tactical Mastery", "2ML", base_url + "tier2/Spell_nature_enchantarmor.png", 5)},
                                  {"2RR", new Talent(pchar, "Improved Thunder Clap", "2RR", base_url + "tier2/Spell_nature_thunderclap.png", 3)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(pchar, "Improved Overpower", "3LL", base_url + "tier3/Inv_sword_05.png", 2)},
                                  {"3ML", new Talent(pchar, "Anger Management", "3ML", base_url + "tier3/anger_management.png", 1)},
                                  {"3MR", new DeepWounds(pchar)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent(pchar, "Two-Handed Weapon Specialization", "4ML", base_url + "tier4/Inv_axe_09.png", 5)},
                                  {"4MR", new Impale(pchar)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(pchar, "Axe Specialization", "5LL", base_url + "tier5/Inv_axe_06.png", 5)},
                                  {"5ML", new Talent(pchar, "Sweeping Strikes", "5ML", base_url + "tier5/Ability_rogue_slicedice.png", 1)},
                                  {"5MR", new Talent(pchar, "Mace Specialization", "5MR", base_url + "tier5/Inv_mace_01.png", 5)},
                                  {"5RR", new Talent(pchar, "Sword Specialization", "5RR", base_url + "tier5/Inv_sword_27.png", 5)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6LL", new Talent(pchar, "Polearm Specialization", "6LL", base_url + "tier6/Inv_weapon_halbard_01.png", 5)},
                                  {"6MR", new Talent(pchar, "Improved Hamstring", "6MR", base_url + "tier6/Ability_shockwave.png", 3)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(pchar, "Mortal Strike", "7ML", base_url + "tier7/Ability_warrior_savageblow.png", 1)}};
    add_talents(tier7);

    talents["1MR"]->set_bottom_child(talents["3MR"]);
    talents["3MR"]->set_parent(talents["1MR"]);

    talents["3MR"]->set_bottom_child(talents["4MR"]);
    talents["4MR"]->set_parent(talents["3MR"]);
}

Arms::~Arms()
{}
