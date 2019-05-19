#include "ResourceTick.h"

#include "Character.h"
#include "CooldownControl.h"
#include "RegeneratingResource.h"
#include "Utils/Check.h"

ResourceTick::ResourceTick(Character* pchar, RegeneratingResource* resource)
    :
      Spell("Resource Tick", "no-icon", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Mana, 0),
      resource(resource)
{}

ResourceTick::~ResourceTick() {
    delete cooldown;
}

void ResourceTick::spell_effect() {
    check(false, "Not implemented");
}

void ResourceTick::perform_periodic() {
    resource->tick_resource();
}
