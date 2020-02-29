#include "Affliction.h"

#include "Talent.h"
#include "TalentStatIncrease.h"
#include "Warlock.h"
#include "WarlockSpells.h"

Affliction::Affliction(Warlock* warlock) :
    TalentTree("Affliction", "Assets/warlock/warlock_curses.jpg"), warlock(warlock), spells(static_cast<WarlockSpells*>(warlock->get_spells())) {
    talent_names_to_locations = {
        {"Suppression", "1ML"},
        {"Improved Corruption", "1MR"},
        {"Improved Curse of Weakness", "2LL"},
        {"Improved Drain Soul", "2ML"},
        {"Improved Life Tap", "2MR"},
        {"Improved Drain Life", "2RR"},
        {"Improved Curse of Agony", "3LL"},
        {"Fel Concentration", "3ML"},
        {"Amplify Curse", "3MR"},
        {"Grim Reach", "4LL"},
        {"Nightfall", "4ML"},
        {"Improved Drain Mana", "4RR"},
        {"Siphon Life", "5ML"},
        {"Curse of Exhaustion", "5MR"},
        {"Improved Curse of Exhaustion", "5RR"},
        {"Shadow Mastery", "6ML"},
        {"Dark Pact", "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(warlock, this, "Suppression", "1ML", "Assets/spell/Spell_shadow_unsummonbuilding.png", 5,
                           "Reduces the chance for enemies to resist your Affliction spells by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}})},
        {"1MR", new Talent(warlock, this, "Improved Corruption", "1MR", "Assets/spell/Spell_shadow_abominationexplosion.png", 5,
                           "Reduces the casting time of your Corruption spell by %1 sec.", QVector<QPair<double, double>> {{0.4, 0.4}})},
    };
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2LL", new Talent(warlock, this, "Improved Curse of Weakness", "2LL", "Assets/spell/Spell_shadow_curseofmannoroth.png", 3,
                                  "Increases the effect of your Curse of Weakness by %1%.", QVector<QPair<unsigned, unsigned>> {{6, 6}})},
               {"2ML", new Talent(warlock, this, "Improved Drain Soul", "2ML", "Assets/spell/Spell_shadow_haunting.png", 2,
                                  "Gives you a %1% chance to get a 100% increase to your Mana regeneration for 10 sec if the target is killed by you "
                                  "while you drain its soul.  In addition your Mana may continue to regenerate while casting at 50% of normal.",
                                  QVector<QPair<unsigned, unsigned>> {{50, 50}})},
               {"2MR",
                new Talent(warlock, this, "Improved Life Tap", "2MR", "Assets/spell/Spell_shadow_burningspirit.png", 2,
                           "Increases the amount of Mana awarded by your Life Tap spell by %1%.", QVector<QPair<unsigned, unsigned>> {{10, 10}})},
               {"2RR", new Talent(warlock, this, "Improved Drain Life", "2RR", "Assets/spell/Spell_shadow_lifedrain02.png", 5,
                                  "Increases the Health drained by your Drain Life spell by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(warlock, this, "Improved Curse of Agony", "3LL", "Assets/spell/Spell_shadow_curseofsargeras.png", 3,
                           "Increases the damage done by your Curse of Agony by %1%.", QVector<QPair<unsigned, unsigned>> {{2, 2}})},
        {"3ML",
         new Talent(warlock, this, "Fel Concentration", "3ML", "Assets/spell/Spell_shadow_fingerofdeath.png", 5,
                    "Gives you a %1% chance to avoid interruption caused by damage while channeling the Drain Life, Drain Mana, or Drain Soul spell.",
                    QVector<QPair<unsigned, unsigned>> {{14, 14}})},
        {"3MR",
         new Talent(
             warlock, this, "Amplify Curse", "3MR", "Assets/spell/Spell_shadow_contagion.png", 1,
             "Increases the effect of your next Curse of Weakness or Curse of Agony by 50%, or your next Curse of Exhaustion by 20%.  Lasts 30 sec.",
             QVector<QPair<unsigned, unsigned>> {})},
    };
    add_talents(tier3);

    QMap<QString, Talent*>
        tier4 {{"4LL", new Talent(warlock, this, "Grim Reach", "4LL", "Assets/spell/Spell_shadow_callofbone.png", 2,
                                  "Increases the range of your Affliction spells by %1%.", QVector<QPair<unsigned, unsigned>> {{10, 10}})},
               {"4ML", new Talent(warlock, this, "Nightfall", "4ML", "Assets/spell/Spell_shadow_twilight.png", 2,
                                  "Gives your Corruption and Drain Life spells a %1% chance to cause you to enter a Shadow Trance state after "
                                  "damaging the opponent.  The Shadow Trance state reduces the casting time of your next Shadow Bolt spell by 100%.",
                                  QVector<QPair<unsigned, unsigned>> {{2, 2}})},
               {"4RR", new Talent(warlock, this, "Improved Drain Mana", "4RR", "Assets/spell/Spell_shadow_siphonmana.png", 2,
                                  "Causes %1% of the Mana drained by your Drain Mana spell to damage the opponent.",
                                  QVector<QPair<unsigned, unsigned>> {{15, 15}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {
        {"5ML", new Talent(warlock, this, "Siphon Life", "5ML", "Assets/spell/Spell_shadow_requiem.png", 1,
                           "Transfers 15 health from the target to the caster every 3 sec.  Lasts 30 sec.", QVector<QPair<unsigned, unsigned>> {})},
        {"5MR", new Talent(warlock, this, "Curse of Exhaustion", "5MR", "Assets/spell/Spell_shadow_grimward.png", 1,
                           "Reduces the target's movement speed by 10% for 12 sec.  Only one Curse per Warlock can be active on any one target.",
                           QVector<QPair<unsigned, unsigned>> {})},

        {"5RR", new Talent(warlock, this, "Improved Curse of Exhaustion", "5RR", "Assets/spell/Spell_shadow_grimward.png", 4,
                           "Increases the speed reduction of your Curse of Exhaustion by %1%.", QVector<QPair<unsigned, unsigned>> {{5, 5}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_shadow_mastery(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(warlock, this, "Dark Pact", "7ML", "Assets/spell/Spell_shadow_darkritual.png", 1,
                                                     "Drains 150 of your pet's Mana, returning 100% to you.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["5MR"]->talent->set_right_child(talents["5RR"]->talent);
    talents["5RR"]->talent->set_parent(talents["5MR"]->talent);
}

void Affliction::add_shadow_mastery(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(warlock, this, "Shadow Mastery", "6ML", "Assets/spell/Spell_shadow_shadetruesight.png", 5,
                                         "Increases the damage dealt or life drained by your Shadow spells by %1%.",
                                         QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {
                                             {TalentStat::ShadowDmgMod, 2},
                                         });

    add_talent_to_tier(talent_tier, talent);
}
