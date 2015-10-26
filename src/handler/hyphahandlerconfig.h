#ifndef HYPHAHANDLERCONFIG_H
#define HYPHAHANDLERCONFIG_H

#include <QtWidgets/QWidget>
#include <hypha/handler/hyphahandler.h>

using namespace hypha::plugin;

namespace hypha {
namespace database {
class Database;
class UserDatabase;
}

namespace handler {

class HyphaHandlerConfig: public HyphaHandler {
  public:

    void doWork() {}
    void receiveMessage(std::string message) {}
    std::string communicate(std::string message) {
        return "";
    }
    virtual HyphaHandlerConfig *getInstance(std::string id) = 0;
    std::string getHost() {
        return host;
    }
    void setHost(std::string host) {
        this->host = host;
    }
    void setUserDatabase(hypha::database::UserDatabase *userDatabase) {
        this->userDatabase = userDatabase;
    }
    void setDatabase(hypha::database::Database *database) {
        this->database = database;
    }
    virtual QWidget *widget() = 0;

  protected:
    std::string host;
    hypha::database::Database *database;
    hypha::database::UserDatabase *userDatabase;
};
}
}

#endif // HYPHAHANDLERCONFIG_H
