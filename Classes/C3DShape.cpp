#include "C3DShape.h"

//构造
C3DShape::C3DShape():m_VertexBuffer(0)
,m_IndexBuffer(0)
,m_PrimitiveType(PT_TRIANGLES)
,m_IndexFormat(INDEX16)
,m_VertexArray(0)
,m_IndiceArray(0)
,m_VertexCount(0)
,m_IndexCount(0)
,m_ShaderProgram(NULL)
{
    
}
//析构
C3DShape::~C3DShape()
{
	Release();
	CC_SAFE_DELETE(m_ShaderProgram);
}
//创建点
void	C3DShape::CreatePoints()
{
	Release();
	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	//创建数组并填充数据
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);
	m_VertexCount = 4;
	m_IndexCount  = 0;
	m_PrimitiveType = PT_POINTS;
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
	BuildShader();
}
//创建线
void	C3DShape::CreateLines()
{
	Release();
	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	//创建顶点数组
	m_VertexArray = new stShapeVertices[5];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);
	m_VertexArray[4].Position = Vec3(-1,-1,0);
	//创建索引数组
	m_IndiceArray = new GLushort[5];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
	m_IndiceArray[3] = 3;
	m_IndiceArray[4] = 4;
    
	m_VertexCount = 5;
	m_IndexCount  = 5;
	m_PrimitiveType = PT_LINE_STRIP;
    
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
	BuildShader();
}
//创建三角形
void	C3DShape::CreateTriangles()
{
	Release();
	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	//创建顶点数组
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(-1,-1,0);
	m_VertexArray[1].Position = Vec3(-1,1,0);
	m_VertexArray[2].Position = Vec3(1,1,0);
	m_VertexArray[3].Position = Vec3(1,-1,0);
    
	//创建索引数组
	m_IndiceArray = new GLushort[6];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
	m_IndiceArray[3] = 0;
	m_IndiceArray[4] = 2;
	m_IndiceArray[5] = 3;
	m_VertexCount = 4;
	m_IndexCount  = 6;
	m_PrimitiveType = PT_TRIANGLE_STRIP;
    
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
    
	BuildShader();
}

//创建自定义三角形
void    C3DShape::CreateCostomTriangle()
{
    Release();
    //创建VB与IB
    glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
    //创建顶点数组
	m_VertexArray = new stShapeVertices[4];
	m_VertexArray[0].Position = Vec3(0,1,0);
	m_VertexArray[1].Position = Vec3(-1,-1,0);
	m_VertexArray[2].Position = Vec3(1,-1,0);
//	m_VertexArray[3].Position = Vec3(-1,-1,0);
    
    //创建索引数组
	m_IndiceArray = new GLushort[3];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 1;
	m_IndiceArray[2] = 2;
//	m_IndiceArray[3] = 0;
//	m_IndiceArray[4] = 2;
//	m_IndiceArray[5] = 3;
	m_VertexCount = 3;
	m_IndexCount  = 3;
	m_PrimitiveType = PT_TRIANGLE_STRIP;
    
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
    
    BuildShader();
}

//创建多个点
void    C3DShape::CreateMultiPoints()
{
    Release();
	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	//创建数组并填充数据
	m_VertexArray = new stShapeVertices[100];
	int _count=0;
    //可以正常显示十行十列点
    float row = -1.0;
    for (int i = 1; i <= 10; ++i) {
        float col = -1.0;
        for (int j = 1; j <= 10; ++j) {
            m_VertexArray[_count++].Position = Vec3(row,col,0);
            col = col + 0.2;
        }
        row = row + 0.2;
    }
    
    //此for循环后 显示结果为 少一第列的点
//	for(float outer=-1.0f;outer<1.0f;outer+=0.2f)
//	{
//        CCLOG("outer : %f", outer);
//        for(float inner=-1.0f;inner<1.0f;inner+=0.2f)
//        {
//            m_VertexArray[_count++].Position = Vec3(outer,inner,0);
//        }
//	}
    
	m_VertexCount = 100;
	m_IndexCount  = 0;
	m_PrimitiveType = PT_POINTS;
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
	BuildShader();
}

//绘制迷宫 **********************************
void    C3DShape::CreatePuzzle()
{
    Release();
	//创建VB与IB
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
    
    //创建顶点数组并填充数据
	m_VertexArray = new stShapeVertices[100];
	int _count=0;
    //可以正常显示十行十列点
    float row = -1.0;
    for (int i = 1; i <= 10; ++i) {
        float col = -1.0;
        for (int j = 1; j <= 10; ++j) {
            m_VertexArray[_count++].Position = Vec3(row,col,0);
            col = col + 0.2;
        }
        row = row + 0.2;
    }
    
	//创建索引数组
	m_IndiceArray = new GLushort[100];
	m_IndiceArray[0] = 0;
	m_IndiceArray[1] = 9;
	m_IndiceArray[2] = 9;
	m_IndiceArray[3] = 99;
	m_IndiceArray[4] = 99;
    m_IndiceArray[5] = 90;
    m_IndiceArray[6] = 80;
    m_IndiceArray[7] = 88;
    m_IndiceArray[8] = 88;
    m_IndiceArray[9] = 48;
    m_IndiceArray[10] = 48;
    m_IndiceArray[11] = 46;
    m_IndiceArray[12] = 38;
    m_IndiceArray[13] = 36;
    m_IndiceArray[14] = 36;
    m_IndiceArray[15] = 16;
    m_IndiceArray[16] = 75;
    m_IndiceArray[17] = 77;
    m_IndiceArray[18] = 77;
    m_IndiceArray[19] = 57;
    m_IndiceArray[20] = 57;
    m_IndiceArray[21] = 55;
    m_IndiceArray[22] = 55;
    m_IndiceArray[23] = 5;
    m_IndiceArray[24] = 66;
    m_IndiceArray[25] = 64;
    m_IndiceArray[26] = 74;
    m_IndiceArray[27] = 14;
    m_IndiceArray[28] = 14;
    m_IndiceArray[29] = 11;
    m_IndiceArray[30] = 43;
    m_IndiceArray[31] = 42;
    m_IndiceArray[32] = 42;
    m_IndiceArray[33] = 12;
    m_IndiceArray[34] = 73;
    m_IndiceArray[35] = 53;
    m_IndiceArray[36] = 53;
    m_IndiceArray[37] = 51;
    m_IndiceArray[38] = 71;
    m_IndiceArray[39] = 21;
    m_IndiceArray[40] = 21;
    m_IndiceArray[41] = 20;
    m_IndiceArray[42] = 70;
    m_IndiceArray[43] = 0;
    m_IndiceArray[44] = 28;
    m_IndiceArray[45] = 18;
    m_IndiceArray[46] = 18;
    m_IndiceArray[47] = 17;
    m_IndiceArray[48] = 17;
    m_IndiceArray[49] = 27;
    m_IndiceArray[50] = 27;
    m_IndiceArray[51] = 28;
    
	m_VertexCount = 100;
	m_IndexCount  = 52;
	m_PrimitiveType = PT_LINES;
//    m_PrimitiveType = PT_LINE_STRIP;
    
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
	BuildShader();
}

//
void C3DShape::CreateCube()
{
    Release();
    //创建VB和IB
    glGenBuffers(1, &m_VertexBuffer);
    glGenBuffers(1, &m_IndexBuffer);
    
    //创建顶点数组并填充数据
	m_VertexArray = new stShapeVertices[100];
	int _count=0;
    //可以正常显示十行十列点
    float row = -1.0;
    for (int i = 1; i <= 10; ++i) {
        float col = -1.0;
        for (int j = 1; j <= 10; ++j) {
            m_VertexArray[_count++].Position = Vec3(row,col,0);
//            m_VertexArray[_count++].Color = Vec3(0.0f,1.0f,0.0f);
            col = col + 0.2;
        }
        row = row + 0.2;
    }
    
	//创建索引数组
	m_IndiceArray = new GLushort[100];
    
    m_IndiceArray[0] = 47;
    m_IndiceArray[1] = 77;
	m_IndiceArray[2] = 74;
    
    m_IndiceArray[3] = 44;
	m_IndiceArray[4] = 47;
	m_IndiceArray[5] = 74;
    
    m_IndiceArray[6] = 22;
	m_IndiceArray[7] = 74;
	m_IndiceArray[8] = 52;
    
    m_IndiceArray[9] = 22;
	m_IndiceArray[10] = 44;
	m_IndiceArray[11] = 74;
    
    m_IndiceArray[12] = 22;
    m_IndiceArray[13] = 25;
    m_IndiceArray[14] = 47;
    
    m_IndiceArray[15] = 22;
    m_IndiceArray[16] = 47;
    m_IndiceArray[17] = 44;
    
    
    m_VertexCount = 100;
    m_IndexCount = 18;
//    m_PrimitiveType = PT_TRIANGLE_STRIP;
    m_PrimitiveType = PT_TRIANGLES;
    
	//绑定数据到VB中。
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
    
	BuildShader();
}

//创建球体
void    C3DShape::CreateSphere()
{
    Render();
    //创建VB与IB
    glGenBuffers(1, &m_VertexBuffer);
    glGenBuffers(1, &m_IndexBuffer);
    
    int nRings = 20;    //y方向的环数
    int nSegments = 20; //xz平面的环数
    
    //M_PI/nRings是计算出nRings个分段的值
    float deltaRing = M_PI/nRings;
    
    //一个球体的顶点布局，从最高点到最低点的分割，是按180度来分段的。
    //而在横截面上，是按360度来分割
    float deltaSegment = 2.0f*M_PI/nSegments;
    m_VertexCount = (nRings + 1)*(nSegments + 1);       //顶点数
    m_VertexArray = new stShapeVertices[m_VertexCount]; //创建顶点数组
    stShapeVertices* pCurrVertex = m_VertexArray;
    
    //nRings*(2*nSegments） +  nRings*2;
    
    m_IndexCount = nRings*(nSegments+1)*2;
    m_IndiceArray = new GLushort[m_IndexCount];
    GLushort* pCurrIndex = m_IndiceArray;
    GLushort vIndex = 0;
    
    //经典的球体建立算法
    for (int j = 0; j < nRings + 1; j++) {
        float radius = sinf(j*deltaRing);
        float y0 = cosf(j*deltaRing);
        
        for (int i = 0; i < nSegments + 1; i++) {
            float x0 = radius * sinf(i * deltaSegment);
            float z0 = radius * cosf(i * deltaSegment);
            
            pCurrVertex->Position.x = x0;
            pCurrVertex->Position.y = y0;
            pCurrVertex->Position.z = z0;
            
            pCurrVertex++;
            if (j != nRings)//除了第一点和最后一点只有一次,其他都由点都有两次索引
            {
                *pCurrIndex = vIndex;
                pCurrIndex++;
                
                *pCurrIndex = vIndex+(GLushort)(nSegments+1);
                pCurrIndex++;
                vIndex++;
            }
        }
    }
    
    m_PrimitiveType = PT_TRIANGLE_STRIP;
    
    //绑定数据到VB中
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
                 m_VertexCount * sizeof(stShapeVertices),
                 m_VertexArray,
                 GL_STATIC_DRAW);
    
	//绑定数据到IB中。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);
    
	BuildShader();
}

//创建Shader
void	C3DShape::BuildShader()
{
	//由VSH，FSH创建Shader
	m_ShaderProgram = GLProgram::createWithFilenames("ShapeVS.vsh", "ShapePS.fsh");
	if( m_ShaderProgram )
	{
		//设置顶点格式中有位置信息
//		m_ShaderProgram->addAttribute("a_position", VERTEX_ATTRIB_POSITION);
        m_ShaderProgram->bindAttribLocation("a_position", VERTEX_ATTRIB_POSITION);
		//m_ShaderProgram->addAttribute("a_normal", VERTEX_ATTRIB_NORMAL);
		//m_ShaderProgram->addAttribute("a_color", VERTEX_ATTRIB_COLOR);
        //设置图形的颜色 u_ShapeColor
//        m_ShaderProgram->bindAttribLocation("a_color", VERTEX_ATTRIB_COLOR);
//        m_ShaderProgram->bindAttribLocation("u_ShapeColor", VERTEX_ATTRIB_COLOR);
		m_ShaderProgram->retain();
	}
}
//渲染
void	C3DShape::Render()
{
#define kShapeVertexStructSize sizeof(stShapeVertices)
    
	if( m_ShaderProgram && m_VertexCount > 0)
	{
		//开启Shader的使用
		m_ShaderProgram->use();
		//更新Cocos2d-x中为Shader预定义的变量
		m_ShaderProgram->setUniformsForBuiltins();
        
		//设置色彩
		ccColor4F s_tColor = ccc4f(0.0f,1.0f,0.0f,1.0f);    //green
//        Color4F s_tColor = Color4F(1.0f,0.0f,0.0f,1.0f);    //red
		GLuint	  uColorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "u_ShapeColor");
		m_ShaderProgram->setUniformLocationWith4fv(uColorId,(GLfloat*) &s_tColor.r, 1);
        
		//绑定VB
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
//		glEnableClientState(GL_VERTEX_ARRAY);
        glEnable(GL_ARRAY_BUFFER);
        
		//开启顶点中位置信息的使用
		glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
		//指定结构中位置信息的起始地址和占用大小
		glVertexAttribPointer(VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*) offsetof( stShapeVertices, Position));
		//开启顶点中法线信息的使用
//		glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
		//指定结构中法线信息的起始地址和占用大小
//		glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*) offsetof( stShapeVertices, Normal));
		//开启顶点中颜色信息的使用
//		glEnableVertexAttribArray(VERTEX_ATTRIB_COLOR);
		//指定结构中颜色信息的起始地址和占用大小
//		glVertexAttribPointer(VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, kShapeVertexStructSize, (GLvoid*) offsetof( stShapeVertices, Color));
        
		//根据是否有索引缓冲来进行渲染
		if(m_IndexCount > 0 && m_IndiceArray )
		{
			//绑定IB
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
//			glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
            glEnable(GL_ELEMENT_ARRAY_BUFFER);
            
			//使用IB进行绘制
			glDrawElements(m_PrimitiveType, (GLsizei)m_IndexCount, m_IndexFormat, 0);
		}
		else
		{
			//只使用VB进行绘制
			glDrawArrays(m_PrimitiveType, 0, m_VertexCount);
		}
        
		//取消绑定
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//绘制数加一
		CC_INCREMENT_GL_DRAWS(1);
	}
}
//释放VB,IB
void	C3DShape::Release()
{
	//释放VB数组
	if(m_VertexArray)
	{
		delete[] m_VertexArray;
		m_VertexArray = NULL;
	}
	//释放索引数组
	if(m_IndiceArray)
	{
		delete[] m_IndiceArray;
		m_IndiceArray = NULL;
	}
	m_VertexCount = 0;
	m_IndexCount  = 0;
	//释放VB
	if(glIsBuffer(m_VertexBuffer))
	{
		glDeleteBuffers(1, &m_VertexBuffer);
		m_VertexBuffer = 0;
	}
	//释放IB
	if(glIsBuffer(m_IndexBuffer))
	{
		glDeleteBuffers(1, &m_IndexBuffer);
		m_IndexBuffer = 0;
	}
}