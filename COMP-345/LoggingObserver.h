#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>

class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& output) = 0;
};

class Subject {
public:
    void addObserver(Observer* obs1);
    void removeObserver(Observer* obs1);
    void notify(const std::string& output);
private:
    std::vector<Observer*> vecObs;

};

class ILoggable : public Observer {
public:
    ILoggable(Subject* subject);
    ILoggable();
    virtual void update(const std::string& output);
    std::string stringToLog(const std::string& output);
    std::string filePath = "gamelog.txt";
private:
    std::string LoggingObserver;
    Subject* target;
};
