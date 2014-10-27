#include "C3DLayer.h"

//构造
C3DLayer::C3DLayer()
{
	m_pShape_Points = NULL ;
	m_pShape_Lines  = NULL ;
	m_pShape_Triangles = NULL ;
    m_pShape_MultiPoints = NULL;
    m_pShape_CostomTriangle = NULL;
    m_pShape_puzzle = NULL;
    m_pShape_Cube = NULL;
    m_pShape_Sphere = NULL;
}
//析构
C3DLayer::~C3DLayer()
{
	CC_SAFE_DELETE(m_pShape_Points);
	CC_SAFE_DELETE(m_pShape_Lines);
	CC_SAFE_DELETE(m_pShape_Triangles);
    CC_SAFE_DELETE(m_pShape_MultiPoints);
    CC_SAFE_DELETE(m_pShape_CostomTriangle);
    CC_SAFE_DELETE(m_pShape_puzzle);
    CC_SAFE_DELETE(m_pShape_Cube);
    CC_SAFE_DELETE(m_pShape_Sphere);
}

//初始化
bool C3DLayer::init()
{
//	m_pShape_Points = new C3DShape();
//	m_pShape_Points->CreatePoints();
    
//    m_pShape_Lines = new C3DShape();
//    m_pShape_Lines->CreateLines();
    
//    m_pShape_Triangles = new C3DShape();
//    m_pShape_Triangles->CreateTriangles();
    
//    m_pShape_MultiPoints = new C3DShape();
//    m_pShape_MultiPoints->CreateMultiPoints();
    
//    m_pShape_CostomTriangle = new C3DShape();
//    m_pShape_CostomTriangle->CreateCostomTriangle();
    
//    m_pShape_puzzle = new C3DShape();
//    m_pShape_puzzle->CreatePuzzle();
    
//    m_pShape_Cube = new C3DShape();
//    m_pShape_Cube->CreateCube();
    
    m_pShape_Sphere = new C3DShape();
    m_pShape_Sphere->CreateSphere();
    
	return true;
}
//绘制
void C3DLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	//开启深度测试
//	CCDirector::sharedDirector()->setDepthTest(true);
    Director::getInstance()->setDepthTest(true);
    
	//投影和观察矩阵压栈
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPushMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPushMatrix();
	//设置一下观察与投影矩阵
	UpdateViewProjMatrix();
    
	//绘制3D物体
	Render3DWorld();
    
	//投影和观察矩阵出栈
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPopMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPopMatrix();
    
	//关闭深度测试
//	CCDirector::sharedDirector()->setDepthTest(false);
    Director::getInstance()->setDepthTest(false);
}

//设置一下观察与投影矩阵
void	C3DLayer::UpdateViewProjMatrix()
{
	//观察矩阵的设置
	Vec3 tEyeResult = Vec3(0,0,-2);
	Vec3 tLookAtResult = Vec3(0,0,0);
	Vec3 tUpResult = Vec3(0,1,0);
	Mat4 tViewMatrix;
	kmMat4LookAt(&tViewMatrix, &tEyeResult, &tLookAtResult, &tUpResult);
    
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLLoadIdentity();
	kmGLMultMatrix(&tViewMatrix);
    
	//投影矩阵的设置
	Mat4 matrixPerspective;
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLLoadIdentity();
	CCSize size =  CCDirector::sharedDirector()->getVisibleSize();
	kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 500.0f);
	kmGLMultMatrix(&matrixPerspective);
	
}
//绘制3D物体
void	C3DLayer::Render3DWorld()
{
	//渲染
	if(m_pShape_Points)
	{
		m_pShape_Points->Render();
	}
    
    if (m_pShape_Lines) {
        m_pShape_Lines->Render();
    }
    
    if (m_pShape_Triangles) {
        m_pShape_Triangles->Render();
    }
    
    if (m_pShape_MultiPoints) {
        m_pShape_MultiPoints->Render();
    }
    
    if (m_pShape_CostomTriangle) {
        m_pShape_CostomTriangle->Render();
    }
    
    if (m_pShape_puzzle) {
        m_pShape_puzzle->Render();
    }
    
    if (m_pShape_Cube) {
        m_pShape_Cube->Render();
    }
    
    if (m_pShape_Sphere) {
        m_pShape_Sphere->Render();
    }
}







