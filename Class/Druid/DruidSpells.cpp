#include "DruidSpells.h"

#include "BearForm.h"
#include "BloodFrenzy.h"
#include "CasterForm.h"
#include "CatForm.h"
#include "CatFormBuff.h"
#include "ClearcastingDruid.h"
#include "Druid.h"
#include "FerociousBite.h"
#include "Furor.h"
#include "LeaderOfThePack.h"
#include "MainhandAttackDruid.h"
#include "Moonfire.h"
#include "MoonkinForm.h"
#include "MoonkinFormBuff.h"
#include "NaturesGrace.h"
#include "RaidControl.h"
#include "Shred.h"
#include "Starfire.h"
#include "Wrath.h"

DruidSpells::DruidSpells(Druid* druid) :
    CharacterSpells(druid),
    druid(druid)
{
    this->mh_attack = new MainhandAttackDruid(druid);
    add_spell_group({mh_attack});

    this->caster_form = new CasterForm(druid);
    add_spell_group({caster_form});

    this->bear_form = new BearForm(druid);
    add_spell_group({bear_form});

    auto leader_of_the_pack = dynamic_cast<LeaderOfThePack*>(pchar->get_raid_control()->get_shared_party_buff("Leader of the Pack", pchar->get_party()));
    if (leader_of_the_pack == nullptr) {
        leader_of_the_pack = new LeaderOfThePack(druid);
        leader_of_the_pack->enable_buff();
    }
    this->furor = new Furor(druid);
    this->cat_form_buff = new CatFormBuff(druid, leader_of_the_pack, furor);
    this->cat_form = new CatForm(druid, cat_form_buff);
    add_spell_group({cat_form});

    auto moonkin_aura = dynamic_cast<MoonkinFormBuff*>(pchar->get_raid_control()->get_shared_party_buff("Moonkin Form", pchar->get_party()));
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
                        new FerociousBite(druid, 1),
                        new FerociousBite(druid, 2),
                        new FerociousBite(druid, 3),
                        new FerociousBite(druid, 4),
                        new FerociousBite(druid, 5),
                    });

    natures_grace = new NaturesGrace(druid);
    omen_of_clarity = new ClearcastingDruid(druid);
}

DruidSpells::~DruidSpells() {
    delete natures_grace;
    delete omen_of_clarity;
    delete cat_form_buff;
    delete blood_frenzy;
    delete furor;
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

Proc* DruidSpells::get_omen_of_clarity() const {
    return this->omen_of_clarity;
}

Proc* DruidSpells::get_blood_frenzy() const {
    return this->blood_frenzy;
}

Proc* DruidSpells::get_furor() const {
    return this->furor;
}

bool DruidSpells::omen_of_clarity_active() const {
    const bool active = omen_of_clarity->buff->is_active();
    omen_of_clarity->buff->use_charge();
    return active;
}
