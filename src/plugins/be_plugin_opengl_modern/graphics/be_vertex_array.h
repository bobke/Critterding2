#ifndef BE_VERTEX_ARRAY_H_INCLUDED
#define BE_VERTEX_ARRAY_H_INCLUDED

// #include <GL/glew.h>
// #include "be_graphics_kernel.h"
#include "be_buffer.h"

	class BeVertexArray
	{
	public:
		GLuint handle() const { return m_handle; }
		BeVertexArray();
		virtual ~BeVertexArray();

		void bind();
		void unbind();

		void setElementArrayBuffer(BeElementArrayBuffer* const elementArrayBuffer);

		void vertexPointer(BeArrayBuffer& buffer, const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset);
		void texCoordPointer(BeArrayBuffer& buffer, const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset);
		void normalPointer(BeArrayBuffer& buffer, const GLenum type, const GLsizei stride, const GLsizei offset);

		void enableClientState(const GLenum array);
		void disableClientState(const GLenum array);
	private:
		BeGraphicsKernel m_graphicsKernel;
		GLuint m_handle;
	};

#endif
