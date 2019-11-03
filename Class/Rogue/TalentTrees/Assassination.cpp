#include "Assassination.h"

#include "Backstab.h"
#include "Eviscerate.h"
#include "Hemorrhage.h"
#include "InstantPoison.h"
#include "Malice.h"
#include "Murder.h"
#include "RelentlessStrikes.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "Ruthlessness.h"
#include "SealFate.h"
#include "SinisterStrike.h"
#include "SliceAndDice.h"
#include "Talent.h"
#include "Vigor.h"

Assassination::Assassination(Rogue* pchar) :
    TalentTree("Assassination", "Assets/rogue/rogue_assassination.jpg"),
    rogue(pchar),
    spells(static_cast<RogueSpells*>(pchar->get_spells()))
{
    talent_names_to_locations = {
        {"Improved Eviscerate", "1LL"},
        {"Remorseless Attacks", "1ML"},
        {"Malice", "1MR"},
        {"Ruthlessness", "2LL"},
        {"Murder", "2ML"},
        {"Improved Slice And Dice", "2RR"},
        {"Relentless Strikes", "3LL"},
        {"Improved Expose Armor", "3ML"},
        {"Lethality", "3MR"},
        {"Vile Poisons", "4ML"},
        {"Improved Poisons", "4MR"},
        {"Cold Blood", "5ML"},
        {"Improved Kidney Shot", "5MR"},
        {"Seal Fate", "6ML"},
        {"Vigor", "7ML"},
    };


    QMap<QString, Talent*> tier1 {{"1ML", new Talent(pchar, this, "Remorseless Attacks", "1ML", "Assets/ability/Ability_fiegndead.png", 2, "After killing an opponent that yields experience or honor, gives you a %1 increased critical strike chance on your next Sinister Strike, Backstab, Ambush, or Ghostly Strike. Lasts 20 sec.", QVector<QPair<unsigned, unsigned>>{{20, 20}})},
                                  {"1MR", new Malice(pchar, this)}};
    add_improved_eviscerate(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Murder(pchar, this)}};
    add_ruthlessness(tier2);
    add_improved_slice_and_dice(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3ML", new Talent(pchar, this, "Improved Expose Armor", "3ML", "Assets/ability/Ability_warrior_riposte.png", 2, "Increases the armor reduced by your Expose Armor ability by %1%.", QVector<QPair<unsigned, unsigned>>{{25, 25}})}};
    add_relentless_strikes(tier3);
    add_lethality(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {};
    add_vile_poisons(tier4);
    add_improved_poisons(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(pchar, this, "Cold Blood", "5ML", "Assets/spell/Spell_ice_lament.png", 1, "When activated, increases the critical strike chance of your next Sinister Strike, Backstab, Ambush, or Eviscerate by 100%.", QVector<QPair<unsigned, unsigned>>())},
                                  {"5MR", new Talent(pchar, this, "Improved Kidney Shot", "5MR", "Assets/ability/Ability_rogue_kidneyshot.png", 3, "While affected by your Kidney Shot ability, the target receives an additional %1% damage from all sources.", QVector<QPair<unsigned, unsigned>>{{3, 3}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_seal_fate(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Vigor(pchar, this)}};
    add_talents(tier7);

    talents["1MR"]->talent->set_bottom_child(talents["3MR"]->talent);
    talents["3MR"]->talent->set_parent(talents["1MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Assassination::add_improved_eviscerate(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the damage done by your Eviscerate ability by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 3, QVector<QPair<unsigned, unsigned>>{{5, 5}});
    Talent* talent = new Talent(rogue, this, "Improved Eviscerate", "1LL",
                                "Assets/ability/Ability_rogue_eviscerate.png", 3, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Eviscerate")});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_ruthlessness(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Gives your finishing moves a %1% chance to add a combo point to your target.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 3, QVector<QPair<unsigned, unsigned>>{{20, 20}});
    Talent* talent = new Talent(rogue, this, "Ruthlessness", "2LL",
                                "Assets/ability/Ability_druid_disembowel.png", 3, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{rogue->get_ruthlessness()});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_improved_slice_and_dice(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the duration of your Slice and Dice ability by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 3, QVector<QPair<unsigned, unsigned>>{{15, 15}});
    Talent* talent = new Talent(rogue, this, "Improved Slice And Dice", "2RR",
                                "Assets/ability/Ability_rogue_slicedice.png", 3, rank_descriptions,
                                QVector<SpellRankGroup*>{spells->get_spell_rank_group_by_name("Slice and Dice")});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_relentless_strikes(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Your finishing moves have a 20% chance per combo point to restore 25 Energy.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(rogue, this, "Relentless Strikes", "3LL",
                                "Assets/ability/Ability_warrior_decisivestrike.png", 1, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{rogue->get_relentless_strikes()});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_lethality(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the critical strike damage bonus of your Sinister Strike, Gouge, Backstab, Ghostly Strike, and Hemorrhage abilities by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{6, 6}});
    Talent* talent = new Talent(rogue, this, "Lethality", "3MR",
                                "Assets/ability/Ability_criticalstrike.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*>{
                                    spells->get_spell_rank_group_by_name("Backstab"),
                                    spells->get_spell_rank_group_by_name("Hemorrhage"),
                                    spells->get_spell_rank_group_by_name("Sinister Strike")
                                });

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_vile_poisons(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the damage dealt by your poisons by %1% and gives your poisons an additional %2% chance to resist dispel effects.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{4, 4}, {8, 8}});
    Talent* talent = new Talent(rogue, this, "Vile Poisons", "4ML",
                                "Assets/ability/Ability_rogue_feigndeath.png", 5, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{rogue->get_mh_instant_poison(), rogue->get_oh_instant_poison()});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_improved_poisons(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Increases the chance to apply poisons to your target by %1%.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{2, 2}});
    Talent* talent = new Talent(rogue, this, "Improved Poisons", "4MR",
                                "Assets/ability/Ability_poisons.png", 5, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{rogue->get_mh_instant_poison(), rogue->get_oh_instant_poison()});

    add_talent_to_tier(talent_tier, talent);
}

void Assassination::add_seal_fate(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = "Your critical strikes from abilities that add combo points have a %1% chance to add an additional combo point.";
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>>{{20, 20}});
    Talent* talent = new Talent(rogue, this, "Seal Fate", "6ML",
                                "Assets/spell/Spell_shadow_chilltouch.png", 5, rank_descriptions,
                                {},
                                {},
                                QVector<Proc*>{rogue->get_seal_fate()});

    add_talent_to_tier(talent_tier, talent);
}
