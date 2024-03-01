#pragma once

#include "kernel/be_entity_interface.h"

	class BShaderAttrib : public BEntity
	{
		public:
			BShaderAttrib();
			const char* class_id() const { return "ShaderAttrib"; }
			virtual ~BShaderAttrib() {};
			virtual void construct();

		private:
			int m_location;

	};
