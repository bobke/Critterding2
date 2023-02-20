#ifndef BE_LOG_H_INCLUDED
#define BE_LOG_H_INCLUDED

#include <string>
#include <boost/lexical_cast.hpp>

#define ANSI_NORMAL		"\033[0;39m"
#define ANSI_RED		"\033[0;31m"
#define ANSI_RED_BOLD		"\033[1;31m"
#define ANSI_GREEN		"\033[0;32m"
#define ANSI_GREEN_BOLD		"\033[1;32m"
#define ANSI_YELLOW		"\033[0;33m"
#define ANSI_YELLOW_BOLD	"\033[1;33m"
#define ANSI_BLUE		"\033[0;34m"
#define ANSI_BLUE_BOLD		"\033[1;34m"
#define ANSI_MAGENTA		"\033[0;35m"
#define ANSI_MAGENTA_BOLD	"\033[1;35m"
#define ANSI_CYAN		"\033[0;36m"
#define ANSI_CYAN_BOLD		"\033[1;36m"

#define BE_ERROR(msg)								\
{										\
	BeLogDebug beError("ERROR");						\
	beError << msg << "\n";							\
	beError << __FILE__ << " : ";						\
	beError << __LINE__ << "\n";						\
	exit(1);								\
}

class BeLog
{
	public:
		template<typename T>
		BeLog& operator<<(const T& t)
		{
			log(boost::lexical_cast<std::string>(t));
			return *this;
		}
	protected:
		virtual ~BeLog() {};
	private:
		virtual void log(const std::string& message)=0;
};

class BeLogDebug : public BeLog
{
	public:
		BeLogDebug( const std::string& chapter )
		 : m_chapter("debug_" + chapter)
		 , m_cout_chapter("::"+chapter+" ")
		 , m_do_chapter(false)
		 , m_do_all(false)
		 , m_one_test_done(false)
		{};
		virtual ~BeLogDebug() {};
		const std::string& chapter() { return m_cout_chapter; }
		const std::string warn()
		{
			return chapter()+std::string(ANSI_YELLOW_BOLD)+"warning"+std::string(ANSI_NORMAL)+": ";
		}
	private:
		void log(const std::string& message);
		std::string m_chapter;
		std::string m_cout_chapter;
		
		bool m_do_chapter;
		bool m_do_all;
		bool m_one_test_done;
};

#endif

