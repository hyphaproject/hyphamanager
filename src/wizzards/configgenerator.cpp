#include <iostream>
#include <fstream>

#include "configgenerator.h"


ConfigGenerator::ConfigGenerator() {
}

void ConfigGenerator::generateIniFile(std::string filename) {
    std::ofstream file (filename);
    if (file.is_open()) {
        file << "[database]" << std::endl;
        file << "database=" << dbDatabase << std::endl;
        file << "driver=" << dbDriver << std::endl;
        file << "host=" << dbHost << std::endl;
        file << "password=" << dbPassword << std::endl;
        file << "username=" << dbUsername << std::endl;
        file << std::endl;
        file << "[userdatabase]" << std::endl;
        file << "attrDevices=" << udbAttributeDevices << std::endl;
        file << "attrFirstname=" << udbAttributeFirstname << std::endl;
        file << "attrLastname=" << udbAttributeLastname << std::endl;
        file << "attrMail=" << udbAttributeMail << std::endl;
        file << "attrUsername=" << udbAttributeUsername << std::endl;
        file << "database=" << udbDatabase << std::endl;
        file << "driver=" << udbDriver << std::endl;
        file << "host=" << udbHost << std::endl;
        file << "password=" << udbPassword << std::endl;
        file << "table=" << udbTable << std::endl;
        file << "username=" << udbUsername << std::endl;
        file.close();
    }
}
