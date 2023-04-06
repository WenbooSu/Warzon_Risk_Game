//
// Created by Administrator on 2023/3/17.
//

#include "CommandProcessing.h"
#include <iostream>
#include <utility>
#include <vector>


Command::Command() {
    this->command = "null";
    this->effect = "null";
}


Command::Command(string command) {
    this->command = std::move(command);
}


Command::Command(const Command * command) {
    this->command = command->command;
    this->effect = command->effect;
}


string Command::getCommandName() {
    return this->command;
}


string Command::getEffect() {
    return this->effect;
}


void Command::saveEffect(string effect) {
    this->effect = std::move(effect);
}


Command::~Command() {


}


void CommandProcessor::saveCommand(string commandStr) {
    Command cmd(commandStr);
    commandList.push_back(cmd);
}


CommandProcessor::CommandProcessor() = default;


CommandProcessor::CommandProcessor(const CommandProcessor * cpp) {
    this->commandList = cpp->commandList;
}


CommandProcessor::~CommandProcessor() {

}


string CommandProcessor::readCommand() {
    string commandStr;
    cout << "ENTER YOUR COMMAND: ";
    getline(cin, commandStr);
    cout << endl;
    if(commandStr.substr(0,7) == "loadmap" || commandStr == "validatemap" ||
       commandStr.substr(0,9) == "addplayer" || commandStr == "gamestart" || commandStr == "replay"
       || commandStr == "quit")
    {
        return commandStr;
    }
    else
    {
        return "";
    }
}


Command CommandProcessor::getCommand() {
    string str = this->readCommand();
    this->saveCommand(str);
    return this->commandList.back();
}



bool CommandProcessor::validate(string state) {
    string command = this->commandList.back().getCommandName(); //return the latest command string
    if (command.substr(0,7) == "loadmap" && (state == "Start" || state == "Map Loaded"))
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if(command == "validatemap" && state == "Map Loaded")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if(command.substr(0,9) == "addplayer" && (state == "Map Validated" || state == "Players Added"))
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if(command == "gamestart" && state == "Players Added")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if(command == "replay" && state == "Win")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if(command == "issueorder" && state == "Assign Reinforcement")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if((command == "issueorder" || command == "endissueorders") && state == "Issue Orders")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if((command == "execorder" || command == "endexecorders" || command == "win") && state == "Execute Orders")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else if ((command == "quit" || command == "replay") && state == "Win")
    {
        this->commandList.back().saveEffect("Command Validated");
        return true;
    }
    else
    {
        this->commandList.back().saveEffect("ERROR: Invalidated Command");
        return false;
    }
}

string CommandProcessor::nextState(string state) {
    string command = this->commandList.back().getCommandName(); //return the latest command string
    if(command.substr(0,7) == "loadmap" && (state == "Start" || state == "Map Loaded"))
    {
        return "Map Loaded";
    }
    if(command == "validatemap" && state == "Map Loaded")
    {
        return "Map Validated";
    }
    if(command.substr(0,9) == "addplayer" && (state == "Map Validated" || state == "Players Added"))
    {
        return "Players Added";
    }
    if(command == "gamestart" && state == "Players Added")
    {
        return "Assign Reinforcement";
    }
    if(command == "replay" && state == "Win")
    {
        return "Start";
    }
    if (command == "quit" && state == "Win")
    {
        cout<<"Terminating program.";
        exit(0);
    }

}

vector<string> CommandProcessor::commandSplit() {
    string fullCommand = this->commandList.back().getCommandName();
    stringstream stream(fullCommand);
    string s;
    int numInputs = 2;
    vector<string> values;
    for (int i = 0; i < numInputs; i++) {
        getline(stream, s, ' ');
        values.push_back(s);
    }
    return values;
}

void CommandProcessor::traverseCommands() {
    cout<< "Command Records:"<< endl;
    for (int i=0; i<commandList.size(); i++)
    {
        cout<<commandList[i].getCommandName()<<endl;
    }
}

void CommandProcessor::traverseCommandsEffects() {
    cout<< "Command Effects: "<<endl;
    for(int i=0; i<commandList.size(); i++)
    {
        cout<<commandList[i].getEffect()<<endl;
    }
}

FileLineReader::FileLineReader() {
    this->inputFile = nullptr;
    this->fileName="";
}

/*FileLineReader::FileLineReader(const FileLineReader *flr) {
    this->inputFile = flr->inputFile;
    this->fileName = flr->fileName;
}*/

string FileLineReader::readLineFromFile(ifstream& file) {
    string line;
    getline(file, line);
    return line;
}

void FileLineReader::setInStream(ifstream* inFile) {
    this->inputFile = inFile;
}

ifstream* FileLineReader::getInStream() {
    return this->inputFile;
}

string FileLineReader::readLineFromFile() {
    string line;
    getline(*inputFile, line);
    return line;
}

FileLineReader::~FileLineReader() {
    delete this->inputFile;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader *flrp) {
    this->flr = flrp;
}

string FileCommandProcessorAdapter::readCommand() {
    string command;
    if(flr->getInStream()->eof())
    {
        exit(0);
    }
    command = flr->readLineFromFile();
    return command;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    this->flr = nullptr;
}

void FileCommandProcessorAdapter::setFileLineReader(FileLineReader* flrp) {
    this->flr = flrp;
}


