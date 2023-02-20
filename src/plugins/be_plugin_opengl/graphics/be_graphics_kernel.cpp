#include "be_graphics_kernel.h"

void BeGraphicsKernel::clear( const GLbitfield mask )
{
	glClear(mask);
}

void BeGraphicsKernel::flush()
{
	glFlush();
}

void BeGraphicsKernel::enable( const GLenum cap )
{
	glEnable(cap);
}

void BeGraphicsKernel::disable( const GLenum cap )
{
	glDisable(cap);
}

void BeGraphicsKernel::drawArrays( const GLenum mode, const GLint first, const GLsizei count )
{
	glDrawArrays(mode, first, count);
}

void BeGraphicsKernel::genFramebuffers( const GLsizei n, GLuint* const ids )
{
	glGenFramebuffers(n, ids);
}

void BeGraphicsKernel::deleteFramebuffers( const GLsizei n, const GLuint* const ids )
{
	glDeleteFramebuffers(n, ids);
}

void BeGraphicsKernel::bindFramebuffer( const GLenum target, const GLuint framebuffer )
{
	glBindFramebuffer(target, framebuffer);
}

void BeGraphicsKernel::framebufferTexture2D( const GLenum target, const GLenum attachment, const GLenum textarget, const GLuint texture, const GLint level )
{
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void BeGraphicsKernel::framebufferRenderbuffer( const GLenum target, const GLenum attachment, const GLenum renderbuffertarget, const GLuint renderbuffer )
{
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

GLenum BeGraphicsKernel::checkFramebufferStatus( const GLenum target )
{
	return glCheckFramebufferStatus(target);
}

void BeGraphicsKernel::blitFramebuffer( const GLint srcX0, const GLint srcY0, const GLint srcX1, const GLint srcY1, const GLint dstX0, const GLint dstY0, const GLint dstX1, const GLint dstY1, const GLbitfield mask, const GLenum filter )
{
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void BeGraphicsKernel::genRenderbuffers( const GLsizei n, GLuint* const ids )
{
	glGenRenderbuffers(n, ids);
}

void BeGraphicsKernel::deleteRenderbuffers( const GLsizei n, const GLuint* const ids )
{
	glDeleteRenderbuffers(n, ids);
}

void BeGraphicsKernel::bindRenderbuffer( const GLenum target, const GLuint renderbuffer )
{
	glBindRenderbuffer(target, renderbuffer);
}

void BeGraphicsKernel::renderbufferStorage( const GLenum target, const GLenum internalformat, const GLsizei width, const GLsizei height )
{
	glRenderbufferStorage(target, internalformat, width, height);
}

void BeGraphicsKernel::renderbufferStorageMultisample( const GLenum target, const GLsizei samples, const GLenum internalformat, const GLsizei width, const GLsizei height )
{
	glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void BeGraphicsKernel::genTextures( const GLsizei n, GLuint* const textures )
{
	glGenTextures(n, textures);
}

void BeGraphicsKernel::deleteTextures( const GLsizei n, const GLuint* const textures )
{
	glDeleteTextures(n, textures);
}

void BeGraphicsKernel::bindTexture( const GLenum target, const GLuint texture )
{
	glBindTexture(target, texture);
}

void BeGraphicsKernel::bindMultiTexture(const GLint texunit, const GLenum target, const GLuint texture)
{
	glBindMultiTextureEXT(texunit, target, texture);
}

void BeGraphicsKernel::texParameteri( const GLenum target, const GLenum pname, const GLint param )
{
	glTexParameteri(target, pname, param);
}

void BeGraphicsKernel::texImage2D( const GLenum target, const GLint level, const GLint internalformat, const GLsizei width, const GLsizei height, const GLint border, const GLenum format, const GLenum type, const GLvoid* const data )
{
	glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
}

void BeGraphicsKernel::generateMipmap( const GLenum target )
{
	glGenerateMipmap(target);
}

void BeGraphicsKernel::genBuffers( const GLsizei n, GLuint* const buffers )
{
	glGenBuffers(n, buffers);
}

void BeGraphicsKernel::deleteBuffers( const GLsizei n, const GLuint* const buffers )
{
	glDeleteBuffers(n, buffers);
}

void BeGraphicsKernel::bindBuffer( const GLenum target, const GLuint buffer )
{
	glBindBuffer(target, buffer);
}

void BeGraphicsKernel::bufferData( const GLenum target, const GLsizeiptr size, const GLvoid* const data, const GLenum usage )
{
	glBufferData(target, size, data, usage);
}

void BeGraphicsKernel::bufferSubData( const GLenum target, const GLintptr offset, const GLsizeiptr size, const GLvoid* const data)
{
	glBufferSubData(target, offset, size, data);
}

void BeGraphicsKernel::genVertexArrays( const GLsizei n, GLuint* const arrays )
{
	glGenVertexArrays(n, arrays);
}

void BeGraphicsKernel::deleteVertexArrays( const GLsizei n, const GLuint* const arrays )
{
	glDeleteVertexArrays(n, arrays);
}

void BeGraphicsKernel::bindVertexArray( const GLuint array )
{
	glBindVertexArray(array);
}

void BeGraphicsKernel::enableClientState( const GLenum array )
{
	glEnableClientState(array);
}

void BeGraphicsKernel::disableClientState( const GLenum array )
{
	glDisableClientState(array);
}

void BeGraphicsKernel::vertexPointer( const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset )
{
	vertexPointer(size, type, stride, reinterpret_cast<GLvoid*>(offset));
}

void BeGraphicsKernel::vertexPointer( const GLint size, const GLenum type, const GLsizei stride, const GLvoid* const pointer )
{
	glVertexPointer(size, type, stride, pointer);
}

void BeGraphicsKernel::texCoordPointer( const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset )
{
	texCoordPointer(size, type, stride, reinterpret_cast<GLvoid*>(offset));
}

void BeGraphicsKernel::texCoordPointer( const GLint size, const GLenum type, const GLsizei stride, const GLvoid* const pointer )
{
	glTexCoordPointer(size, type, stride, pointer);
}

void BeGraphicsKernel::normalPointer( const GLenum type, const GLsizei stride, const GLvoid* const pointer )
{
	glNormalPointer(type, stride, pointer);
}

void BeGraphicsKernel::normalPointer( const GLenum type, const GLsizei stride, const GLsizei offset )
{
	normalPointer(type, stride, reinterpret_cast<GLvoid*>(offset));
}



GLuint BeGraphicsKernel::createProgram()
{
	return glCreateProgram();
}

void BeGraphicsKernel::deleteProgram( const GLuint program )
{
	glDeleteProgram(program);
}

GLuint BeGraphicsKernel::createShader( const GLenum shaderType )
{
	return glCreateShader(shaderType);
}

void BeGraphicsKernel::deleteShader( const GLuint shader )
{
	glDeleteShader(shader);
}

void BeGraphicsKernel::shaderSource( const GLuint shader, const GLsizei count, const GLchar ** const strings, const GLint* const lengths )
{
	glShaderSource(shader, count, strings, lengths);
}

void BeGraphicsKernel::compileShader( const GLuint shader )
{
	glCompileShader(shader);
}

void BeGraphicsKernel::getShaderInfoLog( const GLuint shader, const GLsizei bufSize, GLsizei *length, GLchar* const infoLog )
{
	glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void BeGraphicsKernel::attachShader( const GLuint program, const GLuint shader )
{
	glAttachShader(program, shader);
}

void BeGraphicsKernel::linkProgram( const GLuint program )
{
	glLinkProgram(program);
}

void BeGraphicsKernel::getProgramInfoLog( const GLuint program, const GLsizei bufSize, GLsizei *length, GLchar* const infoLog )
{
	glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void BeGraphicsKernel::useProgram( const GLuint program )
{
	glUseProgram(program);
}

void BeGraphicsKernel::hint( const GLenum target, const GLenum mode )
{
	glHint(target, mode);
}

void BeGraphicsKernel::shadeModel( const GLenum mode )
{
	glShadeModel(mode);
}

void BeGraphicsKernel::cullFace( const GLenum mode )
{
	glCullFace(mode);
}

void BeGraphicsKernel::matrixMode( const GLenum mode )
{
	glMatrixMode(mode);
}

void BeGraphicsKernel::pushMatrix()
{
	glPushMatrix();
}

void BeGraphicsKernel::popMatrix()
{
	glPopMatrix();
}

void BeGraphicsKernel::loadMatrix(const float* const m)
{
	glLoadMatrixf(m);
}

void BeGraphicsKernel::loadIdentity()
{
	glLoadIdentity();
}

void BeGraphicsKernel::frustum( const GLdouble left, const GLdouble right, const GLdouble bottom, const GLdouble top, const GLdouble zNear, const GLdouble zFar )
{
	glFrustum(left, right, bottom, top, zNear, zFar);
}

void BeGraphicsKernel::ortho( const GLdouble left, const GLdouble right, const GLdouble bottom, const GLdouble top, const GLdouble zNear, const GLdouble zFar )
{
	glOrtho(left, right, bottom, top, zNear, zFar);
}

void BeGraphicsKernel::translate( const GLfloat x, const GLfloat y, const GLfloat z )
{
	glTranslatef(x, y, z);
}

void BeGraphicsKernel::rotate( const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z )
{
	glRotatef(angle, x, y, z);
}

void BeGraphicsKernel::scale( const GLfloat x, const GLfloat y, const GLfloat z )
{
	glScalef(x, y, z);
}

void BeGraphicsKernel::multMatrix( const GLfloat* const m)
{
	glMultMatrixf(m);
}

void BeGraphicsKernel::lightModel( const GLenum pname, const GLfloat* const params )
{
	glLightModelfv(pname, params);
}

void BeGraphicsKernel::lightModel( const GLenum pname, const GLint* const params )
{
	glLightModeliv(pname, params);
}

void BeGraphicsKernel::light( const GLenum lightId, const GLenum pname, const GLfloat* const params )
{
	glLightfv(lightId, pname, params);
}

void BeGraphicsKernel::material( const GLenum face, const GLenum pname, const GLfloat* const params )
{
	glMaterialfv(face, pname, params);
// 	glMaterialf(face, pname, *params);
}
