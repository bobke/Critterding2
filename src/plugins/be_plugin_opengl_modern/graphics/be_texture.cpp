#include "be_texture.h"

	BeTexture2D::BeTexture2D(const GLenum internalFormat, const GLsizei width, const GLsizei height) : BeTexture(GL_TEXTURE_2D) 
	{
		GLenum format=0;
		GLenum type=0;

		switch(internalFormat)
		{
			//Integral RGB
		case 3:
		case GL_RGB:
		case GL_RGB8:
			format = GL_RGB;
			type = GL_UNSIGNED_BYTE;
			break;

			//Integral RGBA
		case 4:
		case GL_RGBA:
		case GL_RGBA8:
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;

			//Floating point RGB
		/*case GL_RGB16F:
		case GL_RGB32F:
			format = GL_RGB;
			type = GL_FLOAT;
			break;

			//Floating point RGBA
		case GL_RGBA16F:
		case GL_RGBA32F:
			format = GL_RGBA;
			type = GL_FLOAT;
			break;*/

		}
		data(0, internalFormat, width, height, 0, format, type, 0);
		parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}


BeTexture::BeTexture( const GLenum target ) : m_target(target), m_handle(0)
{
	glGenTextures(1, &m_handle);
}

BeTexture::~BeTexture()
{
	glDeleteTextures(1, &m_handle);
}

void BeTexture::bind()
{
	glBindTexture(m_target, m_handle);
}

void BeTexture::unbind()
{
	glBindTexture(m_target, 0);
}

void BeTexture::parameter( const GLenum name, const GLint param )
{
	bind();
	glTexParameteri(m_target, name, param);
	unbind();
}

void BeTexture::parameter( const GLenum name, const GLfloat param )
{
	bind();
	//m_graphicsKernel.texParameterf(m_target, name, param);
	glTexParameterf(m_target, name, param);
	unbind();
}

void BeTexture::data( const GLint level, const GLint internalformat, const GLsizei width, const GLsizei height, const GLint border, const GLenum format, const GLenum type, const GLvoid* const data )
{
	bind();
	glTexImage2D(m_target, level, internalformat, width, height, border, format, type, data);
	unbind();
}

void BeTexture::generateMipmap()
{
	bind();
	glGenerateMipmap(m_target);
	unbind();
}
 
