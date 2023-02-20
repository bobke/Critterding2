#include "plugin.h"
#include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_timer.h"
#include "be_entity_rng.h"
#include <fstream>
// #include <iostream>


	void CPUInfo::construct()
	{
		// M_TIMER
			if ( m_timer_ms_total == 0 )
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
				m_timer_ms_total = timer->getChild("ms_total", 1);
			}

		// SET TIMER
// 			m_timer.mark();
// 			m_last_processed = m_timer.getTotalMilliSeconds();
			m_last_processed = 0;
		
		// CPU STATS
			std::ifstream proc("/proc/stat");
			BEntity* current_cpu;
			BEntity* raw;

			while(getline(proc, m_line), !proc.fail())
			{
				if(m_line.substr(0, 3) == "cpu")
				{
// 					std::cout << std::endl;

					// GET TITLE PIECE AND ADD CHILD
						m_split_stringstream.str(m_line);
						if ( getline( m_split_stringstream, m_piece, ' ' ) )
						{
// 							std::cout << m_piece << std::endl;
							
// 							if ( m_piece == "cpu" )
// 								m_piece = "composite";

							current_cpu = addChild( m_piece, new BEntity() );
							raw = current_cpu->addChild( "workload_raw", new BEntity() );
							
							// VALUE STORAGE

								raw->addChild( "user", new BEntity_uint() ); // normal processes executing in user mode
								raw->addChild( "nice", new BEntity_uint() ); // niced processes executing in user mode
								raw->addChild( "system", new BEntity_uint() ); // processes executing in kernel mode
								raw->addChild( "idle", new BEntity_uint() ); // twiddling thumbs
								raw->addChild( "iowait", new BEntity_uint() ); // In a word, iowait stands for waiting for I/O to complete. But there are several problems:
										// CPU will not wait for I/O to complete, iowait is the time that a task is waiting for I/O to complete. When CPU goes into idle state for outstanding task I/O, another task will be scheduled on this CPU.
										// In a multi-core CPU, the task waiting for I/O to complete is not running on any CPU, so the iowait of each CPU is difficult to calculate.
										// The value of iowait field in /proc/stat will decrease in certain conditions.
										// So, the iowait is not reliable by reading from /proc/stat.
								raw->addChild( "irq", new BEntity_uint() ); // servicing interrupts
								raw->addChild( "softirq", new BEntity_uint() ); // servicing softirqs
								raw->addChild( "steal", new BEntity_uint() ); // involuntary wait
								raw->addChild( "guest", new BEntity_uint() ); // running a normal guest
								raw->addChild( "guest_nice", new BEntity_uint() ); // running a niced guest
								
								
							// PERCENTAGE STORAGE

							BEntity* perc = current_cpu->addChild( "workload_percent", new BEntity() );
								perc->addChild( "perc_user", new BEntity_float() );
								perc->addChild( "perc_nice", new BEntity_float() );
								perc->addChild( "perc_system", new BEntity_float() );
								perc->addChild( "perc_idle", new BEntity_float() );
								perc->addChild( "perc_iowait", new BEntity_float() ); 
								perc->addChild( "perc_irq", new BEntity_float() );
								perc->addChild( "perc_softirq", new BEntity_float() );
								perc->addChild( "perc_steal", new BEntity_float() );
								perc->addChild( "perc_guest", new BEntity_float() );
								perc->addChild( "perc_guest_nice", new BEntity_float() );

							// EACH NUMBER THAT FOLLOWS SET THE VALUE that is the next piece
								const auto& cpu_children_vector = raw->children();
								auto child_it = cpu_children_vector.begin();
								while ( getline( m_split_stringstream, m_piece, ' ' ) )
								{
									// ignore multispaces
									if ( m_piece == "" )
										continue;

		// 							// FIXME to int
// 										std::cout << "setting " << (*child_it)->name() << " to " << m_piece << std::endl;
										(*child_it)->set( Buint(std::stoul(m_piece)) );
										++child_it;
								}
// 								std::cout << std::endl;
							
						}



					m_split_stringstream.clear();
				}
			}
			
			
		// CPU FREQUENCIES
		{
			unsigned int cpu_counter(0);
			std::ifstream proc2("/proc/cpuinfo");
			while(getline(proc2, m_line), !proc2.fail())
			{
				if(m_line.substr(0, 7) == "cpu MHz")
				{
					std::stringstream name;
					name << "cpu" << cpu_counter;
// 					std::cout << "looking for " << name.str() << std::endl;
					BEntity* cpu = getChild(name.str().c_str(), 1);
					if ( cpu )
					{
						// GET TITLE PIECE AND ADD CHILD
							m_split_stringstream.str(m_line);
							if ( getline( m_split_stringstream, m_piece, ' ' ) )  // cpu
							if ( getline( m_split_stringstream, m_piece, ' ' ) )  // MHz
							if ( getline( m_split_stringstream, m_piece, ' ' ) )  // number
							{
	// 							std::cout << m_piece << std::endl;
// 									cpu->addChild( "mhz", new BEntity_uint() )->set( Buint(std::stoul(m_piece)) ); // normal processes executing in user mode
									cpu->addChild( "mhz", new BEntity_uint() )->set( Buint(0) ); // normal processes executing in user mode
									cpu->addChild( "mhz_highest", new BEntity_uint() )->set( Buint(0) ); // normal processes executing in user mode
							}
							m_split_stringstream.clear();

						++cpu_counter;
					}
				}
			}
		}
	}

	void CPUInfo::process()
	{
/*		
		// MARK TIMER
			m_timer.mark();*/

		// m_CPUInfo
			Buint time_elapsed = m_timer_ms_total->get_uint() - m_last_processed;
// 			Buint time_interval = 200;
			Buint time_interval = 10;
			

		if ( time_elapsed >= time_interval ) // must be multiples of 10 because stat counts in 10ms
		{

			// ROUND UP TIME_ELAPSED
				while ( time_elapsed % time_interval != 0 )
					--time_elapsed;

			// CPU STATS

				std::ifstream proc("/proc/stat");

				BEntity* current_cpu(0);
				BEntity* raw(0);
				BEntity* percent(0);

				while(getline(proc, m_line), !proc.fail())
				{
					if(m_line.substr(0, 3) == "cpu")
					{
						// GET TITLE AND ADD CHILD
							m_split_stringstream.str(m_line);
							if ( getline( m_split_stringstream, m_piece, ' ' ) )
							{
// 								if ( m_piece == "cpu" )
// 									m_piece = "composite";

								current_cpu = getChild(m_piece.c_str());

								raw = current_cpu->getChild( "workload_raw", 1 );
								percent = current_cpu->getChild( "workload_percent", 1 );
// 								raw = current_cpu->getChild( "workload_raw" );
							}

						// CONTINUE FOR EACH NUMBER
							const auto& cpu_children_vector = raw->children();
							auto child_it = cpu_children_vector.begin();
							while ( getline( m_split_stringstream, m_piece, ' ' ) )
							{
								// ignore multispaces
									if ( m_piece == "" )
										continue;

								Buint piece_uint( std::stoul(m_piece) );
								Buint previous_uint( (*child_it)->get_uint() );
								Bint difference( piece_uint - previous_uint );

								// RAW
									if ( difference > 0 )
									{
// 										std::cout << "DIFF " << difference << " over " << time_elapsed << std::endl;
										// get child
											BEntity* diff_child = raw->getChild( (*child_it)->name().c_str() );
										// SET
											diff_child->set( Buint(difference) );
									}

								// PERCENT
									if ( difference < 0 )
										difference = 0;

									Bfloat value = 1000.0f / ((float)time_elapsed) * ((float)difference);;

									if ( current_cpu->name() == "cpu" )
									{
										value /= 32;
									}

									if ( value > 100.0f )
									{
// 										std::cout << "overflow " << value << std::endl;
										value = 100.0f;
									}

									// get child
										std::string diff_string("perc_");
										diff_string.append( (*child_it)->name() );
										BEntity* perc_store = percent->getChild( diff_string.c_str() );

									// SET
										perc_store->set( value );

// 								// TEST HACK THIS OVERRIDES perc_idle
// 
// 									// FORMULA
// 										// average idle percentage X % = ( idle * 100 ) / ( user + nice + system + idle + iowait + irq + softirq )
// 
// 									if ( perc_store->name() == "perc_guest_nice" )
// 									{
// // 										std::cout << "perc_store->name() == perc_guest_nice" << std::endl;
// 										
// 										Bfloat sum_busy =
// 										  percent->getChild("perc_user")->get_float()
// 										+ percent->getChild("perc_nice")->get_float()
// 										+ percent->getChild("perc_system")->get_float()
// 										+ percent->getChild("perc_iowait")->get_float()
// 										+ percent->getChild("perc_irq")->get_float()
// 										+ percent->getChild("perc_softirq")->get_float()
// 										+ percent->getChild("perc_steal")->get_float()
// 										+ percent->getChild("perc_guest")->get_float()
// 										+ percent->getChild("perc_guest_nice")->get_float();
// 										
// 										if ( sum_busy > 0.0f )
// 										{
// 											Bfloat test = (percent->getChild("perc_idle")->get_float() * 1000) / sum_busy / time_elapsed;
// 											std::cout << "test float " << test << std::endl;
// 											percent->getChild("perc_idle")->set( test );
// 										}
// 										else
// 										{
// 											percent->getChild("perc_idle")->set( 100.0f );
// 										}
// 									}


								// UPDATE THE CHILD
									(*child_it)->set( piece_uint );
							
								// NEXT CHILD
									++child_it;
							}

						m_split_stringstream.clear();
					}
				}

			// CPU FREQUENCIES
				unsigned int cpu_counter(0);
				std::ifstream proc2("/proc/cpuinfo");
				while(getline(proc2, m_line), !proc2.fail())
				{
					if(m_line.substr(0, 7) == "cpu MHz")
					{
						std::stringstream name;
						name << "cpu" << cpu_counter;
	// 					std::cout << "looking for " << name.str() << std::endl;
						BEntity* cpu = getChild(name.str().c_str(), 1);
						if ( cpu )
						{
							// GET TITLE PIECE AND ADD CHILD
								m_split_stringstream.str(m_line);
								if ( getline( m_split_stringstream, m_piece, ' ' ) )  // cpu
								if ( getline( m_split_stringstream, m_piece, ' ' ) )  // MHz
								if ( getline( m_split_stringstream, m_piece, ' ' ) )  // number
								{
		// 							std::cout << m_piece << std::endl;
										BEntity* mhz = cpu->getChild( "mhz" ); // normal processes executing in user mode
										BEntity* mhz_highest = cpu->getChild( "mhz_highest" ); // normal processes executing in user mode
										mhz->set( Buint(std::stoul(m_piece)) ); // normal processes executing in user mode
										
									// CHECK AND UPDATE HIGHEST MHZ
										if ( mhz->get_uint() >  mhz_highest->get_uint() )
										{
// 											std::cout << "new highest mhz for cpu " << name.str() << ": from " << mhz_highest->get_uint() << " to " << mhz->get_uint();
// 											std::cout << " : diff:  " << mhz->get_uint() - mhz_highest->get_uint();
// 											std::cout << std::endl;
											mhz_highest->set( mhz->get_uint() );
										}
								}
								m_split_stringstream.clear();

							++cpu_counter;
						}
					}
				}

			// UPDATE LAST_PROCESSED
				m_last_processed = m_timer_ms_total->get_uint();
		}
	}


// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, CPU
		, BRNG
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::CPU, "CPUInfo" );
					i.addClass( parent, CLASS::BRNG, "Brng" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::CPU )
					i = new CPUInfo();
				else if ( type == CLASS::BRNG )
					i = new Brng();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
