#include "SealOfCommandProc.h"

#include "Engine.h"
#include "ItemNamespace.h"
#include "ProcInfo.h"
#include "SealOfCommand.h"
#include "SpellCallback.h"
#include "Utils/Check.h"

SealOfCommandProc::SealOfCommandProc(Character* pchar, SealOfCommand* seal) :
    ProcPPM("Seal of Command (MH)", "Assets/ability/Ability_warrior_innerrage.png", EnchantSlot::MAINHAND,
            7.0, 0, QVector<Proc*>(),
            QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                       ProcInfo::Source::RangedSpell}),
            pchar),
    seal(seal)
{
    this->enabled = false;
}

void SealOfCommandProc::proc_effect() {
    auto* new_event = new SpellCallback(seal, engine->get_current_priority() + 0.5);
    this->engine->add_event(new_event);
    seal->signal_proc_in_progress();
}

bool SealOfCommandProc::proc_specific_conditions_fulfilled() const {
    return !seal->proc_is_in_progress();
}
