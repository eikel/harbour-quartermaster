#ifndef ENTITIESSERVICE_H
#define ENTITIESSERVICE_H

#include <QObject>

#include "src/entities/climate.h"
#include "src/entities/group.h"
#include "src/entities/light.h"
#include "src/models/entitiesmodel.h"
#include "src/models/entitytypesmodel.h"

class EntitiesService : public QObject
{
    Q_OBJECT

public:
    explicit EntitiesService(QObject *parent = nullptr);

    // members
    Q_INVOKABLE EntitiesModel *entitiesModel();
    Q_INVOKABLE EntityTypesModel *entityTypesModel();

    // functions
    Q_INVOKABLE QString getEntityIcon(quint8 entityType) const;

signals:
    void homeassistantVersionAvailable(const QString &version);

public slots:
    void onRequestDataFinished(quint64 requestType, const QJsonDocument &payload);
    void updateEntity(const QJsonObject &obj);

private:
    Entity::EntityType getEntityType(const QString &entityId) const;
    EntityTypeItem getEntityTypeItem(const Entity::EntityType &entityType, quint16 count) const;
    void parseStates(const QJsonArray &arr);

    EntitiesModel *m_entitiesModel{new EntitiesModel(this)};
    EntityTypesModel *m_entityTypesModel{new EntityTypesModel(this)};
};

#endif // ENTITIESSERVICE_H
