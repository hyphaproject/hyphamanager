#ifndef HYPHAPLUGIN_H
#define HYPHAPLUGIN_H

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QThread>
#include "hyphabaseplugin.h"
#include "../database/database.h"

namespace hypha{
namespace plugin{

class HyphaPlugin: public HyphaBasePlugin{
public:
    virtual QString getName(){ return "hyphaplugin"; }
    virtual QString getTitle() { return "HyphaPlugin"; }
    virtual QString getVersion() { return "1.0"; }
    virtual QString getDescription() { return "Hypha plugin";}
    virtual HyphaPlugin * getInstance(QString id, QObject *parent) = 0;
    void setDatabase(Database * database){ this->database = database; }
protected:
    Database * database;
};
}
}

#define HyphaPluginIID "Hypha.Plugin/1.0"
Q_DECLARE_INTERFACE(hypha::plugin::HyphaPlugin, HyphaPluginIID)

#endif // HYPHAPLUGIN_H
