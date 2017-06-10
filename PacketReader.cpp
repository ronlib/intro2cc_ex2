#include <sstream>
#include <iostream>
#include <istream>
#include <ios>
#include "PacketReader.h"

using namespace std;

PacketReader::PacketReader(const std::string& file_path, FlowVector& fv,
													 unsigned long int default_weight)
	: last_read_time_(0),
		fv_(fv),
		infile_(file_path),
		default_weight_(default_weight),
		eof_(false)
{
	if (this->infile_.fail())
		{
			throw ios_base::failure("Unable to open input file");
		}
}


bool PacketReader::read_until(unsigned long int time)
{
	std::string line;
	long unsigned int pkt_time = 0;
	long unsigned int pktID = 0;
	unsigned short int pkt_src_ip[4];
	unsigned long int pkt_src_port;
	unsigned short int pkt_dst_ip[4];
	unsigned long int pkt_dst_port;
	unsigned short int pkt_length;
	unsigned long int pkt_weight;

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

					this->eof_ = eof = true;
					break;
				}

			stringstream line_ss(line);
			this->parse_line(line_ss, pkt_time, pktID, pkt_src_ip, pkt_src_port,
											 pkt_dst_ip, pkt_dst_port, pkt_length);

			if (pkt_time > time)
				{
					break;
				}
			// All should work up here
			Flow flow = Flow(pkt_src_ip, pkt_src_port, pkt_dst_ip, pkt_dst_port);
			std::vector<Flow>::iterator found_flow = this->fv_.find_flow(flow);
			if (found_flow == this->fv_.end())
				{
					// This is a new flow
					line_ss >> pkt_weight;
					if (!line_ss.fail())
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
					return true;
				}
		}

	return false;
}

bool PacketReader::has_reached_eof()
{
	return this->eof_;
}

unsigned long int PacketReader::next_packet_time()
{
	unsigned long int pkt_time;
	unsigned long int pktID;
	unsigned short int pkt_src_ip[4];
	unsigned long int pkt_src_port;
	unsigned short int pkt_dst_ip[4];
	unsigned long int pkt_dst_port;
	unsigned short int pkt_length;

	streampos prev_line_pos;
	string line;
	prev_line_pos = this->infile_.tellg();
	std::getline(this->infile_, line);
	if (this->infile_.eof())
		{

			this->eof_ = true;
			throw runtime_error("Reached end of file");
		}

	this->infile_.seekg(prev_line_pos);

	stringstream line_ss(line);
	this->parse_line(line_ss, pkt_time, pktID, pkt_src_ip, pkt_src_port,
									 pkt_dst_ip, pkt_dst_port, pkt_length);

	return pkt_time;
}

void PacketReader::parse_line(std::stringstream& line_ss,
															unsigned long int& pkt_time,
															unsigned long int& pktID,
															unsigned short int pkt_src_ip[4],
															unsigned long int& pkt_src_port,
															unsigned short int pkt_dst_ip[4],
															unsigned long int& pkt_dst_port,
															unsigned short int& pkt_length)
{
	char dot;
	line_ss >> pktID;
	line_ss >> pkt_time;
	line_ss >> pkt_src_ip[0] >> dot >> pkt_src_ip[1] >> dot >>
		pkt_src_ip[2] >> dot >> pkt_src_ip[3];
	line_ss >> pkt_src_port;
	line_ss >> pkt_dst_ip[0] >> dot >> pkt_dst_ip[1] >> dot >>
		pkt_dst_ip[2] >> dot >> pkt_dst_ip[3];
	line_ss >> pkt_dst_port;
	line_ss >> pkt_length;
}
