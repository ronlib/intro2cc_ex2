#ifndef _FLOW__H
#define _FLOW__H

#include <vector>

struct FlowState
{
	unsigned long int credit;
	std::vector<unsigned short> packetlist;

	public:
	FlowState();

};


struct Flow
{
	unsigned short int src_ip[4];
	unsigned long int src_port;
	unsigned short int dst_ip[4];
	unsigned long int dst_port;
	unsigned long int priority;

	FlowState state;

public:
	Flow();
};

#endif
