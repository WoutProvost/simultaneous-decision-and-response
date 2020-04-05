#ifndef APPLICATION_H
#define APPLICATION_H

#include "MainWindow.h"
#include <iostream>
#include <getopt.h>

// General variables and constants
QString command;
QString fileName;
int maxGraphs = 2;
int experiment = 1;
int maxExperiments = 1;
int gateGrippingRobots = 0;
int temperatureSensingRobots = 0;

// Methods
int main(int argc, char **argv);
void parseOptions(int argc, char **argv);
void printError(QString message);

#endif