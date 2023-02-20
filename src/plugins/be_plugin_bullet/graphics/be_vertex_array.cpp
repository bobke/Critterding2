#include "be_vertex_array.h"

BeVertexArray::BeVertexArray() : m_handle(0)
{
	m_graphicsKernel.genVertexArrays(1, &m_handle);
}

BeVertexArray::~BeVertexArray()
{
	m_graphicsKernel.deleteVertexArrays(1, &m_handle);
}

void BeVertexArray::bind()
{
	m_graphicsKernel.bindVertexArray(m_handle);
}

void BeVertexArray::unbind()
{
	m_graphicsKernel.bindVertexArray(0);
}

void BeVertexArray::vertexPointer( BeArrayBuffer& buffer, const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset )
{
	bind();
	buffer.bind();
	m_graphicsKernel.vertexPointer(size, type, stride, offset);
	buffer.unbind();
	unbind();
}

void BeVertexArray::texCoordPointer( BeArrayBuffer& buffer, const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset )
{
	bind();
	buffer.bind();
	m_graphicsKernel.texCoordPointer(size, type, stride, offset);
	buffer.unbind();
	unbind();
}

void BeVertexArray::normalPointer( BeArrayBuffer& buffer, const GLenum type, const GLsizei stride, const GLsizei offset )
{
	bind();
	buffer.bind();
	m_graphicsKernel.normalPointer(type, stride, offset);
	buffer.unbind();
	unbind();
}


void BeVertexArray::enableClientState( const GLenum array )
{
	bind();
	m_graphicsKernel.enableClientState(array);
	unbind();
}

void BeVertexArray::disableClientState( const GLenum array )
{
	bind();
	m_graphicsKernel.disableClientState(array);
	unbind();
}

void BeVertexArray::setElementArrayBuffer( BeElementArrayBuffer* const elementArrayBuffer )
{
	bind();
	if(elementArrayBuffer)
	{
		elementArrayBuffer->bind();
	}
	else
	{
		m_graphicsKernel.bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	unbind();
}
