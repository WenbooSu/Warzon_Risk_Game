//
// Created by Administrator on 2023/3/17.
//
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#ifndef A2_COMMANDPROCESSING_H
#define A2_COMMANDPROCESSING_H

class Command
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
};


class CommandProcessor
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
