#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_base_entity_types.h"
#include "kernel/be_entity_macros.h"

#include <GL/glew.h>
#include <GL/gl.h>

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
			private:
		};

		ENTITY_SIMPLEST( BglClearColorBuffer ) { glClear(GL_COLOR_BUFFER_BIT); } END
		ENTITY_SIMPLEST( BglQuads ) { glBegin(GL_QUADS); } END
		ENTITY_SIMPLEST( BglEnd ) { glEnd(); } END
	
		
// 		ENTITY(BglClearColorBuffer)
// 			PROCESS
// 				glClear(GL_COLOR_BUFFER_BIT);
// 			END
// 		END


	//	BglClearColor
			ENTITY(BglClearColor)
				DATA_4(float, R, G, B, A)
				PROCESS
					glClearColor(m_R, m_G, m_B, m_A);
				END
			END

	//	BglColor3f
			ENTITY(BglColor3f)
				DATA_3(float, R, G, B)
				PROCESS
					glColor3f(m_R, m_G, m_B);
				END
			END

	//	BglColor4f
			ENTITY(BglColor4f)
				DATA_4(float, R, G, B, A)
				PROCESS
					glColor4f(m_R, m_G, m_B, m_A);
				END
			END

	//	BglVertex2f
			ENTITY(BglVertex2f)
				DATA_2(float, X, Y)
				PROCESS
					glVertex2f(m_X, m_Y);
				END
			END

	//	BRectangle
			ENTITY(BRectangle)
				DATA_2(float, X, Y)
				PROCESS
					glVertex2f(-m_X, -m_Y);
					glVertex2f(m_X, -m_Y);
					glVertex2f(m_X, m_Y);
					glVertex2f(-m_X, m_Y);
				END
			END



// 			class BglClearColor : public BEntity
// 			{
// 				public:
// 					BglClearColor() {};
// 					virtual ~BglClearColor() {};
// 
// 					virtual void process() { glClearColor(m_v1, m_v2, m_v3, m_v4); }
// 					DATA_4(Bfloat, v1, v2, v3, v4)
// 			};

// 		class BglClearColor : public BEntity
// 		{
// 			public:
// 				BglClearColor() : m_v1(0.0f), m_v2(0.0f), m_v3(0.0f), m_v4(0.0f) {};
// 				virtual ~BglClearColor() {};
// 				virtual void process() { glClearColor(m_v1, m_v2, m_v3, m_v4); }
// 
// 				bool set( const Bstring& id, const Bfloat& value )
// 				{
// 					if ( id == "v1" )
// 					{
// 						if ( m_v1 != value )
// 						{
// 							m_v1 = value;
// 							return true;
// 						}
// 					}
// 					return false;
// 				}
// 			private:
// 				Bfloat m_v1;
// 				Bfloat m_v2;
// 				Bfloat m_v3;
// 				Bfloat m_v4;
// 		};







#endif
