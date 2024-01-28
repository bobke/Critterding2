#include <sstream>
// #include "utils/settings.h"

#include "be_rootpaths.h"

BeRootPaths::BeRootPaths()
{
	// current relative path
		push( "" );
		push( "/" );
}

void BeRootPaths::push( const std::string& directory )
{
// 	cerr << "added " << directory << endl;
	list.push_back( directory );
}

BeRootPaths::~BeRootPaths()
{
}
