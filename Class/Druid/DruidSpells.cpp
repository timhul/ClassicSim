#include "DruidSpells.h"

#include "BearForm.h"
#include "CasterForm.h"
#include "CatForm.h"
#include "ClearcastingDruid.h"
#include "Druid.h"
#include "MainhandAttack.h"
#include "Moonfire.h"
#include "MoonkinForm.h"
#include "MoonkinFormBuff.h"
#include "NaturesGrace.h"
#include "RaidControl.h"
#include "Starfire.h"
#include "Wrath.h"

DruidSpells::DruidSpells(Druid* druid) :
    CharacterSpells(druid),
    druid(druid)
{
    this->mh_attack = new MainhandAttack(druid);
    add_spell_group({mh_attack});

    this->caster_form = new CasterForm(druid);
    add_spell_group({caster_form});

    this->bear_form = new BearForm(druid);
    add_spell_group({bear_form});

    this->cat_form = new CatForm(druid);
    add_spell_group({cat_form});

    auto buff = dynamic_cast<MoonkinFormBuff*>(pchar->get_raid_control()->get_shared_party_buff("Moonkin Form", pchar->get_party()));
    if (buff == nullptr) {
        buff = new MoonkinFormBuff(druid);
        buff->enable_buff();
    }
    this->moonkin_form = new MoonkinForm(druid, buff);
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

    natures_grace = new NaturesGrace(druid);
    omen_of_clarity = new ClearcastingDruid(druid);
}

DruidSpells::~DruidSpells() {
    delete natures_grace;
    delete omen_of_clarity;
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

Proc* DruidSpells::get_omen_of_clarity() const {
    return this->omen_of_clarity;
}

bool DruidSpells::omen_of_clarity_active() const {
    const bool active = omen_of_clarity->buff->is_active();
    omen_of_clarity->buff->use_charge();
    return active;
}
