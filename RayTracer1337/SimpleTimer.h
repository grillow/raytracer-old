#pragma once
#include <chrono>
#include <ostream>
class SimpleTimer {
public:
	SimpleTimer(std::ostream& _out, std::string _name) : out(_out), name(_name) {
		start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		out << "<" << name <<  "> - started\n";
	}
	~SimpleTimer() {
		out << "<" << name << "> - finished in " << (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start) / (double)1000 << " seconds\n";
	}
private:
	unsigned __int64 start;
	std::ostream& out;
	const std::string name;
};