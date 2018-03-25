
#include "ImprovedRend.h"
#include <QDebug>

ImprovedRend::ImprovedRend() :
    Talent("Improved Rend", "1MR", "Assets/warrior/arms/tier1/Ability_gouge.png", 3)
{
    QString base_str = "Increases the bleed damage done by your Rend ability by %1%.";
    initialize_rank_descriptions(base_str, 15, 10);
}

ImprovedRend::~ImprovedRend() {

}
