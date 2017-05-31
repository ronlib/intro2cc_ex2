#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "Flow.h"
#include "FlowVector.h"
#include "PacketReader.h"


using namespace std;

int main(int argc, char *argv[])
{
	stringstream ss;
	ss << argv[4] << ' ' << argv[5];

	std::string scheduler(argv[1]), input_file_path(argv[2]), output_file_path(argv[3]);
	int default_weight = 0, quantum = 0;

	ss >> default_weight;
	ss >> quantum;

	FlowVector fv = FlowVector();
	PacketReader pr = PacketReader(input_file_path, fv, default_weight);

	bool res = pr.read_until(7);

	return 0;
}
