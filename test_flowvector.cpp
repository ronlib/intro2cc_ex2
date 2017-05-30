#include <iostream>
#include <cstring>
#include <cassert>
#include "FlowVector.h"
#include "Flow.h"

int main()
{

	FlowVector flowvector;
	unsigned short int src_ip[] = {100, 100, 100, 100};
	unsigned short int dst_ip[] = {100, 100, 100, 101};
	Flow flow = Flow(src_ip, 10, dst_ip, 10);
	flow.state.credit = 1;
	flowvector.add_flow(flow);

	std::vector<Flow>::iterator found_flow = flowvector.find_flow(src_ip, 10, dst_ip, 10);

	assert(std::memcmp(found_flow->src_ip, src_ip, sizeof(src_ip)) == 0);

	std::cout << "All tests passed" << std::endl;
	return 0;
}
