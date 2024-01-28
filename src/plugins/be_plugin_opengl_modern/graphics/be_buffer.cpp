#include "be_buffer.h"

	void BeBuffer::data( GLsizeiptr size, const GLvoid* const d, const GLenum usage )
	{
		bind();
		m_graphicsKernel.bufferData(m_target, size, d, usage);
		unbind();
	}

	void BeBuffer::subData(const GLintptr offset, const GLsizeiptr size, const GLvoid* const data)
	{
		bind();
		m_graphicsKernel.bufferSubData(m_target, offset, size, data);
		unbind();
	}

	BeBuffer::BeBuffer( const GLenum target ) : m_handle(0), m_target(target)
	{
		m_graphicsKernel.genBuffers(1, &m_handle);
	}

	BeBuffer::~BeBuffer()
	{
		m_graphicsKernel.deleteBuffers(1, &m_handle);
	}

	void BeBuffer::bind()
	{
		m_graphicsKernel.bindBuffer(m_target, m_handle);
	}

	void BeBuffer::unbind()
	{
		m_graphicsKernel.bindBuffer(m_target, 0);
	}
