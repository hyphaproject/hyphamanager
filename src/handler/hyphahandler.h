#ifndef HYPHAHANDLER_H
#define HYPHAHANDLER_H

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtCore/QThread>

#include "../plugin/hyphabaseplugin.h"

using namespace hypha::plugin;

class Database;
class UserDatabase;

namespace hypha{
namespace handler{

class HyphaHandler: public HyphaBasePlugin{
public:

    virtual QString getName(){ return "hyphahandler"; }
    virtual QString getTitle() { return "HyphaHandler"; }
    virtual QString getVersion() { return "1.0"; }
    virtual QString getDescription() { return "Hypha handler plugin";}
    virtual HyphaHandler * getInstance(QString id, QObject *parent) = 0;
    QString getHost(){ return host; }
    void setHost(QString host){ this->host = host; }
    void setUserDatabase(UserDatabase * userDatabase){ this->userDatabase = userDatabase; }
    void setDatabase(Database * database){ this->database = database; }

protected:
    QString host;
    Database * database;
    UserDatabase * userDatabase;
};
}
}


#define HyphaHandlerIID "Hypha.Handler/1.0"
Q_DECLARE_INTERFACE(hypha::handler::HyphaHandler, HyphaHandlerIID)

#endif // HYPHAHANDLER_H
