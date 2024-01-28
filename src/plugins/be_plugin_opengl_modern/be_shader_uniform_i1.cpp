#include "be_shader_uniform_i1.h"
#include "be_entity_graphics_model.h"

	BShaderUniformI1::BShaderUniformI1()
	: BEntity()
	, m_current(-1)
	{
	}

	void BShaderUniformI1::construct()
	{
		m_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent()->parent() )->m_effect->m_program.get()->handle(), name().c_str() );
		std::cout << "created UNIFORM I1 with name " << name() << std::endl;
	}

	bool BShaderUniformI1::set( const Bint& value )
	{
		if ( m_current != value )
		{
			m_current = value;
			glUniform1i( m_location, m_current );
			// std::cout << "updated vec4" << std::endl;
			return true;
		}
		// std::cout << "SKIPPED i1" << std::endl;
		return false;
	}
