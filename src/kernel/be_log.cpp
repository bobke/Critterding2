// #include "be_log.h"
// #include "common/be_parser.h"
// #include <iostream>
// #ifdef WIN32
// 	#include <Windows.h>
// #endif
// #include "utils/settings.h"
// 
// BeLogDebug::BeLogDebug( const std::string& chapter )
//  : m_chapter("debug_" + chapter)
//  , m_cout_chapter("::"+chapter+" ")
//  , m_setting_all(0)
//  , m_setting_chapter(0)
// {
// // 	m_setting_all = Settings::Instance()->getCVarP("debug_ALL");
// // 	m_setting_chapter = Settings::Instance()->getCVarP(m_chapter);
// };
// 
// void BeLogDebug::log(const std::string& message)
// {
// 	if ( m_setting_all==0 )
// 	{
// 		m_setting_all = Settings::Instance()->getCVarPtr("debug_ALL");
// 		m_setting_chapter = Settings::Instance()->getCVarPtr(m_chapter);
// }
// 	
// 	if ( 
// 		*m_setting_chapter == 1
// 		|| *m_setting_all == 1
// 		|| m_chapter == "debug_ERROR"
// 	)
// 	{
// 		#ifndef WIN32
// 			std::string newmessage(message);
// 			BeParser parseH;
// 
// 			// color wrap chapter
// 			if ( parseH.beginMatchesStrip("::", newmessage ) )
// 				parseH.wrap( newmessage, parseH.returnUntillStrip(" ", newmessage), ANSI_CYAN_BOLD, ANSI_NORMAL );
// 
// 			// color wrap errors and warnings
// 			parseH.wrap( newmessage, " error", ANSI_RED_BOLD, ANSI_NORMAL );
// 			parseH.wrap( newmessage, " warning", ANSI_YELLOW_BOLD, ANSI_NORMAL );
// 			std::cout << newmessage;
// 		#else
// 			OutputDebugString(message.c_str());
// 			std::cout << message;
// 		#endif
// 	}
// }


#include "be_log.h"
// #include "common/be_parser.h"
#include "utils/settings.h"
#include <iostream>
#ifdef WIN32
	#include <Windows.h>
#endif

void BeLogDebug::log(const std::string& message)
{
	if ( !m_one_test_done )
	{
		if (m_do_chapter==false)
			if ( Settings::Instance()->getCVar(m_chapter) == 1 )
				m_do_chapter=true;
		if (m_do_all==false)
			if ( Settings::Instance()->getCVar("debug_ALL") == 1 )
				m_do_all=true;
		m_one_test_done = true;
	}
	
	if ( 
		m_do_chapter == 1
		|| m_do_all == 1
		|| m_chapter == "debug_ERROR"
	)
// 	if ( 
// 		Settings::Instance()->getCVar(m_chapter) == 1
// 		|| Settings::Instance()->getCVar("debug_ALL") == 1
// 		|| m_chapter == "debug_ERROR"
// 	)
	{
		#ifndef WIN32
			std::string newmessage(message);
			BeParser parseH;

			// color wrap chapter
			if ( parseH.beginMatchesStrip("::", newmessage ) )
				parseH.wrap( newmessage, parseH.returnUntillStrip(" ", newmessage), ANSI_CYAN_BOLD, ANSI_NORMAL );

			// color wrap errors and warnings
			parseH.wrap( newmessage, " error", ANSI_RED_BOLD, ANSI_NORMAL );
			parseH.wrap( newmessage, " warning", ANSI_YELLOW_BOLD, ANSI_NORMAL );
			std::cout << newmessage;
		#else
			OutputDebugString(message.c_str());
			std::cout << message;
		#endif
	}
}
