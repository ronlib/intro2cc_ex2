#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iterator>

#include "Flow.h"
#include "FlowVector.h"
#include "PacketReader.h"
#include "PacketWriter.h"


using namespace std;

int main(int argc, char *argv[])
{
	stringstream ss;
	ss << argv[4] << ' ' << argv[5];

	std::string scheduler(argv[1]), input_file_path(argv[2]), output_file_path(argv[3]);
	int default_weight = 0, quantum = 0;
	bool drr = false;

	ss >> default_weight;
	ss >> quantum;

	if (scheduler == "DRR")
		{
			drr = true;
		}
	else if (scheduler == "RR")
		{
			drr = false;
		}
	else
		{
			throw invalid_argument("Scheduler type is not DRR or RR");
		}

	FlowVector fv = FlowVector();
	PacketReader pr = PacketReader(input_file_path, fv, default_weight);
	PacketWriter pw = PacketWriter(output_file_path);

	unsigned long int time = 0;

	vector<Flow>::iterator fi = fv.iterator(); // Flow iterator

	while (!pr.has_reached_eof() || fv.count_packets() > 0)
	{
		if (fv.count_packets() == 0)
			{
				try
					{
						time = pr.next_packet_time();
					}
				catch (...)
					{
						break;
					}
				pr.read_until(time);
				fi = fv.iterator();
			}

		bool packet_sent = false;

		while (!packet_sent)
			{
				if ((*fi).state.packetlist.size() > 0)
					{
						if (drr)
							{
								if (!packet_sent)
									{
										(*fi).state.credit += (*fi).weight*quantum;
									}

								while ((*fi).state.packetlist.size() > 0 &&
											 (*fi).state.credit >= (*fi).state.packetlist.front().length)
									{
										pw.write_packet((*fi).state.packetlist.front().pktID, time);
										(*fi).state.credit -= (*fi).state.packetlist.front().length;
										time = time + (*fi).state.packetlist.front().length;
										(*fi).state.packetlist.erase((*fi).state.packetlist.begin());
										unsigned long int index = fi - fv.iterator();
										pr.read_until(time);
										fi = fv.iterator();
										advance(fi, index);
										packet_sent = true;
									}
							}
						else
							{
								if (!packet_sent)
									{
										(*fi).state.credit = (*fi).weight;
									}

								while ((*fi).state.packetlist.size() > 0 &&
											 (*fi).state.credit > 0)
									{
										pw.write_packet((*fi).state.packetlist.front().pktID, time);
										(*fi).state.credit -= 1;
										time = time + (*fi).state.packetlist.front().length;
										(*fi).state.packetlist.erase((*fi).state.packetlist.begin());
										unsigned long int index = fi - fv.iterator();
										pr.read_until(time);
										fi = fv.iterator();
										advance(fi, index);
										packet_sent = true;
									}
							}
					}
				else
					{
						(*fi).state.credit = 0;
					}

				++fi;
				if (fi == fv.end())
					{
						fi = fv.iterator();
					}
			}
	}

	// while ((read_res=pr.read_until(time)))
	// 	{
	// 		// fv.add_credit(quantum);
	// 		bool sending = false;

	// 		if (sending_until <= time)
	// 			{

	// 				sending = false;
	// 				// Check for the first flow to have enough credit to send
	// 				vector<Flow>::iterator starting_fi = fi;
	// 				do
	// 					{
	// 						if ((*fi).state.packetlist.size() > 0)
	// 							{
	// 								(*fi).state.credit += (*fi).weight*quantum;

	// 								if ((*fi).state.credit > (*fi).state.packetlist.front().length)
	// 									{
	// 										pw.write_packet((*fi).state.packetlist.front().pktID, time);
	// 										(*fi).state.credit -= (*fi).state.packetlist.front().length;
	// 										(*fi).state.packetlist.erase((*fi).state.packetlist.begin());

	// 										if ((*fi).state.packetlist.size() == 0)
	// 											{
	// 												(*fi).state.credit = 0;
	// 											}

	// 										sending_until = time + (*fi).state.packetlist.front().length;
	// 										sending = true;
	// 									}
	// 							}

	// 						if (!sending)
	// 							{
	// 								++fi;
	// 								if (fi == fv.end())
	// 									// starting from the beginning of the vector
	// 									{
	// 										fi = starting_fi;
	// 									}
	// 							}
	// 					} while (!sending && starting_fi != fi);


	// 				if (!sending)
	// 					// Meaning there was no flow with enough credit
	// 					{

	// 					}


	// 			}


	// 		++time;
	// 	}

	return 0;
}
