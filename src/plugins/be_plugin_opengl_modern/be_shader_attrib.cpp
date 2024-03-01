#include "be_shader_attrib.h"
#include "be_entity_graphics_model.h"

	BShaderAttrib::BShaderAttrib()
	: BEntity()
	{
	}

	void BShaderAttrib::construct()
	{
		std::cout << "creating ATTRIB with name " << name() << " location: " << m_location << " error: " << glGetError() << std::endl;
		m_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent()->parent() )->m_effect->m_program.get()->handle(), name().c_str() );
		std::cout << "created ATTRIB with name " << name() << " location: " << m_location << " error: " << glGetError() << std::endl;

		if ( m_location > -1 )
		{
			// Set up per-instance attribute pointers
			glEnableVertexAttribArray(m_location);

			glVertexAttribPointer(m_location, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
			glVertexAttribPointer(m_location + 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
			glVertexAttribPointer(m_location + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
			glVertexAttribPointer(m_location + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
			
			glVertexAttribDivisor(m_location, 1);
			// std::cout << "created ATTRIB with name " << name() << " location: " << m_location << std::endl;
		}
		// else
		// {
			// std::cout << "failed creating ATTRIB with name " << name() << " error: " << glGetError() << std::endl;
		// }
		
	}

