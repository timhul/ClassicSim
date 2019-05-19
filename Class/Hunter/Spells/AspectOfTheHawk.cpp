#include "AspectOfTheHawk.h"

#include "AspectOfTheHawkBuff.h"
#include "Character.h"
#include "CooldownControl.h"
#include "ImprovedAspectOfTheHawkProc.h"

AspectOfTheHawk::AspectOfTheHawk(Character* pchar) :
    Spell("Aspect of the Hawk",
          "Assets/spell/Spell_nature_ravenform.png",
          pchar,
          RestrictedByGcd::Yes,
          0.0,
          ResourceType::Mana,
          120),
    aspect_of_the_hawk_buff(new AspectOfTheHawkBuff(pchar)),
    imp_hawk_proc(new ImprovedAspectOfTheHawkProc(pchar, aspect_of_the_hawk_buff))
{
    aspect_of_the_hawk_buff->enable_buff();
}

AspectOfTheHawk::~AspectOfTheHawk() {
    if (aspect_of_the_hawk_buff->is_enabled())
        aspect_of_the_hawk_buff->disable_buff();

    delete aspect_of_the_hawk_buff;
    delete imp_hawk_proc;
}

void AspectOfTheHawk::spell_effect() {
    cooldown->add_gcd_event();
    aspect_of_the_hawk_buff->apply_buff();
}

Proc* AspectOfTheHawk::get_improved_aspect_of_the_hawk_proc() const {
    return this->imp_hawk_proc;
}

AspectOfTheHawkBuff* AspectOfTheHawk::get_aspect_of_the_hawk_buff() const {
    return this->aspect_of_the_hawk_buff;
}
