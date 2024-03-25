#pragma once

#include "kernel/be_entity_interface.h"

	class BImGuiPen : public BEntity
	{
		public:
			BImGuiPen();
			virtual ~BImGuiPen() {};
			const char* class_id() const { return "ImGuiPen"; }
			
			void construct();
			bool set( const Bstring& id, const Buint& value );
			Buint m_r;
			Buint m_g;
			Buint m_b;
		private:
	};

	class BImGuiGraph: public BEntity
	{
		public:
			BImGuiGraph();
			virtual ~BImGuiGraph() {};
			const char* class_id() const { return "ImGuiGraph"; }
			void process();
			void construct();
			Bbool onAddChild( BEntity* entity );
			bool set( const char* value );
			bool set( const Bstring& id, const char* value );
			bool set( const Bstring& id, const Buint& value );
			void addValue( float value );
			// bool set();
				virtual bool set( const Bfloat& value );
				virtual bool set( const Buint& value );
		private:
			unsigned int m_width;
			unsigned int m_height;

			std::vector<float> m_list;
			unsigned int m_count;
			BEntity* m_size_max;
			inline void resizeList();
			
			std::string m_title;
			
			BImGuiPen* m_pen;
	};

// CURVE_FLOAT_POLL
	class BImGuiGraph_Float_Poll : public BImGuiGraph
	{
		public:
			BImGuiGraph_Float_Poll();
			const char* class_id() const { return "ImGuiGraph_Float_Poll"; }
			virtual ~BImGuiGraph_Float_Poll() {};
			
			void process();
			bool set( const Bstring& id, BEntity* value );

	protected:
			BEntity* m_entity_to_poll;
	};

	
