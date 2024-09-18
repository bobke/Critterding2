#ifndef BE_PARSER_H_INCLUDED
#define BE_PARSER_H_INCLUDED

#include <string>

class btVector3;

class BeParser
{
	public:
		BeParser();
		~BeParser();

		void		trimWhitespaces(const std::string& line);
		void		removeCommentlines(std::string& line);

		bool		endMatches(const std::string& stop, std::string& line);
		bool		endMatchesStrip(const std::string& stop, std::string& line);

		bool		beginMatches(const std::string& stop, const std::string& line);
		bool		beginMatchesStrip(const std::string& stop, const std::string& line);

		std::string	returnUntillStrip(const char stop, const std::string& line);
		std::string	returnUntillStrip(const std::string& stop, const std::string& line);
		std::string	returnRemainder(const std::string& line);
		
		bool		wrap(std::string& wrapin, const std::string& towrap, const std::string& insert_front, const std::string& insert_behind );

		void		reset();
		std::string::size_type position_index;
	protected:
	private:
		std::string	m_result;

};

#endif
 
