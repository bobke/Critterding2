#include "be_mesh.h"
#include <cassert>

void BeMesh::drawArrays( BeVertexArray* const vertexArray, const GLenum mode, const GLint first, const GLsizei count )
{
	DrawArrays* const drawArrays=new DrawArrays(vertexArray, mode, first, count);
	assert(drawArrays);
	m_drawArrays.push_back(drawArrays);
}

BeMesh::DrawArrays::DrawArrays( BeVertexArray* const vertexArray, const GLenum mode, const GLint first, const GLsizei count ) :
m_vertexArray(vertexArray),
	m_mode(mode),
	m_first(first),
	m_count(count)
{

}
