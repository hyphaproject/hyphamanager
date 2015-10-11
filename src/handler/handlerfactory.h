#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

#include <QtCore/QObject>
#include "hyphahandler.h"
#include "../settings/handlersettings.h"

class Instance;

namespace hypha{
namespace handler{

class HandlerFactory : public QObject
{
    Q_OBJECT
public:
    explicit HandlerFactory(Instance * instance, QObject *parent = 0);
    ~HandlerFactory();

signals:

public slots:
public:
    HyphaHandler *loadHandler(QString id, QObject *parent);

    void setId(QString id);
    void setHost(QString host);
    void setConfig(QString config);

private:

    QString id;
    QString host;
    QString config;
    HyphaHandler *create();

    Instance *instance;

};
}
}

#endif // HANDLERFACTORY_H
