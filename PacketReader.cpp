#include <sstream>
#include <iostream>
#include <istream>
#include <ios>
#include "PacketReader.h"

using namespace std;

PacketReader::PacketReader(const std::string& file_path, FlowVector& fv,
													 unsigned long int default_weight)
	: last_read_time_(0),
		default_weight_(default_weight),
		fv_(fv),
		infile_(file_path)
{
	if (this->infile_.fail())
		{
			throw ios_base::failure("Unable to open input file");
		}
}


bool PacketReader::read_until(unsigned long int time)
{
	std::string line;
	int line_counter = 0;
	char dot;
	long int pkt_time = 0;
	long int pktID = 0;
	unsigned short int pkt_src_ip[4];
	unsigned long int pkt_src_port;
	unsigned short int pkt_dst_ip[4];
	unsigned long int pkt_dst_port;
	unsigned long int pkt_length;
	unsigned long int pkt_weight;
	unsigned long int current_time = 0;

	streampos prev_line_pos;
	bool error = false, eof = false;

	do
		{
			prev_line_pos = this->infile_.tellg();

			std::getline(this->infile_, line);
			if (this->infile_.bad() || this->infile_.fail())
				{
					error = true;
					break;
				}

			if (this->infile_.eof())
				{
					eof = true;
					break;
				}
			stringstream line_ss(line);
			line_ss >> pktID;
			line_ss >> pkt_time;
			line_ss >> pkt_src_ip[0] >> dot >> pkt_src_ip[1] >> dot >>
				pkt_src_ip[2] >> dot >> pkt_src_ip[3];
			line_ss >> pkt_src_port;
			line_ss >> pkt_dst_ip[0] >> dot >> pkt_dst_ip[1] >> dot >>
				pkt_dst_ip[2] >> dot >> pkt_dst_ip[3];
			line_ss >> pkt_dst_port;
			line_ss >> pkt_length;
			// All should work up here
			Flow flow = Flow(pkt_src_ip, pkt_src_port, pkt_dst_ip, pkt_dst_port);
			std::vector<Flow>::iterator found_flow = this->fv_.find_flow(flow);
			if (found_flow == this->fv_.end())
				{
					// This is a new flow
					line_ss >> pkt_weight;
					if (line_ss.good())
						{
							flow.weight = pkt_weight;
						}
					else
						{
							flow.weight = this->default_weight_;
						}
					flow.state.packetlist.push_back(Packet(pkt_length, pktID));
					this->fv_.add_flow(flow);
				}
			else
				{
					(*found_flow).state.packetlist.push_back(Packet(pkt_length, pktID));
				}

		} while (pkt_time <= time);

	if (!error)
		{
			if (!eof)
				{
					this->infile_.seekg(prev_line_pos);
				}
			return true;
		}

	return false;
}
