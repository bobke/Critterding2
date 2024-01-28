#pragma once

#include "kernel/be_entity_interface.h"

	class BShaderUniformI1 : public BEntity
	{
		public:
			BShaderUniformI1();
			const char* class_id() const { return "ShaderUniformI1"; }

			virtual ~BShaderUniformI1() {};
			virtual void construct();

			virtual bool set( const Bint& value );

		private:
			unsigned int m_location;
			int m_current;
	};
 
