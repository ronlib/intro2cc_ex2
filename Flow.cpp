#include <algorithm>
#include <cstring>
#include "FlowVector.h"
#include "Flow.h"

using namespace std;

std::vector<Flow>::iterator FlowVector::iterator()
{
	return this->flow_vector_.begin();
}

std::vector<Flow>::iterator FlowVector::end()
{
	return this->flow_vector_.end();
}

Flow::Flow(const unsigned short int src_ip[4], long int src_port,
					 const unsigned short int dst_ip[4], long int dst_port)
	:weight(0)
{
	std::memcpy(this->src_ip, src_ip, sizeof(this->src_ip));
	std::memcpy(this->dst_ip, dst_ip, sizeof(this->src_ip));
	this->src_port = src_port;
	this->dst_port = dst_port;
}


std::vector<Flow>::iterator FlowVector::find_flow(const unsigned short int src_ip[4], long int src_port,
																			const unsigned short int dst_ip[4], long int dst_port)
{
	return std::find(this->flow_vector_.begin(), this->flow_vector_.end(),
									 Flow(src_ip, src_port, dst_ip, dst_port));
}

std::vector<Flow>::iterator FlowVector::find_flow(const Flow& f)
{
	return std::find(this->flow_vector_.begin(), this->flow_vector_.end(), f);
}

void FlowVector::add_flow(const Flow& flow)
{
	this->flow_vector_.push_back(flow);
}


FlowState::FlowState(): credit(0)
{};

Flow::Flow():
	src_ip{},
	src_port(0),
	dst_ip{},
	dst_port(0),
	weight(0)
{};


bool Flow::operator==(const Flow& b) const
{
	bool result = true;
	result = result && std::equal(std::begin(this->src_ip), std::end(this->src_ip),
												 std::begin(b.src_ip), std::end(b.src_ip));
	result = result && std::equal(std::begin(this->dst_ip), std::end(this->dst_ip),
												std::begin(b.dst_ip), std::end(b.dst_ip));
	result = result && this->src_port==b.src_port;
	result = result && this->dst_port==b.dst_port;

	return result;
}

Packet::Packet(unsigned short length, unsigned long pktID)
	: length(length), pktID(pktID)
{}


void FlowVector::add_credit(const unsigned int quantum)
{
	for (vector<Flow>::iterator t_fi = this->iterator() ; t_fi != this->end() ; ++t_fi)
		{
			if ((*t_fi).state.packetlist.size() > 0)
				{
					(*t_fi).state.credit += (*t_fi).weight*quantum;
				}
		}

}

unsigned long int FlowVector::count_packets()
{
	unsigned long int counter = 0;
	for (vector<Flow>::iterator t_fi = this->iterator() ; t_fi != this->end() ; ++t_fi)
		{
			counter += (*t_fi).state.packetlist.size();
		}

	return counter;
}


void FlowVector::zero_credit()
{
	for (vector<Flow>::iterator t_fi = this->iterator() ; t_fi != this->end() ; ++t_fi)
		{
			(*t_fi).state.credit = 0;
		}
}
