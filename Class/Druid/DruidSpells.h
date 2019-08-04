#pragma once

#include "CharacterSpells.h"

class BearForm;
class Buff;
class CasterForm;
class CatForm;
class ClearcastingDruid;
class Druid;
class MoonkinForm;
class Proc;

class DruidSpells: public CharacterSpells {
public:
    DruidSpells(Druid* druid);
    ~DruidSpells() override;

    CasterForm* get_caster_form() const;
    BearForm* get_bear_form() const;
    CatForm* get_cat_form() const;
    MoonkinForm* get_moonkin_form() const;
    Buff* get_natures_grace() const;
    Buff* get_cat_form_buff() const;
    Proc* get_omen_of_clarity() const;

    bool omen_of_clarity_active() const;

private:
    Druid* druid;

    CasterForm* caster_form;
    BearForm* bear_form;
    CatForm* cat_form;
    MoonkinForm* moonkin_form;
    Buff* natures_grace;
    Buff* cat_form_buff;
    ClearcastingDruid* omen_of_clarity;
};
