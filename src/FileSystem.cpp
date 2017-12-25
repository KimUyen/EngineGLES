#include "FileSystem.h"



void FileSystem::AddSearchPath(const char * path)
{
	if (path)
		_searchPath.push_back(path);
}

bool FileSystem::Open(const char * filename)
{

	for (std::vector<std::string>::reverse_iterator itsp = _searchPath.rbegin(); itsp != _searchPath.rend(); itsp++)
	{
		return true;
	}
	return false;
}

FileSystem::FileSystem()
{
}


FileSystem::~FileSystem()
{
}
