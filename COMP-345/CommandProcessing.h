//
// Created by Administrator on 2023/3/17.
//
#include <vector>
#include <fstream>
#include <sstream>
#include "LoggingObserver.h"
using namespace std;

#ifndef A2_COMMANDPROCESSING_H
#define A2_COMMANDPROCESSING_H

class Command : public Subject, public ILoggable
{
private:
    string command;
    string effect;
public:
    Command();
    explicit Command(string);
    explicit Command(const Command*);
    ~Command();
    string getCommandName();
    string getEffect();
    void saveEffect(string); //set effect
    string stringToLog(const std::string& output);
};


class CommandProcessor : public Subject, public ILoggable
{
private:
    vector<Command> commandList;
    void saveCommand(string); //store commands
public:
    CommandProcessor();
    explicit CommandProcessor(const CommandProcessor*);
    ~CommandProcessor();
    virtual string readCommand(); //ask user input wanted command
    Command getCommand(); //return Command obj to game engine and player
    bool validate(string);
    void traverseCommands();
    void traverseCommandsEffects();
    string nextState(string);
    /*Return a vector, splitting the most recent command based on command and parameter*/
    vector<string> commandSplit();
    string stringToLog(const std::string& output);
};

class FileLineReader
{
private:
    string fileName;
    ifstream* inputFile;
public:
    FileLineReader();
    //FileLineReader(const FileLineReader*);
    ~FileLineReader();
    string readLineFromFile(ifstream&);
    string readLineFromFile();
    void setInStream(ifstream*);
    ifstream* getInStream();
};

class FileCommandProcessorAdapter : public CommandProcessor{
private:
    FileLineReader* flr;

public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader *flrp);
    void setFileLineReader(FileLineReader*);
    string readCommand() override;
};

#endif //A2_COMMANDPROCESSING_H
