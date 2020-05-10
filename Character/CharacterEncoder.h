#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>

class Character;
class Item;

class CharacterEncoder {
public:
    CharacterEncoder(Character* pchar = nullptr);

    void set_character(Character* pchar);
    QJsonDocument get_current_setup_json_object();
    QString get_current_setup_string();

private:
    Character* pchar;

    QJsonObject pchar_as_json;

    void new_element();
    void new_list_element();
    void add_vector_values_only(const QString& name, const QVector<QString>& vec);
    void add_vector(QVector<QPair<QString, QVector<QPair<QString, QString>>>>& vec);
    void add_vector(QVector<QPair<QString, QVector<QString>>>&);
    void add_item(const QString& key, Item* item);
    void key_val(const QString& key, const QString& value);
    void key_val_list(const QString& key, const QString& value);

    void add_enchants();
    void add_affixes();
};
