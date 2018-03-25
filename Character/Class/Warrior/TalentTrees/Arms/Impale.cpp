
#include "Impale.h"
#include <QDebug>

Impale::Impale() :
    Talent("Impale", "4MR", "Assets/warrior/arms/tier4/Ability_searingarrow.png", 2)
{
    QString base_str = "Increases the critical strike damage bonus of your abilities in Battle, Defensive, and Berserker stance by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

Impale::~Impale() {

}
