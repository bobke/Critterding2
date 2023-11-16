#ifndef BE_ENTITY_IO_HANDLER_H_INCLUDED
#define BE_ENTITY_IO_HANDLER_H_INCLUDED

#include <vector>
#include <iostream> // NOTE: KEEPING THIS ONE HERES SAVES 3 SECONDS COMPILE TIME

class BEntity;
class BEInput;
class BEOutput;

	// CONNECTION

		class BEOutputConnectionBase
		{
			public:
// 				BEOutputConnectionBase() {};
				BEOutputConnectionBase( BEntity* const output_entity, BEntity* const input_entity )
				 : m_input_entity(input_entity)
				 , m_output_entity(output_entity)
				 {};
				virtual ~BEOutputConnectionBase(){};
				
// 				virtual BEntity* getConnectedToEntity() { return 0; }
				virtual bool commit() { return false; }
				virtual BEntity* getOutputEntity() const { return m_output_entity; }
				virtual BEntity* getInputEntity() const { return m_input_entity; }
				BEntity* m_input_entity;
				BEntity* m_output_entity;
		};

		class BEOutputConnectionLocal : public BEOutputConnectionBase
		{
			public:
				BEOutputConnectionLocal( BEntity* const output_entity, BEntity* const input_entity );
				virtual ~BEOutputConnectionLocal(){};

// 				virtual BEntity* getConnectedToEntity();
				virtual bool commit();
		};

		class BEOutputConnectionCommandBuffer : public BEOutputConnectionBase
		{
			public:
				BEOutputConnectionCommandBuffer( BEntity* const output_entity, BEntity* const input_entity )
				 : BEOutputConnectionBase( output_entity, input_entity) {};

				virtual ~BEOutputConnectionCommandBuffer(){};

// 				virtual BEntity* getConnectedToEntity();
				virtual bool commit();
		};		
// -------------------------------------------------------------------------------------------------------------------------------------------------------------

	// IO BASE CLASS
		class BeIOBase
		{
			public:
				BeIOBase(BEntity* const owning_entity) : m_owner(owning_entity) {};
				virtual ~BeIOBase() {};

				BEntity* getOwner() const { return m_owner; }
			protected:
				BEntity* m_owner;
		};

		// FIXME NO NEED TO BE BEIOBASE BECAUSE IT DOESN'T COMMIT?
	// INPUT
		class BEInput : public BeIOBase
		{
			public:
				BEInput(BEntity* const owning_entity) : BeIOBase(owning_entity) {};
				virtual ~BEInput() {};

				void removeConnection( BEntity* e );

				std::vector<BEntity*> m_connected_outputs;
		};

	// OUTPUT
		class BEOutput : public BeIOBase
		{
			public:
				BEOutput(BEntity* const owning_entity) : BeIOBase(owning_entity) {};
				virtual ~BEOutput();

				void addConnection( BEOutputConnectionBase* connection );
				void removeConnection( BEntity* e );
				std::vector<BEOutputConnectionBase*> m_connections;
// 				void commit();
				virtual bool commit();
		};

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

	// IO HANDLER

		class B_IO_Handler
		{
			public:
				B_IO_Handler();
				virtual ~B_IO_Handler();

			// PROCESSING
				public:
					bool hasInput() const;
					bool hasOutput() const;
					void setInput( BEInput* input );
					void setOutput( BEOutput* output );
					BEInput* getInput() const { return m_input; }
					BEOutput* getOutput() const { return m_output; }
					void process();

					void connectServerServer( BEntity* entity_with_output, BEntity* entity_with_input, const bool force_local=false );
// 					void disconnectServerServer( BEntity* entity_with_output, BEntity* entity_with_input );

				BEInput* m_input;
				BEOutput* m_output;
		};

#endif
