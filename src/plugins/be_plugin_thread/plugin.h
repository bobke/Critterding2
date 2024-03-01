#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_entity_top.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

	class BeSensor
	{
	public:
		BeSensor() :
			m_flag_start(false),
			m_flag_done(false)
		{};
		virtual ~BeSensor() {};
		void start();
		void wait();
		void wait_start();
		void signal_done();
	private:
		bool m_flag_start;
		std::mutex start_condition_mutex;
		std::condition_variable start_condition;

		bool m_flag_done;
		std::mutex done_condition_mutex;
		std::condition_variable done_condition;
	};

// 	//  A THREAD BASECLASS
// 		class BThreadBase
// 		{
// 			public:
// 				BThreadBase() {};
// 				virtual ~BThreadBase() { };
// 		};

	//  A THREAD
		class BEntityThread : public BEntityTop   // FIXME SHOULD BE A be_entity_top, when it's a top though it seems the children are not added
		{
			public:
				BEntityThread();
				virtual ~BEntityThread();
				const char* class_id() const { return "thread"; }
				virtual void construct();
// 				virtual void init() {};
// 				virtual void process();
// 				virtual void destroy() {};
				virtual Bbool onAddChild( BEntity* entity );
				void wait_Done() { sensor.wait(); }
		// ADMIN WINDOW
				virtual void setAdminWindow( BEntity* entity );
				virtual BEntity* getAdminWindow();
            protected:
                virtual void process_general() {}; // overriding so children aren't processed on main thread
                virtual void process();

				void wait_startTick() { sensor.wait_start();  }
				void signal_Done() { sensor.signal_done(); }
			private:
				void signal_startTick() { sensor.start(); }
				void operator()( );
				
				std::thread m_thread;
				BeSensor sensor;
				bool m_flag_exit;
				BEntity* m_commands;
		};

		class BEntityThreadsFinish : public BEntity/*, public BThreadBase*/
		{
			public:
				BEntityThreadsFinish()
				{
					// SET PROCESSING BIT
						setProcessing();
				}
				virtual ~BEntityThreadsFinish();
				const char* class_id() const { return "threads_finish"; }
            protected:
                virtual void process();
			private:
		};

#endif
