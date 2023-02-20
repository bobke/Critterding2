#ifndef BE_TIMER_H_INCLUDED
#define BE_TIMER_H_INCLUDED

#include "kernel/be_entity_interface.h"

	class BTimer : public BEntity
	{
		public:
			BTimer() { setProcessing(); }
			virtual ~BTimer() {};

			virtual void construct();

			virtual void process();
			inline void mark();
			void reset();
		private:
			BEntity* m_totalMilliSeconds; 
			BEntity* m_totalMilliSeconds_last;
			BEntity* m_elapsedMilliSeconds;
			BEntity* m_totalSeconds;
			BEntity* m_elapsedSeconds;
			BEntity* m_elapsedFrames;
			BEntity* m_target_fps;
			
			struct timeval m_start;
			struct timeval m_now;
	};

	class BSleeper : public BEntity
	{
		public:
			BSleeper() : m_elapsedMilliSeconds(0) { setProcessing(); }
			virtual ~BSleeper() {};

			virtual void construct();
			virtual void process();
		private:
			BEntity* m_target_fps;
			BEntity* m_elapsedMilliSeconds;
	};
#endif
