#include "be_parser.h"
#include <boost/lexical_cast.hpp>
#include "LinearMath/btVector3.h"

BeParser::BeParser() : position_index(0)
{
}

BeParser::~BeParser()
{
}

void BeParser::reset()
{
	position_index = 0;
}

bool BeParser::endMatches(const std::string& stop, std::string& line)
{
	if ( line.size() >= stop.size() )
	{
		if ( line.substr( line.size()-stop.size(), stop.size() ) == stop )
			return true;
	}

	return false;
}

bool BeParser::endMatchesStrip(const std::string& stop, std::string& line)
{
	if ( line.size() >= stop.size() )
	{
		if ( line.substr( line.size()-stop.size(), stop.size() ) == stop )
		{
			line = line.substr( 0, line.size()-stop.size() );
			return true;
		}
	}

	return false;
}

void BeParser::trimWhitespaces(const std::string& line)
{
	if(position_index!=std::string::npos)
	{
		char ch=0;
		do 
		{
			ch=line[position_index];
			if(isspace(ch))
			{
				++position_index;
			}
			else if(ch!=0)
			{
				return;
			}
		} 
		while (ch!=0);
		position_index = std::string::npos;
	}
}

void BeParser::removeCommentlines(std::string& line)
{
	if(position_index != std::string::npos)
	{
		const char *ch=line.c_str();
		if(ch && (ch[position_index]=='/'||ch[position_index]=='#') )
		{
			position_index = std::string::npos;
		}
		else if(!ch)
		{
			position_index = std::string::npos;
		}
	}
}


bool BeParser::beginMatches(const std::string& stop, const std::string& line)
{
	if ( line.substr( position_index, stop.size() ) == stop )
		return true;
	return false;
}

bool BeParser::beginMatchesStrip(const std::string& stop, const std::string& line)
{
	if ( line.substr( position_index, stop.size() ) == stop )
	{
		position_index += stop.size();
		return true;
	}
	return false;
}

std::string BeParser::returnUntillStrip(const char stop, const std::string& line)
{
	std::string result;
	if(position_index!=std::string::npos)
	{
		const size_t pos = line.find_first_of( stop, position_index );
		if ( pos != std::string::npos )
		{
			result = line.substr( position_index, pos-position_index );

			// increase positionindex
			position_index = pos+1;
		}
		else
		{
			result = line.substr( position_index, std::string::npos );
			position_index = std::string::npos;
		}
	}
	return result;
}

std::string BeParser::returnUntillStrip(const std::string& stop, const std::string& line)
{
	std::string result;
	if(position_index!=std::string::npos)
	{
		const size_t pos = line.find( stop, position_index );
		if ( pos != std::string::npos )
		{
			result = line.substr( position_index, pos-position_index );

			// increase positionindex
			position_index = pos+stop.size();
		}
		else
		{
			result = line.substr( position_index, std::string::npos );
			position_index = std::string::npos;
		}
	}
	return result;
}

std::string BeParser::returnRemainder(const std::string& line)
{
	std::string result;
	if(position_index!=std::string::npos)
	{
// 		const size_t pos = line.find( stop, position_index );
		if ( position_index != std::string::npos )
		{
			result = line.substr( position_index, line.size() );

			// increase positionindex
			position_index = std::string::npos;
		}
		else
		{
			result = line.substr( position_index, std::string::npos );
			position_index = std::string::npos;
		}
	}
	return result;
}

bool BeParser::parseUnsignedInt( const std::string& string, unsigned int& value )
{
	const std::string& str=returnUntillStrip(' ', string);
	if( !str.empty() )
	{
		value = boost::lexical_cast<unsigned int>(str);
		return true;
	}
	return false;
}

bool BeParser::parseInt( const std::string& string, int& value )
{
	const std::string& str=returnUntillStrip(' ', string);
	if( !str.empty() )
	{
		value = boost::lexical_cast<int>(str);
		return true;
	}
	return false;
}

bool BeParser::parseFloat( std::string& string, float& value )
{
	const std::string& str = returnUntillStrip(' ', string);
	if( !str.empty() )
	{
		value = boost::lexical_cast<float>(str);
		return true;
	}
	return false;
}

bool BeParser::parseVector3( std::string& string, btVector3& value )
{
	float x(0),y(0),z(0);
	if( parseFloat(string, x) )
	{
		if( parseFloat(string, y) )
		{
			if( parseFloat(string, z) )
			{
				value = btVector3(x,y,z);
				return true;
			}
		}
	}
	return false;
}

bool BeParser::parseString( std::string& string, std::string& value )
{
    value = returnUntillStrip( ' ', string );
    return true;
}

bool BeParser::wrap(std::string& wrapin, const std::string& towrap, const std::string& insert_front, const std::string& insert_behind )
{
	size_t pos = wrapin.find( towrap );
	if ( pos != std::string::npos )
	{
		std::string wrapped(insert_front);
		wrapped.append(towrap);
		wrapped.append(insert_behind);
		
		wrapin.replace( pos, towrap.size(), wrapped );
		return true;
	}
	return false;
} 
