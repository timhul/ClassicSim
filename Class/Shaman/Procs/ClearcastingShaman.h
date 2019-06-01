#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Buff;
class Shaman;

class ClearcastingShaman: public Proc, public TalentRequirer {
public:
    ClearcastingShaman(Shaman* pchar);
    ~ClearcastingShaman() override;

private:
    friend class ShamanSpells;

    Buff* buff;

    void proc_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
