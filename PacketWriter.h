#include <fstream>
#include <string>


class PacketWriter
{
 public:
	PacketWriter(const std::string& file_path);
	void write_packet(const unsigned int pktID, const unsigned int time);

 private:
	std::ofstream outfile_;
};
