#include "DruidSpells.h"

#include "BearForm.h"
#include "BearFormBuff.h"
#include "BloodFrenzy.h"
#include "CasterForm.h"
#include "CatForm.h"
#include "CatFormBuff.h"
#include "CharacterSpells.h"
#include "ClearcastingDruid.h"
#include "Druid.h"
#include "Enrage.h"
#include "FerociousBite.h"
#include "Furor.h"
#include "LeaderOfThePack.h"
#include "MainhandAttackDruid.h"
#include "Maul.h"
#include "Moonfire.h"
#include "MoonkinForm.h"
#include "MoonkinFormBuff.h"
#include "NaturesGrace.h"
#include "NoEffectSelfBuff.h"
#include "PrimalFury.h"
#include "RaidControl.h"
#include "Shred.h"
#include "SpellRankGroup.h"
#include "Starfire.h"
#include "Swipe.h"
#include "TigersFury.h"
#include "TigersFuryBuff.h"
#include "Wrath.h"

DruidSpells::DruidSpells(Druid* druid) : CharacterSpells(druid), druid(druid) {
    this->primal_fury = new PrimalFury(druid);
    this->mh_attack = new MainhandAttackDruid(druid, primal_fury);
    add_spell_group({mh_attack});

    this->caster_form = new CasterForm(druid);
    add_spell_group({caster_form});

    auto leader_of_the_pack = static_cast<LeaderOfThePack*>(
        pchar->get_raid_control()->get_shared_party_buff("Leader of the Pack", pchar->get_party()));
    if (leader_of_the_pack == nullptr) {
        leader_of_the_pack = new LeaderOfThePack(druid);
        leader_of_the_pack->enable_buff();
    }

    this->furor = new Furor(druid);
    this->bear_form_buff = new BearFormBuff(druid, leader_of_the_pack, furor);
    this->bear_form = new BearForm(druid, bear_form_buff);
    add_spell_group({bear_form});

    this->cat_form_buff = new CatFormBuff(druid, leader_of_the_pack, furor);
    this->cat_form = new CatForm(druid, cat_form_buff);
    add_spell_group({cat_form});

    auto moonkin_aura = static_cast<MoonkinFormBuff*>(pchar->get_raid_control()->get_shared_party_buff("Moonkin Form", pchar->get_party()));
    if (moonkin_aura == nullptr) {
        moonkin_aura = new MoonkinFormBuff(druid);
        moonkin_aura->enable_buff();
    }
    this->moonkin_form = new MoonkinForm(druid, moonkin_aura);
    add_spell_group({moonkin_form});

    add_spell_group({
        new Wrath(druid, this, 4),
        new Wrath(druid, this, 5),
        new Wrath(druid, this, 6),
        new Wrath(druid, this, 7),
        new Wrath(druid, this, 8),
    });

    add_spell_group({
        new Moonfire(druid, this, 1),
        new Moonfire(druid, this, 2),
        new Moonfire(druid, this, 3),
        new Moonfire(druid, this, 4),
        new Moonfire(druid, this, 5),
        new Moonfire(druid, this, 6),
        new Moonfire(druid, this, 7),
        new Moonfire(druid, this, 8),
        new Moonfire(druid, this, 9),
        new Moonfire(druid, this, 10),
    });

    add_spell_group({
        new Starfire(druid, this, 1),
        new Starfire(druid, this, 2),
        new Starfire(druid, this, 3),
        new Starfire(druid, this, 4),
        new Starfire(druid, this, 5),
        new Starfire(druid, this, 6),
        new Starfire(druid, this, 7),
    });

    this->blood_frenzy = new BloodFrenzy(druid);
    add_spell_group({
        new Shred(druid, this, blood_frenzy, 1),
        new Shred(druid, this, blood_frenzy, 2),
        new Shred(druid, this, blood_frenzy, 3),
        new Shred(druid, this, blood_frenzy, 4),
        new Shred(druid, this, blood_frenzy, 5),
    });

    add_spell_group({
        new Swipe(druid, this, primal_fury, 1),
        new Swipe(druid, this, primal_fury, 2),
        new Swipe(druid, this, primal_fury, 3),
        new Swipe(druid, this, primal_fury, 4),
        new Swipe(druid, this, primal_fury, 5),
    });

    this->maul_buff = new NoEffectSelfBuff(druid, BuffDuration::PERMANENT, "Maul Queued", "Assets/ability/Ability_rogue_ambush.png", Hidden::No);
    this->maul_buff->enable_buff();
    add_spell_group({
        new Maul(druid, this, maul_buff, 1),
        new Maul(druid, this, maul_buff, 2),
        new Maul(druid, this, maul_buff, 3),
        new Maul(druid, this, maul_buff, 4),
        new Maul(druid, this, maul_buff, 5),
        new Maul(druid, this, maul_buff, 6),
        new Maul(druid, this, maul_buff, 7),
    });

    add_spell_group({
        new FerociousBite(druid, 1),
        new FerociousBite(druid, 2),
        new FerociousBite(druid, 3),
        new FerociousBite(druid, 4),
        new FerociousBite(druid, 5),
    });

    add_spell_group({new Enrage(druid)});

    tigers_fury_buff = new TigersFuryBuff(pchar);
    tigers_fury_buff->enable_buff();
    add_spell_group({
        new TigersFury(druid, this, tigers_fury_buff, 1),
        new TigersFury(druid, this, tigers_fury_buff, 2),
        new TigersFury(druid, this, tigers_fury_buff, 3),
        new TigersFury(druid, this, tigers_fury_buff, 4),
    });

    natures_grace = new NaturesGrace(druid);
    omen_of_clarity = new ClearcastingDruid(druid);
}

DruidSpells::~DruidSpells() {
    delete natures_grace;
    delete omen_of_clarity;
    delete cat_form_buff;
    delete bear_form_buff;
    delete blood_frenzy;
    delete furor;
    delete tigers_fury_buff;
    delete maul_buff;
}

void DruidSpells::mh_auto_attack(const int iteration) {
    if (!mh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    if (maul->is_queued() && maul->get_spell_status() == SpellStatus::Available) {
        maul->calculate_damage();
    } else {
        if (maul->is_queued())
            maul->cancel();

        mh_attack->perform();
    }

    add_next_mh_attack();
}

void DruidSpells::prepare_set_of_combat_iterations_class_specific() {
    SpellRankGroup* group = get_spell_rank_group_by_name("Maul");
    maul = static_cast<Maul*>(group->get_max_available_spell_rank());
}

CasterForm* DruidSpells::get_caster_form() const {
    return this->caster_form;
}

BearForm* DruidSpells::get_bear_form() const {
    return this->bear_form;
}

CatForm* DruidSpells::get_cat_form() const {
    return this->cat_form;
}

MoonkinForm* DruidSpells::get_moonkin_form() const {
    return this->moonkin_form;
}

Buff* DruidSpells::get_natures_grace() const {
    return this->natures_grace;
}

Buff* DruidSpells::get_cat_form_buff() const {
    return this->cat_form_buff;
}

Buff* DruidSpells::get_bear_form_buff() const {
    return this->bear_form_buff;
}

Proc* DruidSpells::get_omen_of_clarity() const {
    return this->omen_of_clarity;
}

Proc* DruidSpells::get_blood_frenzy() const {
    return this->blood_frenzy;
}

Proc* DruidSpells::get_primal_fury() const {
    return this->primal_fury;
}

Proc* DruidSpells::get_furor() const {
    return this->furor;
}

bool DruidSpells::omen_of_clarity_active() const {
    const bool active = omen_of_clarity->buff->is_active();
    omen_of_clarity->buff->use_charge();
    return active;
}
