#ifndef _FLOW_VECTOR__H
#define _FLOW_VECTOR__H


#include <vector>
#include "Flow.h"

class FlowVector
{
 public:
	FlowVector();
	FlowState& find_or_add_flow(Flow&);
	std::vector<Flow> get_iterator();

 private:
	std::vector <Flow> flow_vector_;

};

#endif
