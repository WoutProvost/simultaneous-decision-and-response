#ifndef APPLICATION_H
#define APPLICATION_H

#include "MainWindow.h"
#include <iostream>
#include <getopt.h>

// Methods
int main(int argc, char **argv);
void parseOptions(int argc, char **argv);
void printError(QString message);

#endif