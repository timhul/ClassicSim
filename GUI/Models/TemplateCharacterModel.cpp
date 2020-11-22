#include "TemplateCharacterModel.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "NumberCruncher.h"
#include "SimSettings.h"

TemplateCharacterModel::TemplateCharacterModel(QObject* parent) : QAbstractListModel(parent) {
    QFile file("template_characters.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open template_characters.json";
    } else {
        QJsonArray template_characters_in_file = QJsonDocument::fromJson(file.readAll()).array();

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        for (const auto& template_char_value : template_characters_in_file) {
            QJsonObject template_char = template_char_value.toObject();
            QJsonObject setup_object = template_char["setup"].toObject();

            const auto template_char_info = new TemplateCharacterInfo(template_char["title"].toString(), setup_object["CLASS"].toString(),
                                                                      template_char["color"].toString(), setup_object);
            this->template_characters.push_back(template_char_info);
        }

        endInsertRows();
    }

    file.close();
}

TemplateCharacterModel::~TemplateCharacterModel() {
    for (const auto& template_char : template_characters)
        delete template_char;
}

int TemplateCharacterModel::rowCount(const QModelIndex&) const {
    return template_characters.count();
}

QVariant TemplateCharacterModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= template_characters.count())
        return QVariant();

    if (role == TemplateCharacterRoles::Title)
        return template_characters[index.row()]->title;
    if (role == TemplateCharacterRoles::Color)
        return template_characters[index.row()]->color;

    return QVariant();
}

TemplateCharacterInfo* TemplateCharacterModel::template_char_info(const QString& title) const {
    for (const auto& template_char : template_characters) {
        if (template_char->title == title)
            return template_char;
    }

    return nullptr;
}

QHash<int, QByteArray> TemplateCharacterModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Title] = "_title";
    roles[Color] = "_color";
    return roles;
}
