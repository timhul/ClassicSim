#pragma once

#include <QAbstractListModel>
#include <QJsonObject>

struct TemplateCharacterInfo {
    TemplateCharacterInfo(const QString& title, const QString& class_name, const QString& color, const QJsonObject& setup) :
        title(title), class_name(class_name), color(color), setup(setup) {}

    const QString title;
    const QString class_name;
    const QString color;
    const QJsonObject setup;
};

class TemplateCharacterModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum TemplateCharacterRoles
    {
        Title = Qt::UserRole + 1,
        Color,
    };

    TemplateCharacterModel(QObject* parent = nullptr);
    ~TemplateCharacterModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    TemplateCharacterInfo* template_char_info(const QString& title) const;

private:
    QHash<int, QByteArray> roleNames() const;
    QVector<TemplateCharacterInfo*> template_characters;
};
