#pragma once

#include "CharacterSpells.h"

class ClearcastingMage;
class Combustion;
class ElementalVulnerability;
class Ignite;
class ImprovedScorch;
class Mage;
class Proc;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage* mage);
    ~MageSpells() override;

    Combustion* get_combustion() const;
    Proc* get_clearcasting() const;
    Proc* get_improved_scorch() const;
    Proc* get_t3_6piece_proc() const;
    Buff* get_t3_6piece_buff() const;
    Proc* get_t2_8piece_proc() const;
    Buff* get_t2_8piece_buff() const;

    void inflict_ignite(const double damage);
    bool clearcasting_active() const;
    void roll_clearcasting();
    void roll_netherwind_focus();

private:
    Mage* mage;

    ClearcastingMage* clearcasting;
    Combustion* combustion;
    ElementalVulnerability* elemental_vulnerability;
    Ignite* ignite;
    ImprovedScorch* imp_scorch;
    Proc* t3_6piece_proc;
    Proc* t2_8piece_proc;
    Buff* t2_8piece_buff;
};
