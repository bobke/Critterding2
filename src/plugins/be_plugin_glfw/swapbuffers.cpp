#include "swapbuffers.h"
#include <GLFW/glfw3.h>
#include "plugin.h"

	GLSwapBuffers::GLSwapBuffers()
	: BEntity()
	, m_glwindow(0)
	{
		setProcessing();
	}

	void GLSwapBuffers::process()
	{
		if ( m_glwindow )
		{
			glfwSwapBuffers( m_glwindow->m_window );
		}
	}

	bool GLSwapBuffers::set( const Bstring& id, BEntity* value )
	{
		if ( id == "set_glwindow" )
		{
			m_glwindow = dynamic_cast<BGLWindow*>( value );
			return true;
		}
		return false;
	}
 
