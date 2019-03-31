#include "ResourceTick.h"

#include "Character.h"
#include "RegeneratingResource.h"
#include "Utils/Check.h"

ResourceTick::ResourceTick(Character* pchar, RegeneratingResource* resource)
    :
      Spell("Resource Tick", "no-icon", pchar, RestrictedByGcd::No, 0.0, ResourceType::Mana, 0),
      resource(resource)
{}

void ResourceTick::spell_effect() {
    check(false, "Not implemented");
}

void ResourceTick::perform_periodic() {
    resource->tick_resource();
}
