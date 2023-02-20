#include "be_shader.h"
// #include "kernel/be_profiler.h"

BeShader::BeShader( const GLenum shaderType ) : m_handle(0)
{
	m_handle=m_graphicsKernel.createShader(shaderType);
}

BeShader::~BeShader()
{
	m_graphicsKernel.deleteShader(m_handle);
}

void BeShader::source( const GLsizei count, const GLchar ** const strings, const GLint* const lengths )
{
	m_graphicsKernel.shaderSource(m_handle, count, strings, lengths);
}

void BeShader::source( const GLchar *string, const GLint* const length )
{
	m_graphicsKernel.shaderSource(m_handle, 1, &string, length);
}

void BeShader::source( const GLchar *string )
{
	m_graphicsKernel.shaderSource(m_handle, 1, &string, 0);
}

void BeShader::source( const std::string& string )
{
	const GLchar* p=string.c_str();
	m_graphicsKernel.shaderSource(m_handle, 1, &p, 0);
}

void BeShader::compile()
{
// 	BE_FUNCTION_PROFILER;
	m_graphicsKernel.compileShader(m_handle);
	char infoLog[4096]={0};
	int length=0;
	m_graphicsKernel.getShaderInfoLog(m_handle, 4096, &length, infoLog);
	if(length==0)
	{
	}
	else
	{
// 		m_logDebug << "::GRAPHICS " <<  infoLog;
		printf("%s\nEE", infoLog);
		exit(1);
	}
}

BeProgram::BeProgram() : m_handle(0)
{
	m_handle=m_graphicsKernel.createProgram();
}

BeProgram::~BeProgram()
{
	m_graphicsKernel.deleteProgram(m_handle);
}

void BeProgram::attachShader( BeShader* const shader )
{
	assert(shader);
	if(shader)
	{
		m_graphicsKernel.attachShader(m_handle, shader->handle());
	}
}

void BeProgram::link()
{
	m_graphicsKernel.linkProgram(m_handle);
	char infoLog[4096]={0};
	int length=0;
	m_graphicsKernel.getProgramInfoLog(m_handle, 4096, &length, infoLog);
	if(length==0)
	{
	}
	else
	{
// 		m_logDebug << "::GRAPHICS " <<  infoLog;
		printf("%s\n", infoLog);
		exit(1);
	}
}
