#include "plugin.h"
#include "kernel/be_plugin_interface.h"

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, THREAD
		, THREADS_FINISH
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::THREAD, "thread" );
					i.addClass( parent, CLASS::THREADS_FINISH, "threads_finish" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::THREAD )
					i = new BEntityThread();

				else if ( type == CLASS::THREADS_FINISH )
					i = new BEntityThreadsFinish();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
		delete p;
	}
	
	
	BEntityThread::BEntityThread()
	: BEntityTop(true)
	, m_flag_exit(false)
	{
		// std::cout << " launching thread" << std::endl;
		m_thread = std::thread( &BEntityThread::operator(), this );
	}
	
	void BEntityThread::construct()
	{
		spawnCommandBuffer();
	}

	BEntityThread::~BEntityThread() {
// 		std::cout << " killing thread " << id() << std::endl;
		sensor.wait();
		m_flag_exit=true;
		sensor.start();
		m_thread.join();
	}
	
	void BEntityThread::process()
	{
// 		std::cout << "BEntityThread::process() : " << m_id << std::endl;
		signal_startTick();
	}

	Bbool BEntityThread::onAddChild( BEntity* entity )
	{
		// passthrough to this parent
		if ( parent() != 0 )
			parent()->onAddChild(entity);
		return true;
	}

	void BEntityThread::operator()( )
	{
		// RECONSTRUCT PROCESS LIST IF NEEDED
// 			reConstructProcessList( this );  // HACK

		while ( 1 )
		{
			signal_Done();

			wait_startTick();

			if ( m_flag_exit )
				break;
			

			// PROCESS
			m_processor->run();

		}
		signal_Done();
	}
	
	// ADMIN WINDOW
		BEntity* BEntityThread::getAdminWindow()
		{
			return parent()->getAdminWindow();
		}
		void BEntityThread::setAdminWindow( BEntity* entity )
		{
			parent()->setAdminWindow( entity );
		}

	void BEntityThreadsFinish::process()
	{
		// FIXME DISABLED THIS AT IMPORT
		// after between processing all threads process all command buffers

// 		parent()->process_children_post();
// 
		BEntity* parent = this->parent();
		if ( parent )
		{
			// WAIT FOR ALL THREADS TO FINISH
			for_all_children_of(parent)
			{
				BEntityThread* thread = dynamic_cast<BEntityThread*>(*child);
				if ( thread )
				{
// 					std::cout << "waiting for " << thread->id() << " to finish: ";
					thread->wait_Done();
// 					std::cout << "done" << std::endl;
				}
			}
			
			// PROCESS ALL THREAD COMMAND BUFFERS
			for_all_children_of2(parent)
			{
				BEntityThread* thread = dynamic_cast<BEntityThread*>(*child2);
				if ( thread )
				{
					thread->process_and_clear_command_buffer();
					// RECONSTRUCT PROCESS LIST IF NEEDED
					thread->reConstructProcessList( thread );
				}
			}
		}
	}
	
	void BeSensor::start()
	{
		m_flag_done = false;
		std::lock_guard<std::mutex> lock( start_condition_mutex );
		m_flag_start = true;
		start_condition.notify_one();
	}

	void BeSensor::wait()
	{
		std::unique_lock<std::mutex> lock( done_condition_mutex );
		while( !m_flag_done )
			done_condition.wait(lock);
	}
	
	void BeSensor::wait_start()
	{
		std::unique_lock<std::mutex> lock( start_condition_mutex );
		while( !m_flag_start )
			start_condition.wait(lock);
		m_flag_start = false;
	}
	void BeSensor::signal_done()
	{
		std::lock_guard<std::mutex> done_lock( done_condition_mutex );
			m_flag_done = true;
		done_condition.notify_one();
	}
	
