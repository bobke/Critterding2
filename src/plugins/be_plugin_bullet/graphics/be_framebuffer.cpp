#include "be_framebuffer.h"

BeRenderbuffer::BeRenderbuffer() : m_handle(0)
{
	m_graphicsKernel.genRenderbuffers(1, &m_handle);
}

BeRenderbuffer::BeRenderbuffer( const GLenum internalformat, const GLsizei width, const GLsizei height ) : m_handle(0)
{
	m_graphicsKernel.genRenderbuffers(1, &m_handle);
	storage(internalformat, width, height);
}

void BeRenderbuffer::storage( const GLenum internalformat, const GLsizei width, const GLsizei height )
{
	bind();
	m_graphicsKernel.renderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
	unbind();
}

void BeRenderbuffer::storageMultisample( const GLsizei samples, const GLenum internalformat, const GLsizei width, const GLsizei height )
{
	bind();
	m_graphicsKernel.renderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
	unbind();
}

BeRenderbuffer::~BeRenderbuffer()
{
	m_graphicsKernel.deleteRenderbuffers(1, &m_handle);
}

void BeRenderbuffer::bind()
{
	m_graphicsKernel.bindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void BeRenderbuffer::unbind()
{
	m_graphicsKernel.bindRenderbuffer(GL_RENDERBUFFER, 0);
}

BeFramebuffer::BeFramebuffer() : m_handle(0)
{
	m_graphicsKernel.genFramebuffers(1, &m_handle);
}

BeFramebuffer::~BeFramebuffer()
{
	m_graphicsKernel.deleteFramebuffers(1, &m_handle);
}

void BeFramebuffer::bind()
{
	m_graphicsKernel.bindFramebuffer(GL_FRAMEBUFFER, m_handle);
	const GLenum status = m_graphicsKernel.checkFramebufferStatus(GL_FRAMEBUFFER);
	switch(status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		break;
	default:
		assert(0);
	}
}

void BeFramebuffer::unbind()
{
	m_graphicsKernel.bindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

void BeFramebuffer::renderbuffer( const GLenum attachment, const GLuint handle )
{
	privateBind();
	m_graphicsKernel.framebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, handle);
	unbind();
}

void BeFramebuffer::texture2D( const GLenum attachment, const GLuint handle, const GLint level )
{
	privateBind();
	m_graphicsKernel.framebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, handle, level);
	unbind();
}

void BeFramebuffer::privateBind()
{
	m_graphicsKernel.bindFramebuffer(GL_FRAMEBUFFER, m_handle);
}
