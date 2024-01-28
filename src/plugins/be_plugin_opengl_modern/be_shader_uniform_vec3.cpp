#include "be_shader_uniform_vec3.h"
#include "be_entity_graphics_model.h"

	BShaderUniformVec3::BShaderUniformVec3()
	: BEntity()
	, m_x(0.0f)
	, m_y(0.0f)
	, m_z(0.0f)
	{
	}

	void BShaderUniformVec3::construct()
	{
		m_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent()->parent() )->m_effect->m_program.get()->handle(), name().c_str() );
		std::cout << "created UNIFORM VEC3 with name " << name() << std::endl;
	}

	void BShaderUniformVec3::setValue(const float x, const float y, const float z )
	{
		if ( x != m_x || y != m_y || z != m_z )
		{
			m_x = x;
			m_y = y;
			m_z = z;
			glUniform3f( m_location, m_x, m_y, m_z );
			// std::cout << "updated vec3" << std::endl;
		}
		// else
		// {
		// 	// std::cout << "SKIPPED vec3" << std::endl;
		// }
	}
