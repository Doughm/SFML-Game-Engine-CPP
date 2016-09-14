#include "loadini.h"

//returns if the given file exists
bool LoadINI::fileExists(std::string const& file)
{
	std::ifstream openFile;
	openFile.open(file);
	if(openFile.good() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	openFile.close();
}

//returns the whole file
std::string LoadINI::getWholeFile(std::string const& file)
{
	std::string tempString = "";
	std::ifstream openFile;
	std::stringstream buffer;
	if(openFile.good() == true)
	{
		openFile.open(file);
		buffer<<openFile.rdbuf();
		tempString = buffer.str();
	}
	openFile.close();
	return tempString;
}

//tests if given key is in the file
bool LoadINI::inFile(std::string const& file, std::string const& key)
{
	std::string tempString = "";
	std::ifstream openFile;
	std::stringstream buffer;
	openFile.open(file);
	buffer<<openFile.rdbuf();

	if(openFile.good() == true)
	{
		for(int i = 0; i < buffer.str().size(); ++i)
		{
			tempString.push_back(buffer.str()[i]);

			if(tempString == key)
			{
				return true;
			}

			if(buffer.str()[i] == ' ' || buffer.str()[i] == '=' || buffer.str()[i] == '\n')
			{
				tempString.clear();
			}
		}
	}

	openFile.close();
	return false;
}

//returns value of given key from file in a string format
std::string LoadINI::getValue(std::string const& file, std::string const& key)
{
	std::string tempString = "";
	std::ifstream openFile;
	std::stringstream buffer;
	openFile.open(file);
	buffer<<openFile.rdbuf();

	if(openFile.good() == true)
	{
		for(int i = 0; i < buffer.str().size() + 1; ++i)
		{
			tempString.push_back(buffer.str()[i]);

			if(tempString == key)
			{
				tempString.clear();
				for(int ii = i + 1; ii < buffer.str().size() + 1; ++ii)
				{
					if(buffer.str()[ii] == '\n' || ii == buffer.str().size())
					{
						return tempString;
					}
					else if(buffer.str()[ii] != ' ' && buffer.str()[ii] != '=' )
					{
						tempString.push_back(buffer.str()[ii]);
					}
				}
				tempString.clear();
			}

			if(buffer.str()[i] == ' ' || buffer.str()[i] == '=' || buffer.str()[i] == '\n')
			{
				tempString.clear();
			}
		}
	}
	openFile.close();
	return "key not found";
}

//updates a key in the file to a given value
void LoadINI::updateFile(std::string const& file, std::string const& key, std::string const& newValue)
{
	
	std::ifstream openFile;
	std::stringstream buffer;
	openFile.open(file);
	buffer<<openFile.rdbuf();
	std::string tempString = buffer.str();
	tempString.append(key + " = " + newValue);

	std::ofstream writeFile;
	writeFile.open(file);
	writeFile<<tempString;
	writeFile.close();
}