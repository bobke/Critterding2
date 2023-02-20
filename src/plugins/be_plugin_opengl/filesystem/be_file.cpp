#include <cstring>
#include "be_file.h"

BeFile::BeFile()
{
	m_fstream = 0;
}

void BeFile::setFilename( const std::string& fullfilename )
{
	size_t pos = fullfilename.find_last_of("/", fullfilename.size());
	if ( pos != std::string::npos )
	{
		m_directory = fullfilename.substr( 0, pos+1 );
		m_filename = fullfilename.substr( pos+1, fullfilename.size() );
		setFilename(
			fullfilename.substr( 0, pos+1 ), fullfilename.substr( pos+1, fullfilename.size() )
		);
	}
}

void BeFile::setFilename( const std::string& directory, const std::string& filename )
{
	m_directory = directory;
	m_filename = filename;

	m_fullfilename = m_directory;
	m_fullfilename.append(m_filename);
}

std::string BeFile::getFilename( ) const
{
	return m_filename;
}

std::string BeFile::getFullFilename( ) const
{
	return m_fullfilename;
}

std::string BeFile::getDirectory( ) const
{
	return m_directory;
}

std::fstream* BeFile::getFstream( )
{
// 	std::cerr << m_fullfilename.c_str() << std::endl;
	if ( m_fstream == 0 )
		m_fstream = new std::fstream( m_fullfilename.c_str(), std::ios::in );

	return m_fstream;
}

bool BeFile::getLine( std::string& line )
{
	std::fstream* file_op = getFstream();
	if ( file_op != 0 )
	{
		if ( !file_op->eof() )
		{
			char str[2000];
// 			memset(str, 0, 2000);
			
			file_op->getline(str,2000);
			line = str;

			if ( line.size() > 0 )
			{
				if ( line.substr( line.size()-1, 1 ) == "\r" )
					line = line.substr( 0, line.size()-1 );
				if ( line.size() > 0 )
					if ( line.substr( line.size()-1, 1 ) == "\0" )
						line = line.substr( 0, line.size()-1 );
			}
			return true;
		}
		return false;
	}
	return false;
}

void BeFile::getFile( std::string& file )
{
	std::string line;
	while ( getLine(line) )
	{
		file.append(line);
		file.append("\n");
	}
}


BeFile::~BeFile()
{
	if ( m_fstream )
		delete m_fstream;
}
