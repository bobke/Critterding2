#pragma once

#include "kernel/be_entity_interface.h"

	class BShaderUniformVec3 : public BEntity
	{
		public:
			BShaderUniformVec3();
			const char* class_id() const { return "ShaderUniformVec3"; }

			virtual ~BShaderUniformVec3() {};
			virtual void construct();

			virtual void setValue(const float x, const float y, const float z);

		private:
			unsigned int m_location;
			float m_x;
			float m_y;
			float m_z;
	};
