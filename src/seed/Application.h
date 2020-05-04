#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <getopt.h>

using namespace std;

// General variables and constants
string command;
string inputFileName;
int amount = 10;
unsigned int srandSeed = 1;

// Methods
int main(int argc, char **argv);
void parseOptions(int argc, char **argv);
void printError(string message);

#endif