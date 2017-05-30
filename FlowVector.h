#ifndef _FLOW_VECTOR__H
#define _FLOW_VECTOR__H


#include <vector>
#include "Flow.h"

class FlowVector
{
 public:

	std::vector<Flow>::iterator find_flow(	const unsigned short int src_ip[4], long int src_port,
																					const unsigned short int dst_ip[4], long int dst_port);
	void add_flow(const Flow& flow);
	std::vector<Flow>::iterator get_iterator();

 private:
	std::vector<Flow> flow_vector_;

};

#endif
