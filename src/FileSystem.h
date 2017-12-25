#pragma once
#include <queue>

class FileSystem
{
	std::vector<std::string> _searchPath;
public:
	void AddSearchPath(const char * path);
	bool Open(const char * filename);
	FileSystem();
	~FileSystem();
};

