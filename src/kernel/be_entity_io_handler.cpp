#include "be_entity_io_handler.h"
#include "be_entity_core_types.h"
#include <iostream> // NOTE: KEEPING THIS ONE HERES SAVES 3 SECONDS COMPILE TIME

	// CONSTRUCTORS / DESTRUCTOR

		BEOutputConnectionLocal::BEOutputConnectionLocal( BEntity* const output_entity, BEntity* const input_entity )
		: BEOutputConnectionBase( output_entity, input_entity) {};
		
		bool BEOutputConnectionLocal::commit()
		{
// 			std::cout << "EOutputConnectionLocal::commit(): try APPLY: i:" << m_input_entity->get_uint() << " o:" << m_output_entity->get_uint() << std::endl;
			if ( m_output_entity->apply( m_input_entity ) )
				return true;

			// FIXME if the value above doesn't change, this gets triggered when it shouldn't, then copy binary test fails
// 			// std::cout << "BEOutputConnectionLocal::commit() apply returned false so copy entity" << std::endl;
// 			std::cout << "EOutputConnectionLocal::commit(): try SET" << std::endl;
// 			return m_output_entity->set( m_input_entity );
			return false;
		}
		
		
		bool BEOutputConnectionCommandBuffer::commit()
		{
			// get command buffer
// 			auto top_of_output_entity = m_output_entity->getNearestTop();
			
			// add command to the top's command buffer
			// add reference to output_entity with a child, the target input_entity
			
			// make command with output and input for command_buffer
			auto command_buffer = m_output_entity->getCommandBuffer();
			auto command = command_buffer->addChild("commitValue", new BEntity_reference());
			command->set( m_output_entity );
			command->addChild("entity_with_input", new BEntity_reference())->set( m_input_entity );
			
			
// 			// std::cout << "EOutputConnectionLocal::commit()" << std::endl;
// 			if ( m_output_entity->apply( m_input_entity ) )
// 			{
// 				return true;
// 			}

			// std::cout << "BEOutputConnectionCommandBuffer::commit() apply returned false so copy entity" << std::endl;
			
			// m_output_entity->set( m_input_entity ); // FIXME CREATE THE COMMAND FOR THIS
			return true;
		}		
		
		BEOutput::~BEOutput()
		{
			for ( auto it(m_connections.begin()); it != m_connections.end(); ++it )
			{
				delete  *it;
			}
		}
		void BEOutput::addConnection( BEOutputConnectionBase* connection )
		{
			m_connections.push_back( connection );
		}

		bool BEOutput::commit()
		{
			// catch in case this output gets removed and m_connections is no longer accessible

			// HACK MAKE COPY OF CONNECTIONS BEFORE COMMIT, for if when removed it doesn't crash?
// 					const auto conn_copy(m_connections);
// 					for ( auto it(conn_copy.begin()); it != conn_copy.end(); ++it )
			
			// FIXME hackish
			bool committed(false);
			for ( auto it(m_connections.begin()); it != m_connections.end(); ++it )
			{
				committed = (*it)->commit();
			}
// 			std::cout << "BEOutput::commit returning true" << std::endl;
			return committed;
		}
				
// 		inline void BEOutput::commit()
// 		{
// 			for ( auto it(m_connections.begin()); it != m_connections.end(); ++it )
// 			{
// 				(*it)->commit();
// // 				m_owner->apply( (*it)->getConnectedToEntity() );
// 			}
// 		}

		void BEOutput::removeConnection( BEntity* e )
		{
			for ( auto it(m_connections.begin()); it != m_connections.end(); )
			{
				BEntity* t_input( (*it)->getInputEntity() );
				if ( t_input->id() != 0 )
				{
					if ( t_input->id() == e->id() )
					{
						delete *it;
						m_connections.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
		}

		void BEInput::removeConnection( BEntity* e )
		{
			for ( auto it(m_connected_outputs.begin()); it != m_connected_outputs.end(); )
			{
				// REMOVE OUTPUTS WHEN MATCH
				if ( (*it)->id() == e->id() )
				{
					m_connected_outputs.erase(it);
				}
				else
				{
					++it;
				}
			}
		}


	// CONSTRUCTORS / DESTRUCTOR

		B_IO_Handler::B_IO_Handler() 
		: m_input(0)
		, m_output(0)
		{
		}

		B_IO_Handler::~B_IO_Handler() 
		{
			if ( m_input != 0 )
				delete m_input;
			if ( m_output != 0 )
				delete m_output;
		}

	// INPUT
		void B_IO_Handler::setInput( BEInput* input)
		{
			m_input = input;
		}

	// OUTPUT
		void B_IO_Handler::setOutput( BEOutput* output)
		{
			m_output = output;
		}

		bool B_IO_Handler::hasInput() const
		{
			if ( m_input != 0 )
			{
				return true;
			}
			return false;
		}

		bool B_IO_Handler::hasOutput() const
		{
			if ( m_output != 0 )
			{
				return true;
			}
			return false;
		}

	// CONNECTING
		void B_IO_Handler::connectServerServer(BEntity* entity_with_output, BEntity* entity_with_input, const bool force_local)
		{
			// checks
				if ( entity_with_output == entity_with_input )
				{
					std::cout << "B_IO_Handler::connectServerServer::entity connects to itself?" << std::endl;
					return;
				}

			// CREATE OUTPUT FOR SENDER
				if ( !getOutput() )
				{
					// std::cout << "B_IO_Handler::connectServerServer::creating output for " << entity_with_output->id() << std::endl;
					setOutput( new BEOutput(entity_with_output) );
				}
			
			// CREATE INPUT FOR RECEIVER
				entity_with_input->spawnInput();
			
			// create connection
				BEOutputConnectionBase* conn;
				
				// !!!!!!!!!
				// FIXME THIS IS NOT ENOUGH, IF A COMES BEFORE B IT SHOULD BE A LOCAL CONNECTION
				// !!!!!!!!!

				// auto output_is_top = dynamic_cast<BEntityTop*>( entity_with_output->getNearestTop() );

				// force_local OR TOPS ARE THE SAME OR OUTPUT IS NOT THREAD
				if ( force_local || entity_with_output->getNearestTop() == entity_with_input->getNearestTop() || entity_with_output->class_id() != std::string("thread")  )
				{
					conn = new BEOutputConnectionLocal( entity_with_output, entity_with_input );
				}
				// DIFFERENT TOPS
				else
				{
					// JUST IF ENTITY OUTPUT TOP == THREAD THEN USE REMOTE CONNECTION
					// FIXME EDGE CASE, if child of the same parent, race condition possible
					// maybe should not be fixed, it's just bad practice anyway
					
					// check if top has remote connection
					if ( entity_with_output->getNearestTopConnectionType() == true )
					{
						// std::cout << "tops do not match and remote requested: command_buffer connection" << std::endl;
						conn = new BEOutputConnectionCommandBuffer( entity_with_output, entity_with_input );
					}
					else
					{
						// it's a local connection again, FIXME
						conn = new BEOutputConnectionLocal( entity_with_output, entity_with_input );
					}
				}
			
			// connect local serverentity output with local proxy cliententity input
				getOutput()->addConnection( conn );

			// make input aware of connection
				conn->getInputEntity()->getInput()->m_connected_outputs.push_back( entity_with_output );

			// FIXME neeeeded ?
// 				conn->getInputEntity()->apply(entity_with_output);

// 	// FIXME TODO
// 			// adjust admin window connections
// 				adjust_admin_connections();
// 
// 			// also for one with input
// 				if ( entity_with_input )
// 					entity_with_input->adjust_admin_connections();

// 			return conn;
		}

// 	// DISCONNECTING
// 		void B_IO_Handler::disconnectServerServer(BEntity* entity_with_output, BEntity* entity_with_input)
// 		{
// 				std::cout << "B_IO_Handler::disconnectServerServer " << entity_with_output->id() << " from " << entity_with_input->id() << std::endl;
// 			// checks
// 				if ( !entity_with_output->hasOutput() )
// 				{
// 					std::cout << "B_IO_Handler::disconnectServerServer::entity has no output" << std::endl;
// 					return;
// 				}
// 				else if ( !entity_with_input->hasInput() )
// 				{
// 					std::cout << "B_IO_Handler::disconnectServerServer::entity has no input" << std::endl;
// 					return;
// 				}
// 				else if ( entity_with_output->id() == entity_with_input->id() )
// 				{
// 					std::cout << "B_IO_Handler::disconnectServerServer::entity disconnects from itself?" << std::endl;
// 					return;
// 				}
// 
// 				getOutput()->removeConnection( entity_with_input );
// // 				entity_with_input->getInput()->removeConnection( entity_with_output );
// 		}
	
