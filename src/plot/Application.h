#ifndef APPLICATION_H
#define APPLICATION_H

#include "MainWindow.h"
#include <iostream>
#include <getopt.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

// General variables and constants
string fileName;
int maxGraphs = 2;
int experiment = 1;
int maxExperiments = 1;
int gateGrippingRobots = 0;
int temperatureSensingRobots = 0;

// Methods
int main(int argc, char **argv);
void printError(string command, string message);
void parseOptions(int argc, char **argv);

#endif