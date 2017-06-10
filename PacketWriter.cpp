#include <iostream>
#include <string>
#include "PacketWriter.h"

using namespace std;

PacketWriter::PacketWriter(const std::string& file_path)
	: outfile_(file_path)
{

}

void PacketWriter::write_packet(const unsigned int pktID, const unsigned int time)
{
	outfile_ << time << ": " << pktID << "\r\n";
}
