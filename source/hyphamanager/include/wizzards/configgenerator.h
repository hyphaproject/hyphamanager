#ifndef CONFIGGENERATOR_H
#define CONFIGGENERATOR_H

#include <string>

class ConfigGenerator {
  public:
    ConfigGenerator();

    // Database
    std::string dbDatabase = "hypha";
    std::string dbDriver = "QMYSQL";
    std::string dbHost = "localhost";
    std::string dbPassword = "password";
    std::string dbUsername = "hypha";

    // User Database
    std::string udbAttributeDevices = "deviceids";
    std::string udbAttributeFirstname = "firstname";
    std::string udbAttributeLastname = "lastname";
    std::string udbAttributeMail = "mail";
    std::string udbAttributeUsername = "username";
    std::string udbDatabase = "hypha";
    std::string udbDriver = "QMYSQL";
    std::string udbHost = "localhost";
    std::string udbPassword = "password";
    std::string udbTable = "user";
    std::string udbUsername = "hypha";

    void generateConfigFile(std::string filename);

};

#endif // CONFIGGENERATOR_H
