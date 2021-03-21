#ifndef ENTITIESSERVICE_H
#define ENTITIESSERVICE_H

#include "service.h"

#include "src/entities/climate.h"
#include "src/entities/group.h"
#include "src/entities/light.h"
#include "src/models/entitiesmodel.h"
#include "src/models/entitytypesmodel.h"

class EntitiesService : public Service
{
    Q_OBJECT

public:
    explicit EntitiesService(QObject *parent = nullptr);

    // members
    Q_INVOKABLE EntitiesModel *entitiesModel();
    Q_INVOKABLE EntityTypesModel *entityTypesModel();

    // functions
    Q_INVOKABLE void callService(const QString &domain,
                                 const QString &service,
                                 const QString &entityId);
    Q_INVOKABLE void callService(const QString &domain,
                                 const QString &service,
                                 const QJsonObject &payload = QJsonObject());
    Q_INVOKABLE QString getEntityIcon(quint8 entityType) const;
    Q_INVOKABLE void getEntityState(const QString &entityId);
    Q_INVOKABLE void refresh();

signals:
    void homeassistantVersionAvailable(const QString &version);

public slots:
    void updateEntity(const QJsonObject &obj);

private:
    Entity::EntityType getEntityType(const QString &entityId) const;
    EntityTypeItem getEntityTypeItem(const Entity::EntityType &entityType, quint16 count) const;
    void parseStates(const QJsonArray &arr);

    EntitiesModel *m_entitiesModel{new EntitiesModel(this)};
    EntityTypesModel *m_entityTypesModel{new EntityTypesModel(this)};

    // Service interface
public:
    void initialize() override;

public slots:
    void onRequestFinished(quint8 requestType, const QJsonDocument &data) override;
};

#endif // ENTITIESSERVICE_H
