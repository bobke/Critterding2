#include "be_timer.h"
#include "be_entity_core_types.h"
// #include <sys/time.h>
#include <iostream>
#include <chrono>
#include <thread>

	void BTimer::construct()
	{
		m_totalMilliSeconds = addChild( "ms_total", new BEntity_uint() );
		m_totalMilliSeconds_last = addChild( "ms_total_last", new BEntity_uint() );
		m_elapsedMilliSeconds = addChild( "ms_elapsed", new BEntity_uint() );
		m_totalSeconds = addChild( "s_total", new BEntity_float() );
		m_elapsedSeconds = addChild( "s_elapsed", new BEntity_float() );
		m_elapsedFrames = addChild( "frame", new BEntity_uint() );
		m_startMilliSeconds = addChild( "ms_start", new BEntity_uint() );
		reset();
		m_startMilliSeconds->set( (Buint)(((m_start.tv_sec) * 1000 + (m_start.tv_usec)/1000.0)) );
	}

	void BTimer::process()
	{
		mark();
	}
	
	void BTimer::mark()
	{
		// TEST auto elapsed = std::chrono::high_resolution_clock::now() - frame_start;
        // TEST double elapsed_seconds = std::chrono::duration<double>(elapsed).count();
		
		gettimeofday(&m_now, NULL);

		m_totalMilliSeconds->set( (Buint)(((m_now.tv_sec  - m_start.tv_sec) * 1000 + (m_now.tv_usec - m_start.tv_usec)/1000.0) + 0.5) );
		if ( m_totalMilliSeconds->get_uint() > 0 )
		{
			m_elapsedMilliSeconds->set( (Buint)m_totalMilliSeconds->get_uint() - m_totalMilliSeconds_last->get_uint() );
			m_totalSeconds->set( 0.001f * m_totalMilliSeconds->get_uint() );
			m_elapsedSeconds->set( 0.001f * m_elapsedMilliSeconds->get_uint() );
			m_totalMilliSeconds_last->set( m_totalMilliSeconds->get_uint() );
			m_elapsedFrames->set( m_elapsedFrames->get_uint()+1 );
		}
	}
	
	void BTimer::reset()
	{
		gettimeofday(&m_start, NULL);
		m_now = m_start;
		m_elapsedMilliSeconds->set( (Buint)0 );
		m_totalSeconds->set( 0.0f );
		m_elapsedSeconds->set( 0.0f );
		m_totalMilliSeconds_last->set( (Buint)0 );
		m_elapsedFrames->set( (Buint)0 );
	}

	void BSleeper::construct()
	{
		m_target_fps = addChild( "target_fps", new BEntity_uint() );
		m_target_fps->set( (Buint)0 );
	}

	void BSleeper::process()
	{
		if ( m_target_fps->get_uint() > 0 )
		{
			if ( m_elapsedMilliSeconds == 0 )
			{
				auto found_sys = topParent()->getChild("sys", 1);
				if ( !found_sys )
				{
					found_sys = topParent()->addChild( "sys", new BEntity() );
				}
				auto timer = found_sys->getChild("timer", 1);
				if ( !timer )
				{
					timer = found_sys->addChild( "timer", new BTimer() );
				}
				m_elapsedMilliSeconds = timer->getChild( "ms_elapsed", 1 );
			}

			auto frame_duration = 1000 / m_target_fps->get_uint();
			// std::this_thread::sleep_for(std::chrono::milliseconds( frame_duration ));
			
			unsigned int inter = 0;
			if ( m_elapsedMilliSeconds->get_uint() > frame_duration )
				inter = m_elapsedMilliSeconds->get_uint() - frame_duration;

			if ( inter < frame_duration )
			{
				std::this_thread::sleep_for(std::chrono::milliseconds( frame_duration - inter ));
				// std::cout << "sleep " << frame_duration - inter << std::endl;
				// std::this_thread::sleep_for(std::chrono::duration<double>( frame_duration - elapsed_seconds ));
			}
			// else
			// {
			// 	std::cout << "skip " << frame_duration << std::endl;
			// 	std::this_thread::sleep_for(std::chrono::milliseconds( frame_duration ));
			// }
			
			
			// if ( m_elapsedMilliSeconds->get_uint() < frame_duration )
			// {
			// 	std::this_thread::sleep_for(std::chrono::milliseconds( frame_duration - m_elapsedMilliSeconds->get_uint() ));
			// 	std::cout << "sleep " << frame_duration - m_elapsedMilliSeconds->get_uint() << std::endl;
			// 	// std::this_thread::sleep_for(std::chrono::duration<double>( frame_duration - elapsed_seconds ));
			// }
			// else
			// {
			// 	// std::cout << "skip " << frame_duration << std::endl;
			// 	// std::this_thread::sleep_for(std::chrono::milliseconds( frame_duration ));
			// }
		}
	}

