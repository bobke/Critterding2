#ifndef BE_ROOTPATHS_H_INCLUDED
#define BE_ROOTPATHS_H_INCLUDED

#include <string>
#include <vector>

class BeRootPaths
{
	public:
		BeRootPaths();
		~BeRootPaths();

		void push( const std::string& directory );

		std::vector<std::string> list; // FIXME private?
		
	protected:
	private:
};

#endif
