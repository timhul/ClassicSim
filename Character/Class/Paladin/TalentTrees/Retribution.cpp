#include "Retribution.h"

#include "Paladin.h"
#include "PaladinSpells.h"
#include "TalentStatIncrease.h"

Retribution::Retribution(Paladin* paladin) :
    TalentTree("Retribution", "Assets/paladin/paladin_combat.jpg"),
    paladin(paladin),
    spells(dynamic_cast<PaladinSpells*>(paladin->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1ML", new Talent(paladin, this, "Improved Blessing of Might", "1ML", "Assets/spell/Spell_holy_fistofjustice.png", 5, "Increases the melee attack power bonus of your Blessing of Might by %1%.", QVector<QPair<unsigned, unsigned>>{{4, 4}})},
                                  {"1MR", new Talent(paladin, this, "Benediction", "1MR", "Assets/spell/Spell_frost_windwalkon.png", 5, "Reduces the Mana cost of your Judgement and Seal spells by %1%.", QVector<QPair<unsigned, unsigned>>{{3, 3}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(paladin, this, "Improved Judgement", "2LL", "Assets/spell/Spell_holy_righteousfury.png", 2, "Decreases the cooldown of your Judgement spell by %1 sec.", QVector<QPair<unsigned, unsigned>>{{1, 1}})},
                                  {"2ML", new Talent(paladin, this, "Improved Seal of the Crusader", "2ML", "Assets/spell/Spell_holy_holysmite.png", 3, "Increases the melee attack power bonus of your Seal of the Crusader and the Holy damage increase of your Judgement of the Crusader by %1%.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"2MR", new Talent(paladin, this, "Deflection", "2MR", "Assets/ability/Ability_parry.png", 5, "Increases your Parry chance by %1%", QVector<QPair<unsigned, unsigned>>{{1, 1}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(paladin, this, "Vindication", "3LL", "Assets/spell/Spell_holy_vindication.png", 3, "Gives the Paladin's damaging melee attacks a chance to reduce the target's Strength and Agility by %1% for 10 sec.", QVector<QPair<unsigned, unsigned>>{{5, 5}})},
                                  {"3ML", new Talent(paladin, this, "Conviction", "3ML", "Assets/spell/Spell_holy_retributionaura.png", 5, "Increases your chance to get a critical strike with melee weapons by %1%.", QVector<QPair<unsigned, unsigned>>{{1, 1}})},
                                  {"3MR", new Talent(paladin, this, "Seal of Command", "3MR", "Assets/ability/Ability_warrior_innerrage.png", 1, "Gives the Paladin a chance to deal additional Holy damage equal to 70% of normal weapon damage. Only one Seal can be active on the Paladin at any one time. Lasts 30 sec.\n\nUnleashing this Seal's energy will judge an enemy, instantly causing 46.5 to 55.5 Holy damage, 93 to 102 if the target is stunned or incapacitated.", QVector<QPair<unsigned, unsigned>>())},
                                  {"3RR", new Talent(paladin, this, "Pursuit of Justice", "3RR", "Assets/spell/Spell_holy_persuitofjustice.png", 2, "Increases movement and mounted movement speed by %1%. This does not stack with other movement speed increasing effects.", QVector<QPair<unsigned, unsigned>>{{4, 4}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(paladin, this, "Eye of an Eye", "4LL", "Assets/spell/Spell_holy_eyeforaneye.png", 2, "All spell criticals against you cause %1% of the damage taken to the caster as well. The damage caused by Eye for an Eye will not exceed 50% of the Paladin's total health.", QVector<QPair<unsigned, unsigned>>{{15, 15}})},
                                  {"4MR", new Talent(paladin, this, "Improved Retribution Aura", "4MR", "Assets/spell/Spell_holy_auraoflight.png", 2, "Increases the damage done by your Retribution Aura by %1%.", QVector<QPair<unsigned, unsigned>>{{25, 25}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(paladin, this, "Two-Handed Weapon Specialization", "5LL", "Assets/items/Inv_hammer_04.png", 3, "Increases the damage you deal with two-handed melee weapons by %1%.", QVector<QPair<unsigned, unsigned>>{{2, 2}})},
                                  {"5MR", new Talent(paladin, this, "Sanctity Aura", "5MR", "Assets/spell/Spell_holy_mindvision.png", 1, "Increases Holy damage done by party members within 30 yards by 10%. Players may only have one Aura on them per Paladin at any one time.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6ML", new Talent(paladin, this, "Vengeance", "6ML", "Assets/ability/Ability_racial_avatar.png", 5, "Gives you a %1% bonus to Physical and Holy damage you deal for 8 sec after dealing a critical strike from a weapon swing, spell, or ability.", QVector<QPair<unsigned, unsigned>>{{3, 3}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(paladin, this, "Repentance", "7ML", "Assets/spell/Spell_holy_prayerofhealing.png", 1, "Puts the enemy target in a state of meditation, incapacitating them for up to 6 sec. Any damage caused will awaken the target. Only works against Humanoids.", QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["3ML"]->talent);
}
