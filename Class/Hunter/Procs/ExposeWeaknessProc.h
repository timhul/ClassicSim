#pragma once

#include "Proc.h"
#include "SetBonusRequirer.h"

class ExposeWeaknessBuff;

class ExposeWeaknessProc: public Proc, public SetBonusRequirer {
public:
    ExposeWeaknessProc(Character* pchar, ExposeWeaknessBuff* expose_weakness_buff);
    ~ExposeWeaknessProc() override;

    void proc_effect() override;

private:
    ExposeWeaknessBuff* expose_weakness_buff;

    void enable_spell_effect() override;
    void disable_spell_effect() override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};
