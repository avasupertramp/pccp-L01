// PCCP_L01.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include <time.h>
#include <thread>
#include "Directories.h"
using namespace std;


void printHelp() {
	cout << "help:" << endl;
	cout << "TODO implement" << endl;
}


int main(int argc, char* argv[])
{
	int depth = 0;
	int maxThreads = 0;
	bool printProcesTime = false;
	bool extendedOutput = false;
	bool waitBeforeTerminate = false;
	vector<string> path;
	vector<string> filter;
	clock_t processTime;

	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();	//get max supported threads of the machine


	if (argc < 2) {
		cout << "To less arguemnts" << endl;
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		try {
		string argument = argv[i];
			if (argument == "-r") {
				try {
					depth = stoi(argv[i + 1]);
					if (depth < 0) {
						fprintf(stderr, "Error: folder depth must be > 0");
					}
					i++;
				}
				catch (exception e) {
					depth = -2;		//search in all subdirectories
				}
			}else if(argument == "-f") {
				filter.push_back(argv[i + 1]);
				i++;
			}else if (argument == "-t") {
				maxThreads = stoi(argv[i + 1]);
				if (depth <= 0) {
					fprintf(stderr, "Error: there must be at least 1 Thread");
				}
				i++;
			}else if (argument == "-s") {
				path.push_back(argv[i + 1]);
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
				if (i == (argc-1)) {
					path.push_back(argument);
				}
				else {
					cout << "wrong argument: " << argument << endl;
				}
				
			}
		}
		catch (exception e) {
			fprintf(stderr, "Error: in interpreting arguments %s \n",argv[i]);
		}

		}
	if (printProcesTime) {
		processTime = clock();
	}


	Directories temp;
	temp.generateFileTree(path,filter,depth);


	if (printProcesTime) {
		processTime = clock() - processTime;
		double time_taken = ((double)processTime) / CLOCKS_PER_SEC; // in seconds
		printf("\n The process took %f seconds to execute \n\n", time_taken);
	}
	if (waitBeforeTerminate) {
		cout << "Press any key to exit...";
		_getch();
	}

	return 0;
}

