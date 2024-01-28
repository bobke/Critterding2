#include "be_dir.h"

using namespace boost::filesystem;

Dir::Dir()
{
}

bool Dir::exists(const Path& directory) const
{
	const path directoryPath(directory);
	return boost::filesystem::exists(directoryPath) && is_directory(directoryPath);
}

void Dir::make(const Path& directory) const
{
	const path directoryPath(directory);
	create_directory(directoryPath);        
}

void Dir::listContents(const Path& dir, Paths& files, const bool fullPath) const
{
	if(exists(dir))
	{
		const Path directoryPath(dir);
		const directory_iterator end;	//default constructor constructs end iterator
		
		
		
//         copy(directory_iterator(directoryPath), directory_iterator(), // directory_iterator::value_type
//           ostream_iterator<directory_entry>(cout, "\n")); // is directory_entry, which is
//                                                           // converted to a path by the
//                                                           // path stream inserter
		
		
		
		for( directory_iterator iter(directoryPath) ; iter != end ; ++iter )
		{
// 			if(is_regular_file(*iter))
// 			{
// 				if(fullPath)
// 				{
// 					Path finalPath(dir);
// 					finalPath += "/";
// 					finalPath += iter->path().file_string();
// 					files.push_back(finalPath);
// 				}
// 				else
// 				{
// 					files.push_back(iter->leaf());
// 				}
// 			}
		}
	}
}

void Dir::listContentsFull(const Path& dir, Paths& files) const
{
	listContents(dir, files, true);
}


Dir::~Dir()
{
}