#include "Flow.h"

FlowState::FlowState(): credit(0)
{};

Flow::Flow():
	src_ip{},
	src_port(0),
	dst_ip{},
	dst_port(0),
	priority(0)
{};
