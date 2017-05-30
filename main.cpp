#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "Flow.h"
#include "FlowVector.h"


using namespace std;

int main(int argc, char *argv[])
{
	stringstream ss;
	ss << argv[4] << ' ' << argv[5];

	std::string scheculer(argv[1]), input_file_path(argv[2]), output_file_path(argv[3]);
	int default_weight = 0, quantum = 0;

	ss >> default_weight;
	ss >> quantum;

	std::string line;
	std::ifstream infile(input_file_path);
	int line_counter = 0;

	while (std::getline(infile, line))
		{
			++line_counter;
		}


	cout << "Read " << line_counter << " lines" << endl;
	return 0;
}
