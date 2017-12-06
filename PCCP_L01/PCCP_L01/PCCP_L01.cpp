// PCCP_L01.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
using namespace std;


void printHelp() {
	cout << "help:" << endl;
	cout << "TODO implement" << endl;
}


int main(int argc, char* argv[])
{
	int depth = 0;
	int maxThreads = 0;
	string filter;
	bool printProcesTime = false;
	bool extendedOutput = false;
	bool waitBeforeTerminate = false;


	if (argc < 2) {
		cout << "To less arguemnts" << endl;
		return 0;
	}

	string path = argv[argc - 1];
	for (int i = 1; i < (argc-1); i++) {
		try {
		string argument = argv[i];
			if (argument == "-r") {
				depth = stoi(argv[i + 1]);
				i++;
			}else if(argument == "-f") {
				filter = argv[i + 1];
				i++;
			}else if (argument == "-t") {
				maxThreads = stoi(argv[i + 1]);
				i++;
			}else if (argument == "-h") {
				printHelp();
				break;
			}else if (argument == "-p") {
				printProcesTime = true;
			}else if (argument == "-v") {
				extendedOutput = true;
			}else if (argument == "-w") {
				waitBeforeTerminate = true;
			}
			else {
				cout << "false argument" << endl;
			}
		}
		catch (exception e) {
			fprintf(stderr, "Error in interpreting arguments %s",argv[i]);
		}

		}
	return 0;
}

