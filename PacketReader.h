#include <sstream>
#include <fstream>
#include <string>
#include "FlowVector.h"

class PacketReader
{
 public:
	// TODO: Use move semantics for FlowVector
	PacketReader(const std::string& file_path, FlowVector&, unsigned long int default_weight);
	bool read_until(unsigned long int time);
	bool has_reached_eof();
	unsigned long int next_packet_time();


 private:
	void parse_line(std::stringstream& line_ss,
									unsigned long int& pkt_time,
									unsigned long int& pktID,
									unsigned short int pkt_src_ip[4],
									unsigned long int& pkt_src_port,
									unsigned short int pkt_dst_ip[4],
									unsigned long int& pkt_dst_port,
									unsigned long int& pkt_length);
	unsigned long int last_read_time_;
	FlowVector& fv_;
	std::ifstream infile_;
	unsigned long int default_weight_;
	bool eof_;
};
