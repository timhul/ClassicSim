#ifndef EXPOSEWEAKNESSPROC_H
#define EXPOSEWEAKNESSPROC_H

#include "Proc.h"
#include "SetBonusRequirer.h"

class ExposeWeaknessBuff;

class ExposeWeaknessProc: public Proc, public SetBonusRequirer {
public:
    ExposeWeaknessProc(Character* pchar);
    ~ExposeWeaknessProc() override;

    void proc_effect() override;

    ExposeWeaknessBuff* get_expose_weakness_buff() const;

private:
    ExposeWeaknessBuff* expose_weakness_buff;

    void enable_spell_effect() override;
    void disable_spell_effect() override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // EXPOSEWEAKNESSPROC_H
