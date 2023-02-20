#ifndef BE_FILEBUFFER_H_INCLUDED
#define BE_FILEBUFFER_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

class BeFile
{
	public:
		BeFile();
		~BeFile();

		void clear();
		void setFilename( const std::string& fullfilename );
		void setFilename( const std::string& directory, const std::string& filename );

		std::string getFilename( ) const;
		std::string getFullFilename( ) const;
		std::string getDirectory( ) const;
		std::fstream* getFstream( );
		bool getLine( std::string& line );
		void getFile( std::string& file );

	protected:
	private:
		std::fstream* m_fstream;
		std::string m_filename;
		std::string m_directory;
		std::string m_fullfilename;
};

#endif
