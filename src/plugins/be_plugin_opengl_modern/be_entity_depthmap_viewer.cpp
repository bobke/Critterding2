#include "be_entity_depthmap_viewer.h"
#include "be_entity_graphics_model_system.h"

	BDepthMapViewer::BDepthMapViewer()
	: BEntity()
	{
		setProcessing();

	}
	
	void BDepthMapViewer::construct()
	{
		m_active = addChild("active", "bool" );
		m_active->set( false );
		
		// DEPTHMAP VIEWER
			// Vertex Array Object and Vertex Buffer Object
				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);

			// Quad vertices and texture coordinates
				float vertices[] = {
					// Positions     // Texture coords
					-1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
					-1.0f, -1.0f,  0.0f,  0.0f, 0.0f,
					1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
					-1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
					1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
					1.0f,  1.0f,  0.0f,  1.0f, 1.0f
				};

			// Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			
			// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

			// Texture coordinate attribute
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);

			// Bind depth map texture
			// 	glActiveTexture(GL_TEXTURE0);
			// 	glBindTexture(GL_TEXTURE_2D, dynamic_cast<BGraphicsModelSystem*>(parent())->depthMap);
			// // Set texture wrapping options
			// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// // Set texture filtering options
			// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	
	void BDepthMapViewer::process()
	{
		if ( m_active->get_bool() )
		{
			// DEPTHMAP VIEWER
				glViewport( 0, 0, 800, 800 );
				// glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
				// glClear(GL_COLOR_BUFFER_BIT);

					glUseProgram( dynamic_cast<BGraphicsModelSystem*>(parent())->m_effect_depthmap_viewer->m_program.get()->handle() );
					
					// Bind depth map texture
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, dynamic_cast<BGraphicsModelSystem*>(parent())->depthMap);

				// Bind the depth map texture
					glUniform1i(glGetUniformLocation(dynamic_cast<BGraphicsModelSystem*>(parent())->m_effect_depthmap_viewer->m_program.get()->handle(), "depthMap"), 0); // 0 is the texture unit index

				// Draw the quad
					glBindVertexArray(VAO);
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
					
					glUseProgram( dynamic_cast<BGraphicsModelSystem*>(parent())->m_effect->m_program.get()->handle() );

				glViewport( 0, 0, 1224, 768 );
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);

		}
	}
	
