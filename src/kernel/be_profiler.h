#ifndef BE_PROFILER_H_INCLUDED
#define BE_PROFILER_H_INCLUDED

#include "be_timer.h"
#include <iostream>
// #include "be_log.h"

class BeProfiler
{
public:
	BeProfiler(const char* const id) : m_id(id)
	{
		m_timer.mark();
	}
	~BeProfiler()
	{
		m_timer.mark();
// 		BeLogDebug("PROFILER") << "::PROFILER " << m_id << " " << m_timer.getMilliSeconds() << "\n";
		std::cout << "::PROFILER " << m_id << " " << m_timer.getMilliSeconds() << "ms" << std::endl;
	}
private:
	const char* const m_id;
	BeTimer m_timer;
};

#ifdef UNIX
#define BE_FUNCTION_ID	__PRETTY_FUNCTION__
#else
#define BE_FUNCTION_ID	__FUNCTION__
#endif

#define BE_FUNCTION_PROFILER BeProfiler profiler(BE_FUNCTION_ID)


#endif
