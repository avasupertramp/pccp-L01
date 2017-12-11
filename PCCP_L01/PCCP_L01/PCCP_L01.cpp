// PCCP_L01.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include <time.h>
#include <thread>
#include <boost\filesystem\path.hpp>
#include "Directories.h"
using namespace std;


void printHelp() {
	cout << "help:" << endl;
	cout << "TODO implement" << endl;
}


int main(int argc, char* argv[])
{
	int depth = 0;
	bool printProcesTime = false;
	bool extendedOutput = false;
	bool waitBeforeTerminate = false;
	unsigned int maxThreads = 0;
	uintmax_t resultOnes=0;
	uintmax_t resultZeros = 0;
	uintmax_t sumSize = 0;
	vector<string> path;
	vector<string> filter;
	clock_t processTime;

	if (argc < 2) {
		printHelp();
		return 0;
	}

	//handle input arguments
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

	//calc max Threads
	unsigned concurentThreadsSupported = thread::hardware_concurrency();	//get max supported threads of the machine
	if (maxThreads == 0 || maxThreads > concurentThreadsSupported) {
		maxThreads = concurentThreadsSupported;
	}

	//start measuring process time if wanted
	if (printProcesTime) {
		processTime = clock();
	}

	//place code here to measure the time
	Directories directory(maxThreads, &resultOnes, &sumSize);
	directory.generateFileTree(path, filter, depth);

	//vector <vector<boost::filesystem::path>> subPathes;
	//for (int i = 0; i < maxThreads; i++) {
	//	subPathes.push_back(pathes.begin(),pathes.end());
	//}
	

	//CalculateBits te;
	//te.calcBit(pathes, &resultOnes, &sumSize);

	////start Threads
	//vector<unique_ptr<CalculateBits>> runners;
	//for (size_t i = 0; i < maxThreads; ++i) {
	//	runners.emplace_back(new CalculateBits);
	//}


	//vector<thread> threads;
	//for (const auto& r : runners) {
	//	threads.emplace_back(&CalculateBits::calcBit, r.get(),pathes, &resultZeros, &resultOnes);
	//}

	//for (auto& t : threads) {
	//	t.join();
	//}

	//print counted files
	resultZeros = sumSize * 8 - resultOnes;
	printf("\nCounted Zeros %lu \nCounted Ones %lu\nTotal File size in byte %lu\n",resultZeros, resultOnes, sumSize);

	//print process time
	if (printProcesTime) {
		processTime = clock() - processTime;
		double time_taken = ((double)processTime) / CLOCKS_PER_SEC; // in seconds
		printf("\nThe process took %f seconds to execute \n\n", time_taken);
	}

	//wait for input before exit
	if (waitBeforeTerminate) {
		cout << "Press any key to exit...";
		_getch();
	}

	return 0;
}

