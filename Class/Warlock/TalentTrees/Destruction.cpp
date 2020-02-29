#include "Destruction.h"

#include "Talent.h"
#include "TalentStatIncrease.h"
#include "Warlock.h"
#include "WarlockSpells.h"

Destruction::Destruction(Warlock* warlock) :
    TalentTree("Destruction", "Assets/warlock/warlock_destruction.jpg"),
    warlock(warlock),
    spells(static_cast<WarlockSpells*>(warlock->get_spells())) {
    talent_names_to_locations = {
        {"Improved Shadow Bolt", "1ML"},
        {"Cataclysm", "1MR"},
        {"Bane", "2ML"},
        {"Aftermath", "2MR"},
        {"Improved Firebolt", "3LL"},
        {"Improved Lash of Pain", "3ML"},
        {"Devastation", "3MR"},
        {"Shadowburn", "3RR"},
        {"Intensity", "4LL"},
        {"Destructive Reach", "4ML"},
        {"Improved Searing Pain", "4RR"},
        {"Pyroclasm", "5LL"},
        {"Improved Immolate", "5ML"},
        {"Ruin", "5MR"},
        {"Emberstorm", "6MR"},
        {"Conflagrate", "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(warlock, this, "Improved Shadow Bolt", "1ML", "Assets/spell/Spell_shadow_shadowbolt.png", 5,
                           "Your Shadow Bolt critical strikes increase Shadow damage dealt to the target by %1% until 4 non-periodic damage sources "
                           "are applied.  Effect lasts a maximum of 12 sec.",
                           QVector<QPair<unsigned, unsigned>> {{4, 4}})},
        {"1MR", new Talent(warlock, this, "Cataclysm", "1MR", "Assets/spell/Spell_fire_windsofwoe.png", 5,
                           "Reduces the Mana cost of your Destruction spells by %1%.", QVector<QPair<unsigned, unsigned>> {{1, 1}})},
    };
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2ML", new Talent(warlock, this, "Bane", "2ML", "Assets/spell/Spell_shadow_deathpact.png", 5,
                                  "Reduces the casting time of your Shadow Bolt and Immolate spells by %1 sec and your Soul Fire spell by %2 sec.",
                                  QVector<QPair<double, double>> {{0.1, 0.1}, {0.4, 0.4}})},
               {"2MR",
                new Talent(warlock, this, "Aftermath", "2MR", "Assets/spell/Spell_fire_fire.png", 5,
                           "Gives your Destruction spells a %1% chance to daze the target for 5 sec.", QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(warlock, this, "Improved Firebolt", "3LL", "Assets/spell/Spell_fire_firebolt.png", 2,
                                                     "Reduces the casting time of your Imp's Firebolt spell by %1 sec.",
                                                     QVector<QPair<double, double>> {{0.5, 0.5}})},
                                  {"3ML", new Talent(warlock, this, "Improved Lash of Pain", "3ML", "Assets/spell/Spell_shadow_curse.png", 2,
                                                     "Reduces the cooldown of your Succubus' Lash of Pain spell by %1 sec.",
                                                     QVector<QPair<unsigned, unsigned>> {{3, 3}})},
                                  {"3MR", new Talent(warlock, this, "Devastation", "3MR", "Assets/spell/Spell_fire_flameshock.png", 5,
                                                     "Increases the critical strike chance of your Destruction spells by %1%.",
                                                     QVector<QPair<unsigned, unsigned>> {{1, 1}})},
                                  {
                                      "3RR",
                                      new Talent(warlock, this, "Shadowburn", "3RR", "Assets/spell/Spell_shadow_scourgebuild.png", 1,
                                                 "Instantly blasts the target for 91 to 104 Shadow damage.  If the target dies within 5 sec of "
                                                 "Shadowburn, and yields experience or honor, the caster gains a Soul Shard.",
                                                 QVector<QPair<unsigned, unsigned>> {}),
                                  }};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4LL",
         new Talent(warlock, this, "Intensity", "4LL", "Assets/spell/Spell_fire_lavaspawn.png", 2,
                    "Gives you a %1% chance to resist interruption caused by damage while channeling the Rain of Fire, Hellfire or Soul Fire spell.",
                    QVector<QPair<unsigned, unsigned>> {{35, 35}})},
        {"4ML", new Talent(warlock, this, "Destructive Reach", "4ML", "Assets/spell/Spell_shadow_corpseexplode.png", 2,
                           "Increases the range of your Destruction spells by %1%.", QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"4RR", new Talent(warlock, this, "Improved Searing Pain", "4RR", "Assets/spell/Spell_fire_soulburn.png", 5,
                           "Increases the critical strike chance of your Searing Pain spell by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL",
                                   new Talent(warlock, this, "Pyroclasm", "5LL", "Assets/spell/Spell_fire_volcano.png", 2,
                                              "Gives your Rain of Fire, Hellfire, and Soul Fire spells a %1% chance to stun the target for 3 sec.",
                                              QVector<QPair<unsigned, unsigned>> {{13, 13}})},
                                  {"5ML", new Talent(warlock, this, "Improved Immolate", "5ML", "Assets/spell/Spell_fire_immolation.png", 5,
                                                     "Increases the initial damage of your Immolate spell by %1%.",
                                                     QVector<QPair<unsigned, unsigned>> {{5, 5}})},
                                  {"5MR", new Talent(warlock, this, "Ruin", "5MR", "Assets/spell/Spell_shadow_shadowwordpain.png", 1,
                                                     "Increases the critical strike damage bonus of your Destruction spells by 100%.",
                                                     QVector<QPair<unsigned, unsigned>> {})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_emberstorm(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(warlock, this, "Conflagrate", "7ML", "Assets/spell/Spell_fire_fireball.png", 1,
                           "Ignites a target that is already afflicted by Immolate, dealing 249 to 316 Fire damage and consuming the Immolate spell.",
                           QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["4LL"]->talent->set_bottom_child(talents["5LL"]->talent);
    talents["5LL"]->talent->set_parent(talents["4LL"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Destruction::add_emberstorm(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(warlock, this, "Emberstorm", "6MR", "Assets/spell/Spell_fire_selfdestruct.png", 5,
                                         "Increases the damage done by your Fire spells by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {
                                             {TalentStat::FireDmgMod, 2},
                                         });

    add_talent_to_tier(talent_tier, talent);
}
