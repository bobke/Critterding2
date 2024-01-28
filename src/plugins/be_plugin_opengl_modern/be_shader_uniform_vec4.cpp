#include "be_shader_uniform_vec4.h"
#include "be_entity_graphics_model.h"

	BShaderUniformVec4::BShaderUniformVec4()
	: BEntity()
	, m_x(0.0f)
	, m_y(0.0f)
	, m_z(0.0f)
	, m_w(0.0f)
	{
	}

	void BShaderUniformVec4::construct()
	{
		m_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent()->parent() )->m_effect->m_program.get()->handle(), name().c_str() );
		std::cout << "created UNIFORM VEC4 with name " << name() << std::endl;
	}

	void BShaderUniformVec4::setValue(const float x, const float y, const float z, const float w)
	{
		if ( x != m_x || y != m_y || z != m_z || w != m_w )
		{
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
			glUniform4f( m_location, m_x, m_y, m_z, m_w );
			// std::cout << "updated vec4" << std::endl;
		}
		// else
		// {
		// 	// std::cout << "SKIPPED vec4" << std::endl;
		// }
	}
