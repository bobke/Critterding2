#ifndef BE_FRAMEBUFFER_H_INCLUDED
#define BE_FRAMEBUFFER_H_INCLUDED

// #include <GL/glew.h>
#include "be_graphics_kernel.h"

// #include <cassert>

class BeRenderbuffer
{
public:
	BeRenderbuffer();
	BeRenderbuffer( const GLenum internalformat, const GLsizei width, const GLsizei height );
	GLuint handle() const { return m_handle; }
	void storage(const GLenum internalformat, const GLsizei width, const GLsizei height);
	void storageMultisample(const GLsizei samples, const GLenum internalformat, const GLsizei width, const GLsizei height);
	~BeRenderbuffer();
private:
	void bind();
	void unbind();
	BeGraphicsKernel	m_graphicsKernel;
	GLuint				m_handle;
};

class BeFramebuffer
{
public:
	BeFramebuffer();
	virtual ~BeFramebuffer();
	GLuint handle() const { return m_handle; }
	void bind();
	void unbind();
	void renderbuffer(const GLenum attachment, const GLuint handle);
	void texture2D(const GLenum attachment, const GLuint handle, const GLint level);
private:
	void privateBind();
	BeGraphicsKernel m_graphicsKernel;
	GLuint m_handle;
};

#endif
