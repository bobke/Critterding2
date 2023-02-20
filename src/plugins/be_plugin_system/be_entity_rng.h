#ifndef BE_ENTITY_RNG_H_INCLUDED
#define BE_ENTITY_RNG_H_INCLUDED

#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"

	// RANDOM NUMBER GENERATOR
		class Brng: public BEntity_int
		{
			public:
				Brng() : BEntity_int() {};
				virtual ~Brng() {};

				bool set( const Bstring& id, const Bint& value );
				Bint get_int();
			private:
				Bint m_min;
				Bint m_max;
		};

#endif
