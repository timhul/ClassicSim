#include "Combat.h"

#include "AdrenalineRush.h"
#include "Aggression.h"
#include "BladeFlurryTalent.h"
#include "DaggerSpecialization.h"
#include "DualWieldSpecializationRogue.h"
#include "FistWeaponSpecialization.h"
#include "GenericTalent.h"
#include "ImprovedBackstab.h"
#include "ImprovedSinisterStrike.h"
#include "MaceSpecialization.h"
#include "Precision.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SwordSpecialization.h"
#include "Talent.h"
#include "WeaponExpertise.h"

Combat::Combat(Character *pchar) :
    TalentTree("Combat", "Assets/rogue/rogue_combat.jpg"),
    rogue(dynamic_cast<Rogue*>(pchar)),
    spells(dynamic_cast<RogueSpells*>(pchar->get_spells()))
{
    QMap<QString, Talent*> tier1 {{"1LL", new GenericTalent(pchar, this, "Improved Gouge", "1LL", "Assets/ability/Ability_gouge.png", 3, "Increases the effect duration of your Gouge ability by %1 sec.", QVector<QPair<double, double>>{{0.5, 0.5}})},
                                  {"1ML", new ImprovedSinisterStrike(pchar, this)},
                                  {"1MR", new GenericTalent(pchar, this, "Lightning Reflexes", "1MR", "Assets/spell/Spell_nature_invisibility.png", 5, "Increases your Dodge chance by %1%.", QVector<QPair<int, int>>{{1, 1}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new ImprovedBackstab(pchar, this)},
                                  {"2ML", new GenericTalent(pchar, this, "Deflection", "2ML", "Assets/ability/Ability_parry.png", 5, "Increases your Parry chance by %1%.", QVector<QPair<int, int>>{{1, 1}})},
                                  {"2MR", new Precision(pchar, this)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new GenericTalent(pchar, this, "Endurance", "3LL", "Assets/spell/Spell_shadow_shadowward.png", 2, "Reduces the cooldown of your Sprint and Evasion abilities by %1 sec.", QVector<QPair<int, int>>{{45, 45}})},
                                  {"3ML", new GenericTalent(pchar, this, "Riposte", "3ML", "Assets/ability/Ability_warrior_challange.png", 1, "A strike that becomes active after parrying an opponent's attack. This deals 150% weapon damage and disarms the target for 6 sec.", QVector<QPair<int, int>>{})},
                                  {"3RR", new GenericTalent(pchar, this, "Improved Sprint", "3RR", "Assets/ability/Ability_rogue_sprint.png", 2, "Gives a %1% chance to remove all movement impairing effects when you activate your Sprint ability.", QVector<QPair<int, int>>{{50, 50}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new GenericTalent(pchar, this, "Improved Kick", "4LL", "Assets/ability/Ability_kick.png", 2, "Gives your Kick ability a %1% chance to silence the target for 2 sec.", QVector<QPair<int, int>>{{50, 50}})},
                                  {"4ML", new DaggerSpecialization(pchar, this)},
                                  {"4MR", new DualWieldSpecializationRogue(pchar, this)}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new MaceSpecialization(pchar, this)},
                                  {"5ML", new BladeFlurryTalent(pchar, this)},
                                  {"5MR", get_sword_spec()},
                                  {"5RR", new FistWeaponSpecialization(pchar, this)}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6ML", new WeaponExpertise(pchar, this)},
                                  {"6MR", new Aggression(pchar, this)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", get_adrenaline_rush()}};
    add_talents(tier7);

    talents["2ML"]->talent->set_bottom_child(talents["3ML"]->talent);
    talents["3ML"]->talent->set_parent(talents["2ML"]->talent);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

Talent* Combat::get_sword_spec() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Gives you a %1% chance to get an extra attack on the same target after dealing damage with your Sword.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<int, int>>{{1, 1}});
    Talent* talent = new Talent(rogue, this, "Sword Specialization", "5MR",
                                "Assets/items/Inv_sword_27.png", 5, rank_descriptions,
                                {}, {},
                                QVector<Proc*>{rogue->get_sword_spec()});

    return talent;
}

Talent* Combat::get_adrenaline_rush() {
    QMap<int, QString> rank_descriptions;
    QString base_str = "Increases your Energy regeneration rate by 100% for 15 sec.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(rogue, this, "Adrenaline Rush", "7ML",
                                "Assets/spell/Spell_shadow_shadowworddominate.png", 1, rank_descriptions,
                                QVector<Spell*>{spells->get_adrenaline_rush()});

    return talent;
}
