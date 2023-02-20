#ifndef DIR_H_INCLUDED
#define DIR_H_INCLUDED

#include "boost/filesystem.hpp"

#include <string>
#include <vector>

class Dir
{
private:
	//If/When linux support for boost filesystem is available id recommend changing this std::string 
	//to boost::filesystem::path instead, but not until then.
	typedef std::string Path;
	typedef std::vector<Path> Paths;
public:
		Dir();
		~Dir();

		//Andy - Id consider renaming this arg directoryPath

		bool		exists(const Path& directory) const;
		void		make(const Path& directory) const;

		//Andy - Id like to rename dir for consistency 
		//with the above funtions if/when Linux supports boost::filesystem
		//Id also like to rename files to filePaths
		void		listContents(const Path& dir, Paths& files, const bool fullPath=false) const;
		void		listContentsFull(const Path& dir, Paths& files) const;

};

#endif
