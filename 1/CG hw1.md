<center><font size = 5>计算机图形学 Homework1</font></center>

<center>学号：16340242   姓名：吴宇祺</center>

1. 对计算机图形学的理解

   > 使用数学算法将二维或者三维图形转化为计算机显示器的栅格形式的科学，是数字图形处理或计算机视觉的逆过程。早期的计算机图形学研究如何在计算机中表示三维几何图形,以及如何利用计算机进行图形的生成、处理和显示的相关原理与算法，产生令人赏心悦目的真实感图像。近年来随着计算机图形学的发展，其意义也得到了扩充，主要包括建模、渲染、动画和人机交互四大部分内容。

   

2. 什么是OpenGL，OpenGL ES，Web GL，Vulkan，DirectX

   > - OpenGL广义上是一系列可以操作图形、图像的跨编程语言跨平台的编程接口，狭义上是一个由Khronos组织制定和维护的规范，它严格规定了每个函数的执行方式和输出值（不规定实现细节）。
   >
   > - OpenGL ES(OpenGL for Embedded Systems) 是针对手机、PDA和游戏主机等嵌入式设备而设计的OpenGl三维图形 API 的子集。
   > - Web GL(Web Graphics Library) 是一种3D绘图协议，这种绘图技术标准通过对OpenGL ES 2.0增加一个JavaScript绑定，能够为HTML5 Canvas提供硬件3D加速渲染，使得3D场景和模型能够在浏览器中更流畅地展示。
   > - Vulkan是一个跨平台的针对实时3D程序（如电子游戏）设计的绘图应用程序接口，提供高性能和低CPU管理负担。
   > - DirectX 是由微软创建的使用C++编写的多媒体编程接口，使用这些接口能够让Window下的应用程序运行和显示多媒体元素，包括全色图形、音视频和3D动画等等。

   

3. gl.h, glu.h, glew.h的作用

   > gl.h是OpenGL的核心库，包含最基本的3D函数；glu.h是实用工具库，对gl进行了部分封装；glew.h是扩展库，提供OpenGL的高级特性；

4. 使用GLEW和freeglut的目的

   > 在OpenGL文档中提到，"Before you can actually use OpenGL in a program, you must first initialize it. Because OpenGL is platform-independent, there is not a standard way to initialize OpenGL; each platform handles it differently. Non-C/C++ language bindings can also handle these differently.There are two phases of OpenGL initialization. The first phase is the **creation of an OpenGL context**; ... the second phase is to **load all of the necessary functions** to use OpenGL. Some non-C/C++ language bindings merge these into one."
   >
   > **freeglut**是一个openGL的工具库，封装了各个平台初始化窗口的过程，开发者只需要调用这个库中的初始化函数即可创建一个上下文；**GLEW**扩展库能够在自动定位（在运行时获取函数地址并将其保存在一个函数指针中供以后使用）用户平台所支持的全部OpenGL高级扩展函数，解决平台或者显卡与扩展函数不兼容的问题；

5. 选择一个SIGGRAPH上一个专题进行介绍，并说明该专题使用了什么CG技术。

   > **Computer** **Animation** **Festival** 每年展示来自于全世界最具创新性和优秀的电脑动画作品，得奖作品将具有奥斯卡动画短片入选认证的资格。往期内容主要分做四大块：电子剧场（Electronic Theatre），日间精选（Daytime Selects），幕后分享（Production Sessions）现场展示（Real-TimeLive）。动画是采用连续播放静止图像的方法产生物体运动的效果。计算机动画借助于编程或动画制作软件生成一系列的景物画面。研究方向包括：人体动画，关节动画，运动动画，脚本动画，具有人的意识的虚拟角色的动画系统等。另外，高度物理真实感的动态模拟，包括对各种形变、水、气、云、烟雾、燃烧、爆炸、撕裂、老化等物理现象的真实模拟，也是动画领域的主要问题。这些技术是各类动态仿真应用的核心技术，可以极大地提高虚拟现实系统的沉浸感。
