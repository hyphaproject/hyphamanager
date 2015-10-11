#ifndef HANDLERLOADER_H
#define HANDLERLOADER_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QMutex>
#include <QtCore/QList>
#include <QtCore/QMap>
#include "hyphahandler.h"
#include "../settings/handlersettings.h"

class Instance;

namespace hypha{
namespace handler{
class HandlerLoader : public QObject
{
    Q_OBJECT
public:
    explicit HandlerLoader(Instance * instance, QObject *parent = 0);
    ~HandlerLoader();
    void loadLocalInstances();
    void loadInstances();

    HyphaHandler* getHandler(QString name);
    QList<HyphaHandler *> getHandlers();


    QList<HyphaHandler *> getInstances();
    HyphaHandler *getHandlerInstance(QString id);

signals:

public slots:

private:
    Instance * instance;
    QList<HyphaHandler *> handlers;
    QMap<QString, HyphaHandler *> handlerInstances;
    void loadHandlers(QString dir);

};
}
}

#endif // HANDLERLOADER_H
