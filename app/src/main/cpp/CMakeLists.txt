# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1) #最低支持cmake版本

# Declares and names the project.
#TODO 第一步导入头文件
include_directories("inc")
#批量导入所有源文件
file(GLOB allCPP *.c *.h *.cpp)

project("voicechange")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        voicechange #libvoicechange-lib.so

        # Sets the library as a shared library.
        SHARED #动态库
        #STATIC静态库

        # Provides a relative path to your source file(s).
        ${allCPP} #导入所有
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#TODO 第二步导入库文件

#CMAKE_CXX_FLAGS == win的path:"环境变量"
#CMAKE_CXX_FLAGS == CMakeLists.txt所在的路径
#CMAKE_ANDROID_ARCH_ABI == 获取当前CPU架构

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

#find_library( # Sets the name of the path variable.
#        log-lib
#
#        # Specifies the name of the NDK library that
#        # you want CMake to locate.
#        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        voicechange

        # Links the target library to the log library
        # included in the NDK.
        #TODO 第三步链接具体的库 到我们libvoicechange-lib.so总库
        log
        #具体的库连接到libvoicechange-lib.so总库里面
        fmod
        fmodL
        )