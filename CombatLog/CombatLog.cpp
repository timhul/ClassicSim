
#include "CombatLog.h"
#include <QDebug>

void CombatLog::add_entry(const QString& entry) {
    combatlog.append(entry);
}

void CombatLog::dump() {
    for (const auto & i : combatlog) {
        qDebug() << i;
    }
}
