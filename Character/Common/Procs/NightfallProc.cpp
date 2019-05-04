#include "NightfallProc.h"

#include "Nightfall.h"

NightfallProc::NightfallProc(Character* pchar, const double proc_rate) :
    Proc("Nightfall", "Assets/items/Inv_axe_12.png", proc_rate, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>{ProcInfo::MainhandSpell, ProcInfo::MainhandSwing}, pchar),
    buff(new Nightfall(pchar))
{
    buff->enable_buff();
}

NightfallProc::~NightfallProc() {
    buff->disable_buff();
    delete buff;
}

void NightfallProc::proc_effect() {
    buff->apply_buff();
}
