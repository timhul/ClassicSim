#pragma once

#include "UniqueDebuff.h"

class Proc;

class NoEffectUniqueDebuff: public UniqueDebuff {
public:
    NoEffectUniqueDebuff(Character* pchar,
                 const int duration,
                 const QString& name = "NO_NAME",
                 const QString& icon = NO_ICON,
                 const bool hidden = Hidden::Yes,
                 const int charges = 0);

    void link_buff_expiration(Buff* buff_to_cancel);

    void link_proc_application(Proc* proc_to_apply);
    void link_proc_expiration(Proc* proc_to_cancel);

private:
    Buff* buff_to_cancel {nullptr};
    Proc* proc_to_apply {nullptr};
    Proc* proc_to_cancel {nullptr};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
