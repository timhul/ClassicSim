#include "ResourceTick.h"

#include "NoEffectSelfBuff.h"
#include "RegeneratingResource.h"
#include "Utils/Check.h"

ResourceTick::ResourceTick(Character* pchar, RegeneratingResource* resource)
    :
      SpellPeriodic("Resource Tick", "no-icon", pchar,
                    new NoEffectSelfBuff(pchar, BuffDuration::PERMANENT),
                    RestrictedByGcd::No, ResourceType::Mana, 2.0, 0),
      resource(resource)
{}

ResourceTick::~ResourceTick() {
    delete marker_buff;
}

bool ResourceTick::check_application_success() {
    return true;
}

void ResourceTick::new_application_effect() {

}

void ResourceTick::refresh_effect() {

}

void ResourceTick::tick_effect() {
    resource->tick_resource();

    add_next_tick();
}

void ResourceTick::reset_effect() {

}
