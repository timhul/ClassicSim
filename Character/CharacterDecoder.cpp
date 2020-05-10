#include "CharacterDecoder.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#include "Utils/Check.h"

CharacterDecoder::CharacterDecoder() {}

CharacterDecoder::CharacterDecoder(const QJsonObject& setup_object) : setup(setup_object) {}

CharacterDecoder::CharacterDecoder(const QString& setup_string) : setup(QJsonDocument::fromJson(setup_string.toUtf8()).object()) {}

QString CharacterDecoder::get_value(const QString& key, const bool mandatory) {
    if (setup.contains(key))
        return setup.take(key).toString();

    if (mandatory)
        check(false, QString("Missing key '%1' in CharacterDecoder::get_value").arg(key).toStdString());

    return "";
}

QVector<QPair<QString, QString>> CharacterDecoder::get_key_val_pairs(const QString& key) {
    if (!setup.contains(key) || !setup[key].isArray())
        return QVector<QPair<QString, QString>>();

    const QJsonArray array = setup.take(key).toArray();

    QVector<QPair<QString, QString>> key_val_pairs;
    for (const auto& element : array) {
        for (const auto& k : element.toObject().keys()) {
            key_val_pairs.push_back(QPair<QString, QString>({k, element.toObject()[k].toString()}));
        }
    }

    return key_val_pairs;
}

QVector<QString> CharacterDecoder::get_vector_values(const QString& key) {
    if (!setup.contains(key) || !setup[key].isArray())
        return QVector<QString>();

    const QJsonArray array = setup.take(key).toArray();

    QVector<QString> vec;
    for (const auto& element : array)
        vec.push_back(element.toString());

    return vec;
}
