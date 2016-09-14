//includes all functionality needed to save and load from an ini file

#ifndef LOADINI
#define LOADINI

#include <string>
#include <fstream>
#include <sstream>

class LoadINI
{
public:
	static bool fileExists(std::string const&);
	static std::string getWholeFile(std::string const& file);
	static bool inFile(std::string const&, std::string const&);
	static std::string getValue(std::string const&, std::string const&);
	static void updateFile(std::string const&, std::string const&, std::string const&);
};

#endif