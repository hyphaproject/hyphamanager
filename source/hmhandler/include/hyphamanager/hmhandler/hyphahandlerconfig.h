#ifndef HYPHAHANDLERCONFIG_H
#define HYPHAHANDLERCONFIG_H

#include <hypha/handler/hyphahandler.h>
#include <QtWidgets/QWidget>
#include <hyphamanager/hmhandler/hmhandler_api.h>

using namespace hypha::plugin;

namespace hypha {
namespace database {
class Database;
class UserDatabase;
}

namespace handler {

class HMHANDLER_API HyphaHandlerConfig : public HyphaHandler {
 public:
  void doWork() {}
  void receiveMessage(std::string message) { (void)message; }
  std::string communicate(std::string message) {
    (void)message;
    return "";
  }
  const std::string getConfigDescription() { return "{}"; }
  virtual HyphaHandlerConfig *getInstance(std::string id) = 0;
  std::string getHost() { return host; }
  void setHost(std::string host) { this->host = host; }
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

#endif  // HYPHAHANDLERCONFIG_H
