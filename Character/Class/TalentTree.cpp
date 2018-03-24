
#include "TalentTree.h"
#include "Talent.h"
#include <QDebug>

TalentTree::TalentTree(const QString &name_, QObject *parent) :
    QObject(parent),
    name(name_),
    talents(QMap<QString, Talent*>())
{}

TalentTree::~TalentTree() {
    for (auto it : talents.keys()) {
        delete talents.value(it);
    }

    talents.clear();
}

QString TalentTree::get_name() const {
    return name;
}

void TalentTree::leftClickedPosition(const int tier, const QString position) {
    qDebug() << "Clicked tier" << tier << "position" << position;
}

void TalentTree::add_talents(const QMap<QString, Talent*> &new_talents) {
    for (auto it : new_talents.toStdMap()) {
        assert(!talents.contains(it.first));
        talents.insert(it.first, it.second);
    }
}
