#ifndef ENCHANT_H
#define ENCHANT_H

#include <QString>

class Enchant {
public:
    Enchant(const QString& name, const QString& effect);
    virtual ~Enchant();

    QString get_name() const;
    QString get_effect() const;

protected:
    QString name;
    QString effect;
};


#endif // ENCHANT_H
