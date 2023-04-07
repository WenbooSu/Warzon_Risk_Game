#include "LoggingObserver.h"

void Subject::addObserver(Observer* obs) {
    vecObs.push_back(obs);
}

void Subject::removeObserver(Observer* obs) {
    auto vecRemove = std::find(vecObs.begin(), vecObs.end(), obs);
    if (vecRemove != vecObs.end()) {
        vecObs.erase(vecRemove);
    }
}

void Subject::notify(const std::string& output) {

    for (auto obs : vecObs) {
        obs->update(output);
    }
}

ILoggable::ILoggable(Subject* subject) : target(subject) {
    target->addObserver(this);
}

ILoggable::ILoggable(){
    
};

void ILoggable::update(const std::string& output) {
    std::fstream toFile(this->filePath, std::ios_base::app);
    toFile << output << std::endl;
    toFile.close();
}
std::string stringToLog(const std::string& output) {
    return "changes are " + output;
}
