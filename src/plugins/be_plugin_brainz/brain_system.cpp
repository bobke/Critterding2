#include "brain_system.h"
#include "kernel/be_entity_io_handler.h"
#include <iostream>
#include <iomanip>
 
	void BrainSystem::construct()
	{
		auto settings = addChild( "settings", new BEntity() );
		m_mutation_chance = settings->addChild( "mutation_chance", new BEntity_uint() );
		m_mutationruns_min = settings->addChild( "mutationruns_min", new BEntity_uint() );
		m_mutationruns_max = settings->addChild( "mutationruns_max", new BEntity_uint() );
		m_neuron_adam_min = settings->addChild( "neuron_adam_min", new BEntity_uint() );
		m_neuron_adam_max = settings->addChild( "neuron_adam_max", new BEntity_uint() );
		m_neuron_firingthreshold_min = settings->addChild( "neuron_firingthreshold_min", new BEntity_int() );
		m_neuron_firingthreshold_max = settings->addChild( "neuron_firingthreshold_max", new BEntity_int() );
		m_neuron_firingweight_min = settings->addChild( "neuron_firingweight_min", new BEntity_int() );
		m_neuron_firingweight_max = settings->addChild( "neuron_firingweight_max", new BEntity_int() );
		m_synapse_weight_min = settings->addChild( "synapse_weight_min", new BEntity_int() );
		m_synapse_weight_max = settings->addChild( "synapse_weight_max", new BEntity_int() );
		m_synapse_adam_min = settings->addChild( "synapse_adam_min", new BEntity_uint() );
		m_synapse_adam_max = settings->addChild( "synapse_adam_max", new BEntity_uint() );

		auto mutation_weights = settings->addChild( "mutation_weights", new BEntity() );
		m_mutationweight_neuron_add = mutation_weights->addChild( "m_mutationweight_neuron_add", new BEntity_uint() );
		m_mutationweight_neuron_remove = mutation_weights->addChild( "m_mutationweight_neuron_remove", new BEntity_uint() );
		m_mutationweight_neuron_alter_firingweight = mutation_weights->addChild( "m_mutationweight_neuron_alter_firingweight", new BEntity_uint() );
		m_mutationweight_neuron_alter_firingthreshold = mutation_weights->addChild( "m_mutationweight_neuron_alter_firingthreshold", new BEntity_uint() );
		m_mutationweight_neuron_alter_firingweight_slightly = mutation_weights->addChild( "m_mutationweight_neuron_alter_firingweight_slightly", new BEntity_uint() );
		m_mutationweight_neuron_alter_firingthreshold_slightly = mutation_weights->addChild( "m_mutationweight_neuron_alter_firingthreshold_slightly", new BEntity_uint() );
		m_mutationweight_synapse_add_neuron_to_neuron = mutation_weights->addChild( "m_mutationweight_synapse_add_neuron_to_neuron", new BEntity_uint() );
		m_mutationweight_synapse_add_neuron_to_output = mutation_weights->addChild( "m_mutationweight_synapse_add_neuron_to_output", new BEntity_uint() );
		m_mutationweight_synapse_add_input_to_neuron = mutation_weights->addChild( "m_mutationweight_synapse_add_input_to_neuron", new BEntity_uint() );
		m_mutationweight_synapse_remove_from_neuron = mutation_weights->addChild( "m_mutationweight_synapse_remove_from_neuron", new BEntity_uint() );
		m_mutationweight_synapse_remove_from_output = mutation_weights->addChild( "m_mutationweight_synapse_remove_from_output", new BEntity_uint() );
		m_mutationweight_synapse_alter_weight = mutation_weights->addChild( "m_mutationweight_synapse_alter_weight", new BEntity_uint() );
		m_mutationweight_synapse_alter_weight_slightly = mutation_weights->addChild( "m_mutationweight_synapse_alter_weight_slightly", new BEntity_uint() );
		m_slightly_percent = mutation_weights->addChild( "m_slightly_percent", new BEntity_uint() );
		
		m_mutation_chance->set( Buint(8) );
		m_mutationruns_min->set( Buint(1) );
		m_mutationruns_max->set( Buint(16) );
		// m_mutation_chance->set( Buint(30) );
		// m_mutationruns_min->set( Buint(1) );
		// m_mutationruns_max->set( Buint(20) );
		
		
		m_neuron_firingthreshold_min->set( Bint(-2000) );
		m_neuron_firingthreshold_max->set( Bint(2000) );
		m_neuron_firingweight_min->set( Bint(-400) ); 
		m_neuron_firingweight_max->set( Bint(400) ); 

		m_synapse_weight_min->set( Bint(-2000) ); 
		m_synapse_weight_max->set( Bint(2000) ); 

		// m_neuron_adam_min->set( Buint(30) );
		// m_neuron_adam_max->set( Buint(60) );
		// m_synapse_adam_min->set( Buint(5) );
		// m_synapse_adam_max->set( Buint(10) );

		// m_neuron_adam_min->set( Buint(20) );
		// m_neuron_adam_max->set( Buint(40) );
		// m_synapse_adam_min->set( Buint(4) );
		// m_synapse_adam_max->set( Buint(10) );

		m_neuron_adam_min->set( Buint(50) );
		m_neuron_adam_max->set( Buint(100) );
		m_synapse_adam_min->set( Buint(2) );
		m_synapse_adam_max->set( Buint(6) );
		
		m_mutationweight_neuron_add->set( Buint(25) );
		m_mutationweight_neuron_remove->set( Buint(25) );
		m_mutationweight_neuron_alter_firingweight->set( Buint(25) );
		m_mutationweight_neuron_alter_firingthreshold->set( Buint(25) );
		m_mutationweight_neuron_alter_firingweight_slightly->set( Buint(50) );
		m_mutationweight_neuron_alter_firingthreshold_slightly->set( Buint(50) );
		m_mutationweight_synapse_add_neuron_to_neuron->set( Buint(50) );
		m_mutationweight_synapse_add_neuron_to_output->set( Buint(10) );
		m_mutationweight_synapse_add_input_to_neuron->set( Buint(10) );
		m_mutationweight_synapse_remove_from_neuron->set( Buint(50) );
		m_mutationweight_synapse_remove_from_output->set( Buint(10) );
		m_mutationweight_synapse_alter_weight->set( Buint(80) );
		m_mutationweight_synapse_alter_weight_slightly->set( Buint(160) );

		m_slightly_percent->set( Buint(5) );
		
		m_unit_container = addChild( "unit_container", new BEntity() );
		
		m_rng = parent()->parent()->getChild( "random_number_generator" ); // FIXME PREFETCH
	}

	void BrainSystem::process()
	{
		// std::cout << "brain process " << id() <<  std::endl;
		// fpr each brain: (*child)
		for_all_children_of( m_unit_container )
		{
			auto brain = dynamic_cast<BBrain*>(*child);
			bool first( true );

			// loop through all neurons, check if threshold breached
			for_all_children_of2( brain->m_neurons )
			{
				auto neuron = dynamic_cast<BNeuron*>( *child2 );

				if ( neuron )
				{
					// HACK FIRE FIRST NEURON
					if ( first )
					{
						neuron->m_firingWeight->onUpdate();
						first = false;
					}

					const float threshold( neuron->m_firingThreshold->get_float() ); //FIXME OPTIMIZE
					const float potential( neuron->get_float() );
					
					if ( threshold > 0.0f )
					{
						if ( potential >= threshold )
						{
							neuron->m_firing->set( true );
							neuron->set( 0.0f );
						}
						else if ( potential < 0.0f )
						{
							neuron->set( 0.0f );
						}
					}
					else if ( threshold < 0.0f )
					{
						if ( potential <= threshold )
						{
							neuron->m_firing->set( true );
							neuron->set( 0.0f );
						}
						else if ( potential > 0.0f )
						{
							neuron->set( 0.0f );
						}
					}
				}
			}

			// loop through all neurons, if threshold breaches send signal
			for_all_children_of3( brain->m_neurons )
			{
				auto neuron =  dynamic_cast<BNeuron*>(*child3);
				if ( neuron )
				{
					auto isFiring = neuron->m_firing;
					if ( isFiring->get_bool() )
					{
						// std::cout << "FIRING NEURON: " << neuron->id() << std::endl;
						isFiring->set( false );
						neuron->m_firingWeight->onUpdate();
					}
				}
			}
		}
	}

	BEntity* BrainSystem::addNeuron( BEntity* neurons )
	{
		auto neuron = new BNeuron();
		neurons->addChild( "neuron", neuron );

		// FIRING THRESHOLD
			int threshold(0);
			m_rng->set( "min", m_neuron_firingthreshold_min->get_int() );
			m_rng->set( "max", m_neuron_firingthreshold_max->get_int() );
			while (threshold == 0)
			{
				threshold = m_rng->get_int();
			}
			neuron->m_firingThreshold->set( 0.001f * threshold );
		
		// FIRING WEIGHT
			int weight(0);
			m_rng->set( "min", m_neuron_firingweight_min->get_int() );
			m_rng->set( "max", m_neuron_firingweight_max->get_int() );
			while ( weight == 0 )
			{
				weight = m_rng->get_int();
			}
			neuron->m_firingWeight->set( 0.001f * weight );
			
		// FIRED BOOL
			neuron->m_firing->set( false );
			
			return neuron;
	}
	
	// FIXME INTO JUST AN ENTITY CONSTRUCT
	BEntity* BrainSystem::getChildCustom( BEntity* brain, const char* name )
	{
		if ( name == std::string("new") )
		{
			if ( m_rng )
			{
				m_rng->set( "min", (Bint)m_neuron_adam_min->get_uint() );
				m_rng->set( "max", (Bint)m_neuron_adam_max->get_uint() );
				auto numberOfNeuronsToCreate = m_rng->get_int();

				auto neurons = brain->getChild( "neurons", 1 );

				// POPULATE BRAIN WITH NEURONS
				for ( Bint i(0); i <= numberOfNeuronsToCreate; ++i )
				{
					addNeuron( neurons );
				}
				
				// POPULATE NEURONS WITH SYNAPSES
				for_all_children_of( neurons )
				{
					auto neuron = *child;
					
					// CONNECT THIS NEURON FOR SURE, connect this neuron to a random neuron
						// pick random neuron
						auto random_neuron = randomChild( neurons );
						// std::cout << "for neuron " << neuron->id() << " we picked " << random_neuron->id() << " to connect to " << std::endl;
						
						// add synapse to randomly picked neuron
						auto synapse = addSynapse( random_neuron );
						// auto synapse = random_neuron->getChild( "synapses", 1 )->addChild( "synapse", new Synapse() );
						// m_rng->set( "min", m_synapse_weight_min->get_int() );
						// m_rng->set( "max", m_synapse_weight_max->get_int() );
						// synapse->addChild( "weight", new BEntity_float() )->set( 0.001f * m_rng->get_int() );

						// connect neuron to synapse
						neuron->getChild("firingWeight", 1)->connectServerServer( synapse );

					// ADD CONNECTIONS TO NEURONS, connect random neurons to this neuron
						//number of synapses, -1 but at least one
						m_rng->set( "min", Bint( m_synapse_adam_min->get_uint() ) );
						m_rng->set( "max", Bint( m_synapse_adam_max->get_uint() ) );
						// -1 because already made sure previous new neuron was connected
						int number_synapses = m_rng->get_int() - 1;
						// at least one
						if ( number_synapses <= 0 )
						{
							number_synapses = 1;
						}

						// add synapses
						do_times( (Buint)number_synapses )
						{
							// PICK RANDOM NEURON TO CONNECT FROM
							auto random_neuron = randomChild( neurons );

							// ADD SYNAPSE TO THIS NEURON AND CONNECT FROM RANDOM NEURON TO SYNAPSE
							auto synapse = addSynapse( neuron );

							// connect neuron to synapse
							random_neuron->getChild("firingWeight", 1)->connectServerServer( synapse );
						}
				}
				
				// CONNECT NEURONS TO OUTPUTS
				auto outputs = brain->getChild( "outputs", 1 );
				for_all_children_of2( outputs )
				{
					auto referred_list = (*child2)->get_reference();

					// for each output, link a neuron to it
					for_all_children_of3( referred_list )
					{
						BEntity* to_connect_to;
						auto ref_check = dynamic_cast<BEntity_reference*>( (*child3) );
						if ( ref_check )
							to_connect_to = (*child3)->get_reference();
						else
							to_connect_to = *child3;
						
						// PICK RANDOM NEURONS TO CONNECT FROM
						do_times(2)
						{
							// PICK ANOTHER RANDOM NEURON TO CONNECT FROM
							auto random_neuron = randomChild( neurons );
							random_neuron->getChild("firingWeight", 1)->connectServerServer( to_connect_to );
						}

					}
				}
				
				// CONNECT INPUTS TO NEURONS
				auto inputs = brain->getChild( "inputs", 1 );
				for_all_children_of3( inputs )
				{
					// PICK ANOTHER RANDOM NEURON TO CONNECT FROM
					auto random_neuron = randomChild( neurons );

					// add synapse to randomly picked neuron
					auto synapse = addSynapse( random_neuron );

// 					// VISION WEIGHT HACK
// 					if ( (*child3)->name() == "vision_value_R" || (*child3)->name() == "vision_value_G" || (*child3)->name() == "vision_value_B" || (*child3)->name() == "vision_value_A" )
// 					{
// 						// std::cout << "vision input " << std::endl;
// 						
// 						// kick weight down a notch
// 						auto weightEntity = synapse->getChild("weight", 1);
// 						if ( weightEntity )
// 						{
// 							// std::cout << "from: " << weightEntity->get_float();
// 							weightEntity->set( 0.2f * weightEntity->get_float() );
// 							// std::cout << "  to: " << weightEntity->get_float() << std::endl;
// 						}
// 					}

					// connect input to neuron
					(*child3)->connectServerServer( synapse );
				}
				
				
				
			}
			return brain;
		}
		
		return 0;
	}
	
	BEntity* BrainSystem::addSynapse( BEntity* neuron )
	{
		// add synapse to randomly picked neuron
		auto synapse = dynamic_cast< BNeuron* >( neuron )->m_synapses->addChild( "synapse", new Synapse() );
		m_rng->set( "min", m_synapse_weight_min->get_int() );
		m_rng->set( "max", m_synapse_weight_max->get_int() );
		synapse->addChild( "weight", new BEntity_float() )->set( 0.001f * m_rng->get_int() );

		return synapse;
	}

	
	BEntity* BrainSystem::randomChild( const BEntity* parent )
	{
		auto num_children = parent->numChildren();
		if ( num_children > 0 )
		{
			m_rng->set( "min", Bint(0) );
			m_rng->set( "max", Bint( parent->numChildren())-1 );
			return parent->children()[ m_rng->get_int() ];
		}
		else
		{
			return 0;
		}
	}
	
	bool BrainSystem::set( const Bstring& id, BEntity* value )
	{
		if ( id == "mutate" )
		{
			// CHANCE WE MUTATE
			m_rng->set( "min", 1 );
			m_rng->set( "max", 100 );
			if ( (Buint)m_rng->get_int() <= m_mutation_chance->get_uint() )
			{
				// std::cout << "mutate: yes" << std::endl;
				
				// create total sum
				const unsigned int mutation_factors_sum =
					+ m_mutationweight_neuron_add->get_uint()
					+ m_mutationweight_neuron_remove->get_uint()
					+ m_mutationweight_neuron_alter_firingweight->get_uint()
					+ m_mutationweight_neuron_alter_firingthreshold->get_uint()
					+ m_mutationweight_neuron_alter_firingweight_slightly->get_uint()
					+ m_mutationweight_neuron_alter_firingthreshold_slightly->get_uint()
					+ m_mutationweight_synapse_add_neuron_to_neuron->get_uint()
					+ m_mutationweight_synapse_add_neuron_to_output->get_uint()
					+ m_mutationweight_synapse_add_input_to_neuron->get_uint()
					// + m_mutationweight_synapse_add_constraint_to_neuron->getProperty_UInt()
					// + m_mutationweight_synapse_add_eye_to_neuron->getProperty_UInt()
					+ m_mutationweight_synapse_remove_from_neuron->get_uint()
					+ m_mutationweight_synapse_remove_from_output->get_uint()
					+ m_mutationweight_synapse_alter_weight->get_uint()
					+ m_mutationweight_synapse_alter_weight_slightly->get_uint()
				;

				if ( mutation_factors_sum > 0 )
				{
					// RUNS
						m_rng->set( "min", (Bint)m_mutationruns_min->get_uint() );
						m_rng->set( "max", (Bint)m_mutationruns_max->get_uint() );
						const int runs = m_rng->get_int();
						std::cout/* << std::endl */<< " mutate brain runs: " << runs << std::endl;

					// ATTEMPTS
						unsigned int attempts(0);
						unsigned int max_attempts(runs*20);
						
					// ENTITIES
						auto neurons = value->getChild( "neurons", 1 );

					for ( int run(0); run < runs && attempts < max_attempts; ++run )
					{
						++attempts;
						m_rng->set( "min", (Bint)1 );
						m_rng->set( "max", (Bint)mutation_factors_sum );
						unsigned int mode = m_rng->get_int();
						unsigned int modesum(0);

						modesum += m_mutationweight_neuron_add->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								// ADD NEURON
									std::cout << std::setw(3) << run+1 << "  + neuron: " << "\t\t\t\t\t";

									auto neuron = addNeuron( neurons );

								// CONNECT THIS NEURON FOR SURE, connect this neuron to a random neuron
									// pick random neuron
									auto random_neuron = randomChild( neurons );
									// std::cout << "for neuron " << neuron->id() << " we picked " << random_neuron->id() << " to connect to " << std::endl;

									// add synapse to randomly picked neuron
									if ( random_neuron )
									{
										// connect neuron to new synapse
										neuron->getChild("firingWeight", 1)->connectServerServer( addSynapse( random_neuron ) );
									}

								// ADD CONNECTIONS TO NEURONS, connect random neurons to this neuron
									//number of synapses, -1 but at least one
									m_rng->set( "min", Bint( m_synapse_adam_min->get_uint() ) );
									m_rng->set( "max", Bint( m_synapse_adam_max->get_uint() ) );
									// -1 because already made sure previous new neuron was connected
									int number_synapses = m_rng->get_int() - 1;
									// at least one
									if ( number_synapses <= 0 )
									{
										number_synapses = 1;
									}

									// add synapses
									do_times( (unsigned int)number_synapses )
									{
										// THIS GIVES A 1/7 CHANCE THE SYNAPSE IS CONNECTED FROM AN INPUT
										m_rng->set( "min", 1 );
										m_rng->set( "max", 7 );
										
										// CONNECT FROM AN INPUT
										if ( m_rng->get_int() == 1 )
										{
											// PICK RANDOM NEURON TO CONNECT FROM
											auto random_input = randomChild( value->getChild( "inputs", 1 ) );

											// ADD SYNAPSE TO THIS NEURON AND CONNECT FROM RANDOM INPUT TO SYNAPSE
											auto synapse = addSynapse( neuron );

											// connect neuron to synapse
											random_input->connectServerServer( synapse );
										}
										// CONNECT FROM ANOTHER NEURON
										else
										{
											// PICK RANDOM NEURON TO CONNECT FROM
											auto random_neuron = randomChild( neurons );
											
											// ADD SYNAPSE TO THIS NEURON AND CONNECT FROM RANDOM NEURON TO SYNAPSE
											auto synapse = addSynapse( neuron );
											
											// connect neuron to synapse
											random_neuron->getChild("firingWeight", 1)->connectServerServer( synapse );
										}
									}

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_neuron_remove->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								// NEURON -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  - neuron: " << "\t\t\t\t\t";
								// BeEntity::ptr neuron(brain_container->randomChild());

								// get 1 random neuron
								auto random_neuron = randomChild( neurons );

								// remove the neuron
								neurons->removeChild( random_neuron );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_neuron_alter_firingweight->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								std::cout << std::setw(3) << run+1 << "  * neuron firing weight: " << "\t\t\t";
								
								// get 1 random neuron
								auto random_neuron = randomChild( neurons );

								// get weight
								auto firingWeight = random_neuron->getChild( "firingWeight", 1 );

								int weight(0);
								m_rng->set( "min", m_neuron_firingweight_min->get_int() );
								m_rng->set( "max", m_neuron_firingweight_max->get_int() );
								while ( weight == 0 )
								{
									weight = m_rng->get_int();
								}
								firingWeight->set( 0.001f * weight );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_neuron_alter_firingweight_slightly->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								std::cout << std::setw(3) << run+1 << "  * neuron firing weight slightly: " << "\t\t";
								
								// get 1 random neuron
								auto random_neuron = randomChild( neurons );

								// consider our sign
								float sign( -1.0f );
								m_rng->set( "min", (Bint)0 );
								m_rng->set( "max", (Bint)1 );
								if ( m_rng->get_int() == 0 )
									sign = 1.0f;

								// get weight
								auto firingWeight = random_neuron->getChild( "firingWeight", 1 );

								m_rng->set( "min", m_neuron_firingweight_min->get_int() );
								m_rng->set( "max", m_neuron_firingweight_max->get_int() );

								auto rng_value = abs( m_rng->get_int() );

								auto adjust_size = sign * (0.01f * m_slightly_percent->get_uint()) * 0.001f * rng_value;
								
								// get new size of synapse weight
									float new_size = firingWeight->get_float() + adjust_size;

								// check min/max boundaries
									float fmax( 0.001f * m_neuron_firingweight_max->get_int() );
									if ( new_size > fmax )
										new_size = fmax;

									float fmin( 0.001f * m_neuron_firingweight_min->get_int() );
									if ( new_size < fmin )
										new_size = fmin;

								// std::cout << "old firingweight :: " << firingWeight->get_float() << ">" << new_size << " (" << adjust_size << ")";

								firingWeight->set( new_size );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_neuron_alter_firingthreshold->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								std::cout << std::setw(3) << run+1 << "  * neuron firing threshold: " << "\t\t";
								
								// get 1 random neuron
								auto random_neuron = randomChild( neurons );

								// get threshold
								auto firingThreshold = random_neuron->getChild( "firingThreshold", 1 );

								int threshold(0);
								m_rng->set( "min", m_neuron_firingweight_min->get_int() );
								m_rng->set( "max", m_neuron_firingweight_max->get_int() );
								while ( threshold == 0 )
								{
									threshold = m_rng->get_int();
								}
								firingThreshold->set( 0.001f * threshold );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_neuron_alter_firingthreshold_slightly->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								std::cout << std::setw(3) << run+1 << "  * neuron firing threshold slightly: " << "\t";
								
								// get 1 random neuron
								auto random_neuron = randomChild( neurons );

								// consider our sign
								float sign( -1.0f );
								m_rng->set( "min", (Bint)0 );
								m_rng->set( "max", (Bint)1 );
								if ( m_rng->get_int() == 0 )
									sign = 1.0f;

								// get weight
								auto firingThreshold = random_neuron->getChild( "firingThreshold", 1 );

								m_rng->set( "min", m_neuron_firingthreshold_min->get_int() );
								m_rng->set( "max", m_neuron_firingthreshold_max->get_int() );

								auto rng_value = abs( m_rng->get_int() );

								auto adjust_size = sign * (0.01f * m_slightly_percent->get_uint()) * 0.001f * rng_value;
								
								// get new size of synapse weight
									float new_size = firingThreshold->get_float() + adjust_size;

								// check min/max boundaries
									float fmax( 0.001f * m_neuron_firingthreshold_max->get_int() );
									if ( new_size > fmax )
										new_size = fmax;

									float fmin( 0.001f * m_neuron_firingthreshold_min->get_int() );
									if ( new_size < fmin )
										new_size = fmin;

								// std::cout << "old firingThreshold :: " << firingThreshold->get_float() << ">" << new_size << " (" << adjust_size << ")";

								firingThreshold->set( new_size );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_synapse_add_neuron_to_neuron->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								// NEURON -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  + synapse N>N: " << "\t\t\t\t";
								// BeEntity::ptr neuron(brain_container->randomChild());
								
								// get 2 random neurons
								auto random_neuron1 = randomChild( neurons );
								auto random_neuron2 = randomChild( neurons );
								while ( random_neuron1 == random_neuron2 )
								{
									random_neuron2 = neurons->children()[ m_rng->get_int() ];
								}
								// std::cout << std::setw(3) << random_neuron1->id() << " to " << random_neuron2->id() << "\t\t\t\t";
								
								// add synapse to randomly picked neuron
								auto synapse = addSynapse( random_neuron1 );

								// connect neuron to synapse
								random_neuron2->getChild("firingWeight", 1)->connectServerServer( synapse );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_synapse_add_neuron_to_output->get_uint(); // FIXME THIS NEEDS A REMOVE CONNECTION TOO, SINCE IT'S NOT REALLY A SYNAPSE
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								// NEURON -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  + synapse N>O: " << "\t\t\t\t";
								// BeEntity::ptr neuron(brain_container->randomChild());

								// get random neuron
								auto random_neuron = randomChild( neurons );
								
								// get random output FIXME this only does motors now
								auto outputs = value->getChild( "outputs", 1 );
								auto constraints = outputs->getChild( "bullet_constraints", 1 )->get_reference();
								auto random_constraint = randomChild( constraints )->get_reference();
								random_neuron->getChild("firingWeight", 1)->connectServerServer( random_constraint );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}

						modesum += m_mutationweight_synapse_add_input_to_neuron->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 1  )
							{
								// INPUT -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  + synapse I>N: " << "\t\t\t\t";
								// BeEntity::ptr neuron(brain_container->randomChild());
								
								// get random input
								auto random_input = randomChild( value->getChild( "inputs", 1 ) );
								if ( random_input )
								{
									// get random neuron
									auto random_neuron = randomChild( neurons );
									
									// add synapse to randomly picked neuron
									auto synapse = addSynapse( random_neuron );

									// connect input to synapse
									random_input->connectServerServer( synapse );

									std::cout << " ok" << std::endl;
									continue;
								}
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}

						modesum += m_mutationweight_synapse_remove_from_neuron->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 0  )
							{
								std::cout << std::setw(3) << run+1 << "  - synapse from N: " << "\t\t\t\t";

								// get 1 random neuron
								auto random_neuron = dynamic_cast< BNeuron* >( randomChild( neurons ) );
								
								// FIXME so do we need a synapse_adam_min
								// if there are more than minimum
								// if ( synapses->numChildren() > m_synapse_adam_min->get_uint() )
								if ( random_neuron->m_synapses->numChildren() > 1 )
								{
									// get 1 random synapse
									auto random_synapse = randomChild( random_neuron->m_synapses );
									
									// remove synapse
									random_neuron->m_synapses->removeChild( random_synapse );

									std::cout << " ok" << std::endl;
									continue;
								}
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}
						
						modesum += m_mutationweight_synapse_remove_from_output->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 0  )
							{
								std::cout << std::setw(3) << run+1 << "  - synapse from O: " << "\t\t\t\t";

								// try 10 times to find an output with a connection
								bool done(false);
								Buint attempts(100);
								BEntity* found(0);

								for ( unsigned int i(0); i < attempts && !done ; i++  )
								{
									// get 1 random output
									auto random_output = randomChild( value->getChild( "outputs", 1 ) );

									// std::cout << random_output->class_id() << "::" << random_output->name() << std::endl;
									if ( random_output->class_id() == std::string("reference") )
									{
										random_output = random_output->get_reference();
									}
									// std::cout << random_output->class_id() << "::" << random_output->name() << std::endl;
									
									
									if ( random_output->class_id() == std::string("entity") )
									{
										// std::cout << "entering " << random_output->name() << std::endl;
										found = randomChild( random_output );
										if ( found )
										{
											if ( found->class_id() == std::string("reference") )
											{
												found = found->get_reference();
											}
										}
										
									}

									if ( found )
									{
										if ( found->class_id() == std::string("external_child") )
										{
											found = found->get_reference();
										}
									}

									// HACK get it's connections
									if ( found && found->hasInput() )
									{
										auto input = found->getInput();

										// pick random element from vector m_connected_outputs
										if ( input->m_connected_outputs.size() > 0 )
										{
											// PICK A CONNECTED ENTITY
											m_rng->set( "min", 0 );
											m_rng->set( "max", (Bint)input->m_connected_outputs.size()-1 );

											auto connected_entity = input->m_connected_outputs[ m_rng->get_int() ];
											if ( connected_entity->hasOutput() )
											{
												// FIXME SHOULD WORK LIKE
												// input->removeConnection( connected_entity );
												auto output = connected_entity->getOutput();
												input->removeConnection( connected_entity );
												output->removeConnection( found );
												done = true;
											}
											else
											{
												std::cout << "ERROR " << connected_entity->name() << " HAS NO OUTPUT" << std::endl;
											}

											// FIXME remove neuron if no connections left
										}
									}
								}

								if ( done )
								{
									std::cout << " ok" << std::endl;
									continue;
								}
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}

						modesum += m_mutationweight_synapse_alter_weight->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 0  )
							{
								// NEURON -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  * synapse weight: " << "\t\t\t\t";

								// get 1 random neuron
								auto random_neuron = dynamic_cast< BNeuron* >( randomChild( neurons ) );

								// get 1 random synapse
								auto random_synapse_weight = randomChild( random_neuron->m_synapses )->getChild("weight", 1);

								// change synapse weight
								m_rng->set( "min", m_synapse_weight_min->get_int() );
								m_rng->set( "max", m_synapse_weight_max->get_int() );
								random_synapse_weight->set( 0.001f * m_rng->get_int() );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}


						modesum += m_mutationweight_synapse_alter_weight_slightly->get_uint();
						if ( mode <= modesum )
						{
							if ( neurons->numChildren() > 0  )
							{
								// NEURON -> NEURON(+syn)
								std::cout << std::setw(3) << run+1 << "  * synapse weight slightly: " << "\t\t";

								// get 1 random neuron
								auto random_neuron = dynamic_cast< BNeuron* >( randomChild( neurons ) );

								// get 1 random synapse
								auto random_synapse_weight = randomChild( random_neuron->m_synapses )->getChild("weight", 1);
								
								// consider our sign
								float sign( -1.0f );
								m_rng->set( "min", (Bint)0 );
								m_rng->set( "max", (Bint)1 );
								if ( m_rng->get_int() == 0 )
									sign = 1.0f;

								m_rng->set( "min", m_synapse_weight_min->get_int() );
								m_rng->set( "max", m_synapse_weight_max->get_int() );

								auto rng_value = abs( m_rng->get_int() );

								auto adjust_size = sign * (0.01f * m_slightly_percent->get_uint()) * 0.001f * rng_value;
								
								// get new size of synapse weight
									float new_size = random_synapse_weight->get_float() + adjust_size;

								// check min/max boundaries
									const float fmax( 0.001f * m_synapse_weight_max->get_int() );
									if ( new_size > fmax )
										new_size = fmax;

									const float fmin( 0.001f * m_synapse_weight_min->get_int() );
									if ( new_size < fmin )
										new_size = fmin;

								// std::cout << "old random_synapse :: " << random_synapse_weight->get_float() << ">" << new_size << " (" << adjust_size << ")";

								random_synapse_weight->set( new_size );

								std::cout << " ok" << std::endl;
								continue;
							}
							std::cout << " failed" << std::endl;
							--run;
							continue;
						}
						
					}

					// std::cout << std::endl;
				}
				
				return true;
			}
			
		}
		// std::cout << "mutate: no" << std::endl;
		return false;
	}
	
	void BBrain::construct()
	{
		addChild( "outputs", new BEntity() );
		addChild( "inputs", new BEntity() );
		m_neurons = addChild( "neurons", new BEntity() );
	}
	
	void BNeuron::construct()
	{
		m_firingWeight = addChild( "firingWeight", new BEntity_float() );
		m_firingThreshold = addChild( "firingThreshold", new BEntity_float() );
		m_firing = addChild( "firing", new BEntity_bool() );
		m_synapses = addChild( "synapses", new BEntity() );
	}

	void Synapse::construct()
	{
		m_parent_neuron = parent()->parent();
	}

	bool Synapse::set( const Bfloat& value )
	{
		if ( !m_weight )
			m_weight = getChild("weight", 1);

		// std::cout << "set " << (m_weight->get_float() * value) << std::endl;
		
		m_parent_neuron->set( m_parent_neuron->get_float() + (m_weight->get_float() * value) );
		return true;
	}
