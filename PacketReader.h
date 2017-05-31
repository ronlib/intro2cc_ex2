#include <fstream>
#include <string>
#include "FlowVector.h"

class PacketReader
{
 public:
	// TODO: Use move semantics for FlowVector
	PacketReader(const std::string& file_path, FlowVector&, unsigned long int default_weight);
	bool read_until(unsigned long int time);


 private:
	unsigned long int last_read_time_;
	FlowVector& fv_;
	std::ifstream infile_;
	unsigned long int default_weight_;
};
