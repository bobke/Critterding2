#include "be_model_system.h"
// #include "be_graphics_model_resource.h"
#include "be_texture_2d_resource.h"
#include "be_texture_store.h"
#include "filesystem/be_filesystem.h"
#include "graphics/be_shader.h"
#include "graphics/be_mesh.h"
#include "graphics/be_graphics_system.h"
#include "LinearMath/btTransform.h"


	BeGraphicsModel::BeGraphicsModel( boost::shared_ptr<BeGraphicsSystem> system, const std::string& filename ) :
		m_filename(filename),
		m_numberVertices(0),
		m_numberNormals(0),
		m_numberTexCoor(0),
		m_numberVIndices(0),
		m_arrayBuffer(0),
		m_elementArrayBuffer(0),
		m_vertexArray(0),
		m_system(system),
		m_draw_blend_is_disabled(false)
	{
	}
	
	BeGraphicsModel::~BeGraphicsModel() {}

	const std::string&	BeGraphicsModel::getFilename() const
	{
		return m_filename;
	}
	
	void BeGraphicsModel::setNumberVertices( unsigned int numberVertices ) 
	{ 
		m_numberVertices = numberVertices;
		vertices.reset(new btScalar[m_numberVertices]);
	}

	unsigned int BeGraphicsModel::getNumberVertices() const
	{
		return m_numberVertices;
	}

	void BeGraphicsModel::setNumberNormals( unsigned int numberNormals ) 
	{ 
		m_numberNormals = numberNormals;
		normals.reset(new float[m_numberNormals]);
	}

	unsigned int BeGraphicsModel::getNumberNormals() const
	{
		return m_numberNormals;
	}

	void BeGraphicsModel::setNumberTexCoor( unsigned int numberTexCoor ) 
	{ 
		m_numberTexCoor = numberTexCoor; 
		texcoor.reset(new float[m_numberTexCoor]);
	}

	unsigned int BeGraphicsModel::getNumberTexCoor() const
	{
		return m_numberTexCoor;
	}

	void BeGraphicsModel::setNumberVIndices( unsigned int numberVIndices ) 
	{ 
		m_numberVIndices = numberVIndices;
		indices.reset(new int[m_numberVIndices]);
	}
	unsigned int BeGraphicsModel::getNumberVIndices() const
	{
		return m_numberVIndices;
	}

	void BeGraphicsModel::upload(Texturestore &textureStore)
	{
		buildElementArrayBuffer();
			assert(m_arrayBuffer==0);
			m_arrayBuffer.reset(new BeArrayBuffer);
			assert(m_arrayBuffer);

			m_arrayBuffer->data((m_numberVertices*sizeof(btScalar))+((m_numberNormals+m_numberTexCoor)*sizeof(GLfloat)), NULL, GL_STATIC_DRAW_ARB);
			m_arrayBuffer->subData(0, m_numberVertices*sizeof(btScalar), vertices.get());
			m_arrayBuffer->subData(m_numberVertices*sizeof(btScalar), m_numberNormals*sizeof(GLfloat), normals.get());
			m_arrayBuffer->subData((m_numberVertices*sizeof(btScalar))+(m_numberNormals*sizeof(GLfloat)), m_numberTexCoor*sizeof(GLfloat), texcoor.get());

			assert(m_elementArrayBuffer==0);
			m_elementArrayBuffer.reset(new BeElementArrayBuffer);
			assert(m_elementArrayBuffer);
			m_elementArrayBuffer->data(elementArrayBuffer.size()*sizeof(GLint), &elementArrayBuffer[0], GL_STATIC_DRAW);

			m_vertexArray.reset(new BeVertexArray);
			m_vertexArray->setElementArrayBuffer(m_elementArrayBuffer.get());
			m_vertexArray->vertexPointer( *m_arrayBuffer, 3, GL_FLOAT, 0, 0 );
			m_vertexArray->normalPointer( *m_arrayBuffer, GL_FLOAT, 0, m_numberVertices*sizeof(btScalar) );
			m_vertexArray->texCoordPointer( *m_arrayBuffer, 2, GL_FLOAT, 0, ( (m_numberVertices*sizeof(btScalar)) + (m_numberNormals*sizeof(GLfloat)) ) );
			m_vertexArray->enableClientState(GL_VERTEX_ARRAY);
			m_vertexArray->enableClientState(GL_NORMAL_ARRAY);
			m_vertexArray->enableClientState(GL_TEXTURE_COORD_ARRAY);

			// upload textures
			for ( matit = matlist.begin(); matit != matlist.end(); ++matit )
			{
				if ( matit->second.m_imagePath.size() )
				{
					matlist[ matit->first ].m_imageTexture2D = textureStore.load(matit->second.m_imagePath);
				}
				if ( matit->second.m_imagePathBump.size() )
				{
					matlist[ matit->first ].m_imageTexture2DBump = textureStore.load(matit->second.m_imagePathBump);
				}
			}
	}

	void BeGraphicsModel::buildElementArrayBuffer()
	{
		matlist_iterator it=matlist.begin();
		for ( unsigned int i=0; i < matlist.size(); ++i)
		{
			std::pair<const std::string, Material> pair=*it;
			unsigned int first=elementArrayBuffer.size();
			unsigned int count=0;
			for ( unsigned int j=0; j < facematerials.size(); j++ )
			{
				const Facematerial& facematerial = facematerials[j];
				if(facematerial.material==pair.first)
				{
					for( unsigned int k=0; k < facematerial.faceindex_number; ++k)
					{
						elementArrayBuffer.push_back(indices[facematerial.faceindex_first+k]);
						++count;
					}
				}
			}
			DrawCall drawCall;
			drawCall.m_first=first;
			drawCall.m_count=count;
			m_drawCalls.push_back(drawCall);
			++it;
		}
	}

// 	void BeGraphicsModel::draw( const btTransform& transform )
// 	{
// 		btScalar m[16];
// 		transform.getOpenGLMatrix(m);
// 
// 		glPushMatrix();
// 			glMultMatrixf(m);
// 			draw();
// 		glPopMatrix();
// 	}

	void BeGraphicsModel::draw()
	{
		
// 		std::cout << "BeGraphicsModel::draw():: " << std::endl;
		glBindVertexArray(m_vertexArray.get() ? m_vertexArray.get()->handle() : 0);

		// // MAKES COLOR
		// glEnable(GL_COLOR);
		// glColor4f(0.5f, 0.5f, 1.0f, 1.0f);

		if ( matlist.size() > 0 )
		{
			glEnable(GL_TEXTURE_2D);
			
			BeGraphicsMaterial* material;
			matlist_iterator it = matlist.begin();
			
			size_t minPriority=0;
			size_t maxPriority=0;

			while( it != matlist.end() )
			{
				size_t priority = 0;
				material = m_system->getEffect( (*it).first );
				if ( material )
				{
					priority = material->getPriority();
				}
				if( priority < minPriority )
					minPriority = priority;
				if( priority > maxPriority )
					maxPriority = priority;

				++it;
			}

			for( size_t priority = minPriority; priority <= maxPriority; ++priority )
			{
				size_t i = 0;
				it = matlist.begin();
				while( it != matlist.end() )
				{
// 					std::cout << "mat " << i << std::endl;
					
					size_t pr = 0;
					// bool sort = false; 
					int depthMask=1;
					int depthTest=1;
					int blend = 0;
					material = m_system->getEffect( (*it).first );
					if ( material )
					{
						// sort = material->getSort();
						pr = (int)material->getPriority();
						depthMask = material->getDepthMask();
						depthTest = material->getDepthTest();
						blend = material->getBlend();
					}

					if( pr == priority )
					{
						// // DEPTH AND BLEND, COMMENTED OUT FOR CRITTERDING PERFORMANCE
// 						// DEPTH
// 							glDepthMask( depthMask );
// 							if ( depthTest )
// 							{
// // 								std::cout << "dt+";
// 								glEnable(GL_DEPTH_TEST);
// 							}
// 							else
// 							{
// // 								std::cout << "dt-";
// 								glDisable(GL_DEPTH_TEST);
// 							}
// 						
// 						// BLEND
// 							if ( blend )
// 							{
// 								if ( !m_draw_blend_is_disabled )
// 								{
// // 									std::cout << "bl+";
// 									glEnable(GL_BLEND);
// 									glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
// 									m_draw_blend_is_disabled = false;
// 								}
// 							}
// 							else
// 							{
// 								if ( m_draw_blend_is_disabled )
// 								{
// // 									std::cout << "bl-";
// 									glDisable(GL_BLEND);
// 									glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
// 									m_draw_blend_is_disabled = true;
// 								}
// 							}
							

						const Material& material = (*it).second;

						if ( material.m_imageTexture2D )
						{
							if ( material.m_imageTexture2D->get().get() )
								glBindTexture(GL_TEXTURE_2D, material.m_imageTexture2D->get().get()->handle());
						}
						else
						{
							glBindTexture(GL_TEXTURE_2D, 0);
						}

						// SPECIFIC MATERIALS, COMMENTED OUT FOR CRITTERDING PERFORMANCE
						{
							const auto& ambient = material.m_material.getAmbient();
							const float f_a[4] = { ambient.x(), ambient.y(), ambient.z(), 1 };
							glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, f_a );
						}
						// {
						// 	const auto& diffuse = material.m_material.getDiffuse();
						// 	const float f_d[4] = { diffuse.x(), diffuse.y(), diffuse.z(), 1 };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, f_d );
						// }
						// {
						// 	const auto& specular = material.m_material.getSpecular();
						// 	const float f_s[4] = { specular.x(), specular.y(), specular.z(), 1 };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, f_s );
						// }
						// {
						// 	const auto& emission = material.m_material.getEmission();
						// 	const float f_s[4] = { emission.x(), emission.y(), emission.z(), 1 };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, f_s );
						// }
						// {
						// 	const auto& shininess = material.m_material.getShininess();
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &shininess );
						// }

						const DrawCall& drawCall = m_drawCalls[i];
						glDrawElements( GL_TRIANGLES, drawCall.m_count, GL_UNSIGNED_INT, (char *)NULL + ((drawCall.m_first)*sizeof(GLint)) );
					}

					++it;
					++i;
				}

			}
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
	// 		m_graphicsSystem.bindTexture2D(0);
			//m_graphicsSystem.applyMaterial(GL_FRONT_AND_BACK, 0);
			glDrawElements(GL_TRIANGLES, elementArrayBuffer.size(), GL_UNSIGNED_INT, NULL);
		}

		glBindVertexArray(0);
	}	


	unsigned int BeGraphicsModel::numberOfMaterials()
	{
		return matlist.size();
	}

	BeGraphicsEffect::BeGraphicsEffect(BeFilesystem& fileSystem) : m_fileSystem(fileSystem)
	{
		m_program = boost::shared_ptr<BeProgram>(new BeProgram);
	}

	BeGraphicsEffect::BeGraphicsEffect(BeFilesystem& fileSystem, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : m_fileSystem(fileSystem)
	{
		m_program = boost::shared_ptr<BeProgram>(new BeProgram);
		loadCompileAndAttachVertexShader(vertexShaderPath);
		loadCompileAndAttachFragmentShader(fragmentShaderPath);
		link();
	}

	BeGraphicsEffect::~BeGraphicsEffect()
	{
	}

	void BeGraphicsEffect::loadCompileAndAttachVertexShader(const std::string& path)
	{
		BeFile vertexShaderFile;
		if ( m_fileSystem.load( vertexShaderFile, path) )
		{
			// std::cout << "BeGraphicsEffect::loadCompileAndAttachVertexShader (" << path << ")" << std::endl;
			BeVertexShader vertexShader;
			std::string string;
			vertexShaderFile.getFile(string);
			vertexShader.source(string);
			vertexShader.compile();
			m_program->attachShader(&vertexShader);
		}
	}

	void BeGraphicsEffect::loadCompileAndAttachFragmentShader(const std::string& path)
	{
		BeFile fragmentShaderFile;
		if ( m_fileSystem.load( fragmentShaderFile, path) )
		{
			BeFragmentShader fragmentShader;
			std::string string;
			fragmentShaderFile.getFile(string);
			fragmentShader.source(string);
			fragmentShader.compile();
			m_program->attachShader(&fragmentShader);
		}
	}

	void BeGraphicsEffect::link()
	{
		m_program->link();
	}
