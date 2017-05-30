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
public:
	unsigned short int src_ip[4];
	unsigned long int src_port;
	unsigned short int dst_ip[4];
	unsigned long int dst_port;
	unsigned long int priority;

	bool operator==(const Flow&) const;

	FlowState state;

	Flow();

	/*
		This function creates a Flow with the following members initialized.
		FlowState member will be default initialized.
	 */
	Flow(const unsigned short int src_ip[4], long int src_port,
			 const unsigned short int dst_ip[4], long int dst_port);
};

#endif
