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
	char dot;
	long int time = 0;
	long int pkt_time = 0;
	long int pktID = 0;
	unsigned short int pkt_src_ip[4];
	unsigned long int pkt_src_port;
	unsigned short int pkt_dst_ip[4];
	unsigned long int pkt_dst_port;
	unsigned long int pkt_priority;

	while (std::getline(infile, line))
		{
			stringstream line_ss(line);
			line_ss >> pktID;
			line_ss >> pkt_time;
			line_ss >> pkt_src_ip[0] >> dot >> pkt_src_ip[1] >> dot >>
				pkt_src_ip[2] >> dot >> pkt_src_ip[3];
			line_ss >> pkt_src_port;
			line_ss >> pkt_dst_ip[0] >> dot >> pkt_dst_ip[1] >> dot >>
				pkt_dst_ip[2] >> dot >> pkt_dst_ip[3];
			line_ss >> pkt_dst_port;


			++line_counter;

		}


	cout << "Read " << line_counter << " lines" << endl;
	return 0;
}
