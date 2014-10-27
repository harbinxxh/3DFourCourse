#ifndef _C3DSHAPE_H
#define _C3DSHAPE_H

//=========================================================================
//Author;honghaier
//Desc:第二章《简单的图形绘制》
//红孩儿3D引擎开发课堂 QQ群：275220292
//=========================================================================
#include "cocos2d.h"
USING_NS_CC;

//顶点通道类型
enum VertexChannelType
{
	VERTEX_ATTRIB_POSITION,
	VERTEX_ATTRIB_COLOR,
	VERTEX_ATTRIB_TEX_COORD,
	VERTEX_ATTRIB_NORMAL,
	VERTEX_ATTRIB_MAX,
	// backward compatibility
	VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
};

//索引类型
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,
};

//图形绘制类型
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP
};


//图形顶点结构
struct  stShapeVertices
{
	Vec3 		Position;	//位置
	//kmVec3		Normal;	 	//法线
//	Vec3		Color;		//色彩
};


class C3DShape
{
public:
	//构造
	C3DShape();
	//析构
	~C3DShape();
public:
	//创建点
	void	CreatePoints();
	//创建线
	void	CreateLines();
	//创建三角形
	void	CreateTriangles();
    //创建多个点
    void    CreateMultiPoints();
    //costom三角形
    void    CreateCostomTriangle();
    //绘制迷宫
    void    CreatePuzzle(); //用线条绘制出一个小迷宫。
    //绘制 用六个面绘制出一个立方体,通过修改 Z 值来观察透视效果
    void    CreateCube();
    //创建球体
    void    CreateSphere();
	
public:
	//创建Shader
	void	BuildShader();
	//渲染
	void	Render();
protected:
	//释放
	void	Release();
protected:
	//图形渲染方式
	PrimitiveType		m_PrimitiveType;
	//索引格式
    IndexFormat			m_IndexFormat;
	//顶点数组
	stShapeVertices*	m_VertexArray;
	//索引数组
    GLushort*			m_IndiceArray;
	//VB
    GLuint				m_VertexBuffer;
	//IB
    GLuint				m_IndexBuffer;
	//顶点数量
	int					m_VertexCount;
	//索引数量
	int					m_IndexCount;
	//所用的Shader
	GLProgram*			m_ShaderProgram;
}
;

#endif