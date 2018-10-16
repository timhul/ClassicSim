#ifndef ENCHANTPROC_H
#define ENCHANTPROC_H

#include <QObject>

#include "Enchant.h"
#include "EnchantName.h"

class Character;
class Proc;

QString get_name_from_enum_weapon(EnchantName::Name);
QString get_effect_from_enum_weapon(EnchantName::Name);

class EnchantProc : public Enchant {
public:
    EnchantProc(EnchantName::Name enchant, Character* pchar, const int slot);
    ~EnchantProc() override;

private:
    Character* pchar;
    Proc* proc;
};

#endif // ENCHANTPROC_H
