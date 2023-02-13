## android-ndk-opencv-successProject
you should download opencv-sdk at first, then put it in my code. questions email:archerswet@163.com

## 该内容中 NDK 中集成opencv的步骤操作流程：
1. 下载 3.4.X opencv sdk
2. 将include 文件放入 cpp (android 项目创建 使用c++模式创建)
3. 将libs 下 armeabi,arm64-v8a ...等等 .so文件放入一个自建的jnilib文件夹（注意千万不可以使用new Folder的方式创建jni）
4. 按照github中 CMakeList中的代码配置，并build ->compile CMakeList文件
