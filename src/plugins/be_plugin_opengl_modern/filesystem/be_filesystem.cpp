// boost::shared_ptr<BeGraphicsModel> m(new BeGraphicsModel( m_fileSystem.getDataRoot(path) ));
#include "be_filesystem.h"

using namespace boost::filesystem;

BeFilesystem::BeFilesystem()/* : m_logDebug("FILE")*/
{
}

bool BeFilesystem::load( BeFile& befile, const std::string& file )
{
	// search root paths for file
	for ( unsigned int i=0; i < berootpaths.list.size(); i++ )
	{
		std::string fullfilename( berootpaths.list[i] );
		fullfilename.append( file );
// 		m_logDebug << "::FILE checking " << fullfilename << "\n";
// 		std::cerr << "checking " << fullfilename << std::endl;
		
		if ( boost::filesystem::exists( fullfilename ) )
		{
// 			m_logDebug << "::FILE loading " << fullfilename << "\n";
			befile.setFilename( fullfilename );
			return true;
		}
	}

// 	m_logDebug << "::FILE warning: cannot find file '" << file << "'\n";
	return false;
}

std::string BeFilesystem::getPath( const std::string& file )
{
	// search root paths for file
	for ( unsigned int i=0; i < berootpaths.list.size(); i++ )
	{
		std::string fullfilename( berootpaths.list[i] );
		fullfilename.append( file );
		
		if ( boost::filesystem::exists( fullfilename ) )
		{
			return fullfilename;
		}
	}

// 	m_logDebug << "::FILE warning: cannot find file '" << file << "'\n";
	return "";
}

void BeFilesystem::save(const std::string &filename, const std::string& content)
{
	std::fstream file_op(filename.c_str(),std::ios::out);
	file_op << content;
	file_op.close();
}

void BeFilesystem::rm(const std::string& filename)
{
// 	if( remove( filename.c_str() ) != 0 )
// 		m_logDebug << "::FILE error: deleting file " << filename << "\n";
// 	std::cerr << "Error deleting file" << std::endl;
// 	else
// 		cerr << "file succesfully deleted" << endl;
}

BeFilesystem::~BeFilesystem()
{
}
