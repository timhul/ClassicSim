#ifndef CHARACTERENCODER_H
#define CHARACTERENCODER_H

#include <QObject>
#include <QVector>

class Character;
class Item;

class CharacterEncoder: public QObject {
    Q_OBJECT

public:
    CharacterEncoder(Character* pchar, QObject* parent = nullptr);

    QString get_current_setup_string();

protected:
private:
    Character* pchar;

    QString pchar_str;
    void new_element();
    void new_list_element();
    void add_vector_values_only(const QString& name, const QVector<QString>& vec);
    void add_vector(QVector<QPair<QString, QVector<QPair<QString, QString>>>> &vec);
    void add_item(const QString& key, Item* item);
    void key_val(const QString& key, const QString& value);
    void key_val_list(const QString& key, const QString& value);
};

#endif // CHARACTERENCODER_H
