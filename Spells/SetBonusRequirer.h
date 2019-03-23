#ifndef SETBONUSREQUIRER_H
#define SETBONUSREQUIRER_H

#include <QSet>
#include <QString>

class SetBonusRequirer {
public:
    SetBonusRequirer(QSet<QString> set_names);
    virtual ~SetBonusRequirer() = default;

    void activate_set_bonus(const QString& set_name, const int num_pieces);
    void deactivate_set_bonus(const QString& set_name, const int num_pieces);

protected:
    const QSet<QString> set_names;

    virtual void activate_set_bonus_effect(const QString& set_name, const int num_pieces) = 0;
    virtual void deactivate_set_bonus_effect(const QString& set_name, const int num_pieces) = 0;
};

#endif // SETBONUSREQUIRER_H
