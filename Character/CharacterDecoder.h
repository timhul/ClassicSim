#pragma once

#include <QJsonObject>
#include <QVariantList>
#include <QVector>

class Character;
class Item;
class Rotation;

class CharacterDecoder {
public:
    CharacterDecoder();
    CharacterDecoder(const QString& setup_string);
    CharacterDecoder(const QJsonObject& setup_object);

    static const bool MANDATORY = true;

    QString get_value(const QString& key, const bool mandatory = false);
    QVector<QPair<QString, QString>> get_key_val_pairs(const QString& key);
    QVector<QString> get_vector_values(const QString& key);

    void dump();

private:
    QJsonObject setup;
};
