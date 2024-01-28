#pragma once

#include "kernel/be_entity_interface.h"

	class BShaderUniformVec4 : public BEntity
	{
		public:
			BShaderUniformVec4();
			const char* class_id() const { return "ShaderUniformVec4"; }

			virtual ~BShaderUniformVec4() {};
			virtual void construct();

			virtual void setValue(const float x, const float y, const float z, const float w);

		private:
			unsigned int m_location;

			float m_x;
			float m_y;
			float m_z;
			float m_w;
	};
