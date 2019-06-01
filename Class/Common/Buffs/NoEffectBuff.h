#ifndef NOEFFECTBUFF_H
#define NOEFFECTBUFF_H

#include "Buff.h"

class Proc;

class NoEffectBuff: public Buff {
public:
    NoEffectBuff(Character* pchar,
                 const int duration,
                 const QString& name = "NO_NAME",
                 const QString& icon = NO_ICON,
                 const bool hidden = Hidden::Yes,
                 const bool debuff = false,
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

#endif // NOEFFECTBUFF_H
