#include "Demonology.h"

#include "Talent.h"
#include "TalentStatIncrease.h"
#include "Warlock.h"
#include "WarlockSpells.h"

Demonology::Demonology(Warlock* warlock) :
    TalentTree("Demonology", "Assets/warlock/warlock_summoning.jpg"), warlock(warlock), spells(static_cast<WarlockSpells*>(warlock->get_spells())) {
    talent_names_to_locations = {
        {"Improved Healthstone", "1LL"}, {"Improved Imp", "1ML"},       {"Demonic Embrace", "1MR"},     {"Improved Health Funnel", "2LL"},
        {"Improved Voidwalker", "2ML"},  {"Fel Intellect", "2MR"},      {"Improved Succubus", "3LL"},   {"Fel Domination", "3ML"},
        {"Fel Stamina", "3MR"},          {"Master Summoner", "4ML"},    {"Unholy Power", "4MR"},        {"Improved Enslave Demon", "5LL"},
        {"Demonic Sacrifice", "5ML"},    {"Improved Firestone", "5RR"}, {"Master Demonologist", "6MR"}, {"Soul Link", "7ML"},
        {"Improved Spellstone", "7MR"},
    };

    QMap<QString, Talent*> tier1 {
        {"1LL", new Talent(warlock, this, "Improved Healthstone", "1LL", "Assets/misc/Inv_stone_04.png", 2,
                           "Increases the amount of Health restored by your Healthstone by %1%.", QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"1ML", new Talent(warlock, this, "Improved Imp", "1ML", "Assets/spell/Spell_shadow_summonimp.png", 3,
                           "Increases the effect of your Imp's Firebolt, Fire Shield, and Blood Pact spells by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"1MR", new Talent(warlock, this, "Demonic Embrace", "1MR", "Assets/spell/Spell_shadow_metamorphosis.png", 5,
                           "Increases your total Stamina by %1% but reduces your total Spirit by %2%.",
                           QVector<QPair<unsigned, unsigned>> {{3, 3}, {1, 1}})},
    };
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2LL", new Talent(warlock, this, "Improved Health Funnel", "2LL", "Assets/spell/Spell_shadow_lifedrain.png", 2,
                                  "Increases the amount of Health transferred by your Health Funnel spell by %1%.",
                                  QVector<QPair<unsigned, unsigned>> {{10, 10}})},
               {"2ML", new Talent(warlock, this, "Improved Voidwalker", "2ML", "Assets/spell/Spell_shadow_summonvoidwalker.png", 3,
                                  "Increases the effectiveness of your Voidwalker's Torment, Consume Shadows, Sacrifice and Suffering spells by %1%.",
                                  QVector<QPair<unsigned, unsigned>> {{10, 10}})},
               {"2MR", new Talent(warlock, this, "Fel Intellect", "2MR", "Assets/spell/Spell_holy_magicalsentry.png", 5,
                                  "Increases the maximum Mana of your Imp, Voidwalker, Succubus, and Felhunter by %1%.",
                                  QVector<QPair<unsigned, unsigned>> {{3, 3}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(warlock, this, "Improved Succubus", "3LL", "Assets/spell/Spell_shadow_summonsuccubus.png", 3,
                           "Increases the effect of your Succubus' Lash of Pain and Soothing Kiss spells by %1%, and increases the duration of your "
                           "Succubus' Seduction and Lesser Invisibility spells by %2%.",
                           QVector<QPair<unsigned, unsigned>> {{10, 10}, {10, 10}})},
        {"3ML", new Talent(warlock, this, "Fel Domination", "3ML", "Assets/spell/Spell_nature_removecurse.png", 1,
                           "Your next Imp, Voidwalker, Succubus, or Felhunter Summon spell has its casting time reduced by 5.5 sec and its Mana cost "
                           "reduced by 50%.",
                           QVector<QPair<unsigned, unsigned>> {})},
        {"3MR", new Talent(warlock, this, "Fel Stamina", "3MR", "Assets/spell/Spell_shadow_antishadow.png", 5,
                           "Increases the maximum Health of your Imp, Voidwalker, Succubus, and Felhunter by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{3, 3}})},
    };
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4ML",
         new Talent(warlock, this, "Master Summoner", "4ML", "Assets/spell/Spell_shadow_impphaseshift.png", 2,
                    "Reduces the casting time of your Imp, Voidwalker, Succubus, and Felhunter Summoning spells by %1 sec and the Mana cost by %2%.",
                    QVector<QPair<unsigned, unsigned>> {{2, 2}, {20, 20}})},
        {"4MR", new Talent(warlock, this, "Unholy Power", "4MR", "Assets/spell/Spell_shadow_shadowworddominate.png", 5,
                           "Increases the damage done by your Voidwalker, Succubus, and Felhunter's melee attacks by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{4, 4}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {
        {"5LL",
         new Talent(warlock, this, "Improved Enslave Demon", "5LL", "Assets/spell/Spell_shadow_enslavedemon.png", 5,
                    "Reduces the Attack Speed and Casting Speed penalty of your Enslave Demon spell by %1% and reduces the resist chance by %2%.",
                    QVector<QPair<unsigned, unsigned>> {{2, 2}, {2, 2}})},
        {"5RR", new Talent(warlock, this, "Improved Firestone", "5RR", "Assets/misc/Inv_ammo_firetar.png", 2,
                           "Increases the bonus Fire damage from Firestones and the Firestone effect by %1%.",
                           QVector<QPair<unsigned, unsigned>> {{15, 15}})}};
    add_demonic_sacrifice(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {
        {"6MR", new Talent(warlock, this, "Master Demonologist", "6MR", "Assets/spell/Spell_shadow_shadowpact.png", 5,
                           "Grants both the Warlock and the summoned demon an effect as long as that demon is active.\n\nImp - Reduces threat caused "
                           "by %1%.\n\nVoidwalker - Reduces physical damage taken by %2%.\n\nSuccubus - Increases all damage caused by "
                           "%3%.\n\nFelhunter - Increases all resistances by \n%4 per level.",
                           QVector<QPair<double, double>> {{4.0, 4.0}, {2.0, 2.0}, {2.0, 2.0}, {0.2, 0.2}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(warlock, this, "Soul Link", "7ML", "Assets/spell/Spell_shadow_gathershadows.png", 1,
                           "When active, 30% of all damage taken by the caster is taken by your Imp, Voidwalker, Succubus, or Felhunter demon "
                           "instead.  In addition, both the demon and master will inflict 3% more damage.  Lasts as long as the demon is active.",
                           QVector<QPair<unsigned, unsigned>>())},
        {"7MR", new Talent(warlock, this, "Improved Spellstone", "7MR", "Assets/misc/Inv_misc_gem_sapphire_01.png", 2,
                           "Increases the amount of damage absorbed by your Spellstone by %1%.", QVector<QPair<unsigned, unsigned>> {{15, 15}})}};
    add_talents(tier7);

    talents["3ML"]->talent->set_bottom_child(talents["4ML"]->talent);
    talents["4ML"]->talent->set_parent(talents["3ML"]->talent);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Demonology::add_demonic_sacrifice(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(
        warlock, this, "Demonic Sacrifice", "5ML", "Assets/spell/Spell_shadow_psychicscream.png", 1,
        "When activated, sacrifices your summoned demon to grant you an effect that lasts 30 min.  The effect is canceled "
        "if any Demon is summoned.\n\nImp: Increases your Fire damage by 15%.\n\nVoidwalker : Restores 3% of total Health "
        "every 4 sec.\n\nSuccubus: Increases your Shadow damage by 15%.\n\nFelhunter: Restores 2% of total Mana every 4 sec.",
        QVector<QPair<unsigned, unsigned>> {},
        QVector<QPair<TalentStat, unsigned>> {
            {TalentStat::ShadowDmgMod, 15},
        });

    add_talent_to_tier(talent_tier, talent);
}
