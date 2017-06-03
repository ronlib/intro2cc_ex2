cmake_minimum_required(VERSION 3.5)
project(ex2)

# first we add the executable that generates the table
add_executable(sch main.cpp Flow.cpp PacketReader.cpp PacketWriter.cpp)
add_executable(test_flowvector test_flowvector.cpp Flow.cpp)
add_executable(test_packetreader test_packetreader.cpp Flow.cpp PacketReader.cpp)
