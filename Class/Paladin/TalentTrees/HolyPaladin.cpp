#include "HolyPaladin.h"

#include "Consecration.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "TalentStatIncrease.h"

HolyPaladin::HolyPaladin(Paladin* paladin) :
    TalentTree("Holy", "Assets/paladin/paladin_holy.jpg"),
    paladin(paladin),
    spells(dynamic_cast<PaladinSpells*>(paladin->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1ML", get_divine_strength()},
                                  {"1MR", get_divine_intellect()}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent(paladin, this, "Spiritual Focus", "2ML", "Assets/spell/Spell_arcane_blink.png", 5, "Gives your Flash of Light and Holy Light spells a %1% chance to not lose casting time when you take damage.", QVector<QPair<unsigned, unsigned>>{{14, 14}})},
                                  {"2MR", new Talent(paladin, this, "Improved Seal of Righteousness", "2MR", "Assets/ability/Ability_thunderbolt.png", 5, "Increases the damage done by your Seal of Righteousness and Judgement of Righteousness by %1%.", QVector<QPair<unsigned, unsigned>>{{3, 3}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(paladin, this, "Healing Light", "3LL", "Assets/spell/Spell_holy_holybolt.png", 3, "Increases the amount of healed by your Holy Light and Flash of Light spells by %1%.", QVector<QPair<unsigned, unsigned>>{{4, 4}})},
                                  {"3ML", get_consecration()},
                                  {"3MR", new Talent(paladin, this, "Improved Lay on Hands", "3MR", "Assets/spell/Spell_holy_layonhands.png", 2, "Gives the target of your Lay on Hands spell a %1% bonus to their armor value from items for 2 min. In addition, the cooldown for your Lay on Hands spell is reduced by %2 min.", QVector<QPair<unsigned, unsigned>>{{15, 15}, {10, 10}})},
                                  {"3RR", new Talent(paladin, this, "Unyielding Faith", "3RR", "Assets/spell/Spell_holy_unyieldingfaith.png", 2, "Increases your chance to resist Fear and Disorient effects by an additional %1%.", QVector<QPair<unsigned, unsigned>>{{5, 5}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent(paladin, this, "Illumination", "4ML", "Assets/spell/Spell_holy_greaterheal.png", 5, "After getting a critical effect from your Flash of Light, Holy Light, or Holy Shock heal spell, gives you a %1% chance to gain Mana equal to the base cost of the spell.", QVector<QPair<unsigned, unsigned>>{{20, 20}})},
                                  {"4MR", new Talent(paladin, this, "Improved Blessing of Wisdom", "4MR", "Assets/spell/Spell_holy_sealofwisdom.png", 2, "Increases the effect of your Blessing of Wisdom spell by %1%.", QVector<QPair<unsigned, unsigned>>{{10, 10}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(paladin, this, "Divine Favor", "5ML", "Assets/spell/Spell_holy_heal.png", 1, "When activated, gives your next Flash of Light, Holy Light, or Holy Shock spell a 100% critical effect chance.", QVector<QPair<unsigned, unsigned>>())},
                                  {"5MR", new Talent(paladin, this, "Lasting Judgement", "5MR", "Assets/spell/Spell_holy_healingaura.png", 3, "Increases the duration of your Judgement of Light and Judgement of Wisdom by %1 sec.", QVector<QPair<unsigned, unsigned>>{{10, 10}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Talent(paladin, this, "Holy Power", "6MR", "Assets/spell/Spell_holy_power.png", 5, "Increases the critical effect chance of your Holy spells by %1%.", QVector<QPair<unsigned, unsigned>>{{1, 1}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(paladin, this, "Holy Shock", "7ML", "Assets/spell/Spell_holy_searinglight.png", 1, "Blast the target with Holy energy, causing 204 to 221 Holy damage to an enemy, or 204 to 221 healing to an ally.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["4ML"]->talent->set_bottom_child(talents["5ML"]->talent);
    talents["5ML"]->talent->set_parent(talents["4ML"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* HolyPaladin::get_divine_strength() {
    return new TalentStatIncrease(paladin, this, "Divine Strength", "1ML", "Assets/ability/Ability_golemthunderclap.png",
                                  5, "Increases your Strength by %1%.",
                                  QVector<QPair<unsigned, unsigned>>{{2, 2}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::StrengthMod, 2}});
}

Talent* HolyPaladin::get_divine_intellect() {
    return new TalentStatIncrease(paladin, this, "Divine Intellect", "1MR", "Assets/spell/Spell_nature_sleep.png",
                                  5, "Increases your total Intellect by %1%.",
                                  QVector<QPair<unsigned, unsigned>>{{2, 2}},
                                  QVector<QPair<TalentStat, unsigned>>{{TalentStat::IntellectMod, 2}});
}

Talent* HolyPaladin::get_consecration() {
    return get_new_talent(paladin, "Consecration", "3ML", "Assets/spell/Spell_holy_innerfire.png",
                          1, "Consecrates the land beneath Paladin, doing 64 Holy damage over 8 sec to enemies who enter the area.",
                          QVector<QPair<unsigned, unsigned>>(),
                          QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Consecration")});
}
