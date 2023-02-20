#ifndef BE_BUFFER_H_INCLUDED
#define BE_BUFFER_H_INCLUDED

// #include <GL/glew.h>

#include "be_graphics_kernel.h"

class BeBuffer
{
	friend class BeGraphicsSystem;
	friend class BeVertexArray;
public:
	GLuint handle() const { return m_handle; }
	void data(GLsizeiptr size, const GLvoid* const d, const GLenum usage);
	void subData(const GLintptr offset, const GLsizeiptr size, const GLvoid* const data);
protected:
	BeBuffer(const GLenum target);
	virtual ~BeBuffer();
private:
	void bind();
	void unbind();
	BeGraphicsKernel m_graphicsKernel;
	GLuint m_handle;
	const GLenum m_target;
};

class BeArrayBuffer : public BeBuffer
{
public:
	BeArrayBuffer() : BeBuffer(GL_ARRAY_BUFFER) {}
	virtual ~BeArrayBuffer() {}
};

class BeElementArrayBuffer : public BeBuffer
{
public:
	BeElementArrayBuffer() : BeBuffer(GL_ELEMENT_ARRAY_BUFFER) {}
	virtual ~BeElementArrayBuffer() {}
};

#endif
