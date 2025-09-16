#pragma once

#include "kernel/be_entity_core_types.h"

	//  SYSTEM
		class BrainSystem : public BEntity
		{
			public:
				BrainSystem() : m_rng(0) { setProcessing(); };
				const char* class_id() const { return "BrainSystem"; }
				virtual ~BrainSystem() {};

				void construct();
				void process();

				BEntity* getChildCustom( BEntity* parent, const char* name = "" );
				bool set( const Bstring& id, BEntity* brain );
				
			private:
				BEntity* randomChild( const BEntity* parent );
				inline BEntity* addSynapse( BEntity* neuron );
				inline BEntity* addNeuron( BEntity* neurons );

				// FOOD CONTAINER
				BEntity* m_unit_container;

				BEntity* m_mutation_chance;
				BEntity* m_mutationruns_min;
				BEntity* m_mutationruns_max;
				BEntity* m_neuron_adam_min;
				BEntity* m_neuron_adam_max;
				BEntity* m_neuron_firingthreshold_min;
				BEntity* m_neuron_firingthreshold_max;
				BEntity* m_neuron_firingweight_min;
				BEntity* m_neuron_firingweight_max;
				BEntity* m_synapse_weight_min;
				BEntity* m_synapse_weight_max;
				BEntity* m_synapse_adam_min;
				BEntity* m_synapse_adam_max;
				BEntity* m_mutationweight_neuron_add;
				BEntity* m_mutationweight_neuron_remove;
				BEntity* m_mutationweight_neuron_alter_firingweight;
				BEntity* m_mutationweight_neuron_alter_firingthreshold;
				BEntity* m_mutationweight_neuron_alter_firingweight_slightly;
				BEntity* m_mutationweight_neuron_alter_firingthreshold_slightly;
				BEntity* m_mutationweight_synapse_add_neuron_to_neuron;
				BEntity* m_mutationweight_synapse_add_neuron_to_output;
				BEntity* m_mutationweight_synapse_add_input_to_neuron;
				BEntity* m_mutationweight_synapse_remove_from_neuron;
				BEntity* m_mutationweight_synapse_remove_from_output;
				BEntity* m_mutationweight_synapse_alter_weight;
				BEntity* m_mutationweight_synapse_alter_weight_slightly;
				BEntity* m_slightly_percent;
				
				BEntity* m_rng;
		};

		class BBrain : public BEntity
		{
			public:
				BBrain() {};
				const char* class_id() const { return "Brain"; }
				virtual ~BBrain() {};
				void construct();
				BEntity* m_neurons;
		};

	//  NEURON
		class BNeuron : public BEntity_float
		{
			public:
				BNeuron() {};
				const char* class_id() const { return "Neuron"; }
				virtual ~BNeuron() {};
				void construct();
				BEntity* m_firingWeight;
				BEntity* m_firingThreshold;
				BEntity* m_firing;
				BEntity* m_synapses;
		};

		// FIXME why isn't the weight value just the m_value here?  no need for m_weight entity.
	//  SYNAPSE // FIXME TO FIGURE OUT, I removed some warnings removing property when going into tree to synapses, so warnings when going in admin window to synapses in a neuron :: WHICH MEANS RETHINK THIS OBJECT
		class Synapse : public BEntity_float
// 		class Synapse : public BEntity_float_property
		{
			public:
				Synapse() : m_weight(0) {};
				const char* class_id() const { return "Synapse"; }
				virtual ~Synapse() {};
				bool set( const Bfloat& value );
				void construct();
			private:
				BEntity* m_parent_neuron;
				BEntity* m_weight;
		};
		
