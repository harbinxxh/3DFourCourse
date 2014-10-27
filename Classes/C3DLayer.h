#ifndef _C3DWORLD_H
#define _C3DWORLD_H

//=========================================================================
//Author;honghaier
//Desc:第二章《简单的图形绘制》
//红孩儿3D引擎开发课堂 QQ群：275220292
//=========================================================================
#include "cocos2d.h"
#include "C3DShape.h"
USING_NS_CC;

class C3DLayer :public Layer
{
public:
	//构造
	C3DLayer();
	//析构
	~C3DLayer();
    
public:
	//初始化
    virtual bool init();
	//绘制
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	//创建
    CREATE_FUNC(C3DLayer);
private:
    
	//设置一下观察与投影矩阵
	void	UpdateViewProjMatrix();
	//绘制3D物体
	void	Render3DWorld();
    
private:
	//三种图形的对象实例指针
	C3DShape*	m_pShape_Points;
	C3DShape*	m_pShape_Lines;
	C3DShape*	m_pShape_Triangles;
    C3DShape*   m_pShape_MultiPoints;
    C3DShape*   m_pShape_CostomTriangle;
    C3DShape*   m_pShape_puzzle;
    C3DShape*   m_pShape_Cube;
    C3DShape*   m_pShape_Sphere;
}
;
#endif