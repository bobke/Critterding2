#include "plugin.h"
#include "brain_system.h"
#include <iostream>

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, BRAIN_SYSTEM
		, BRAIN
		, NEURON
		, SYNAPSE
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::BRAIN_SYSTEM, "BrainSystem" );
					i.addClass( parent, CLASS::BRAIN, "Brain" );
					i.addClass( parent, CLASS::NEURON, "Neuron" );
					i.addClass( parent, CLASS::SYNAPSE, "Synapse" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);

				if ( type == CLASS::BRAIN_SYSTEM )
					i = new BrainSystem();
				else if ( type == CLASS::BRAIN )
					i = new BBrain();
				else if ( type == CLASS::NEURON )
					i = new BNeuron();
				else if ( type == CLASS::SYNAPSE )
					i = new Synapse();

				return i;
			}
	}

	extern "C" void destroy( BEntity* p )
	{
		delete p;
	}
	
