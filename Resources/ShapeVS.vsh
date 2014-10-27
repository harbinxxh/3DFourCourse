//定义顶点流的格式,这里说明有位置属性,可以用一个vec4格式进行存储获取。
attribute vec4 a_position;
//入口函数
void main()												
{			
	//将顶点位置由3D空间变换到屏幕并返回。
    gl_Position = CC_MVPMatrix * a_position;						
}

//attribute vec4 a_position;
//attribute vec4 a_color;
//attribute vec4 v_color;
//入口函数
//void main()
//{
	//将顶点位置由3D空间变换到屏幕并返回。
//    gl_Position = a_position;
//    v_color = a_color;

//}