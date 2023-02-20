#ifndef BE_SHADER_H_INCLUDED
#define BE_SHADER_H_INCLUDED

// #include <GL/glew.h>
#include "be_graphics_kernel.h"
// #include "kernel/be_log.h"

// #include <cstdio>
#include <cassert>
#include <string>

class BeShader
{
public:
	BeShader(const GLenum shaderType);
	virtual ~BeShader();
	GLuint handle() const { return m_handle; }
	void source(const GLsizei count, const GLchar ** const strings, const GLint* const lengths);
	void source(const GLchar *string, const GLint* const length);
	void source(const GLchar *string);
	void source(const std::string& string);
	void compile();
private:
	BeGraphicsKernel	m_graphicsKernel;
	GLuint			m_handle;
// 	BeLogDebug		m_logDebug;
};

class BeVertexShader : public BeShader
{
public:
	BeVertexShader() : BeShader(GL_VERTEX_SHADER) {}
};

class BeFragmentShader : public BeShader
{
public:
	BeFragmentShader() : BeShader(GL_FRAGMENT_SHADER) {}
};

class BeProgram
{
public:
	BeProgram();
	~BeProgram();
	GLint getUniformLocation(const char* const name) const
	{
		assert(name);
		return glGetUniformLocation(m_handle, name);
	}

	template<typename T>
	void uniform(const char* const name, const T value)
	{
		uniform(getUniformLocation(name), value);
	}

	template<typename T>
	void uniform(const char* const name, const size_t count, const T* const value)
	{
		uniform(getUniformLocation(name), count, value);
	}

	void uniform(const GLint location, const GLint value)
	{
		glProgramUniform1iEXT(m_handle, location, value);
	}

	void uniform(const GLint location, const GLfloat value)
	{
		glProgramUniform1fEXT(m_handle, location, value);
	}

	void uniform(const GLint location, const size_t count, const GLfloat* const value) const
	{
		glProgramUniform1fvEXT(m_handle, location, count, value);
	}

	void attachShader(BeShader* const shader);
	void link();
	GLuint handle() const { return m_handle; }
private:
	BeGraphicsKernel	m_graphicsKernel;
	GLuint				m_handle;
// 	BeLogDebug		m_logDebug;
};

#endif
