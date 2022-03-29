# CMakeList.txt: myffmpeglib 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("myffmpeglib")

include_directories(ffmpeg/include /libfaac/include)


add_executable (myffmpeglib "myffmpeglib.c" "myffmpeglib.h" "hi_voice_api.h")

#link_libraries(myffmpeglib C:/ffmpeg/lib/avcodec-59.dll.lib C:/ffmpeg/lib/avutil-57.dll)
target_link_libraries(myffmpeglib ffmpeg/lib/avcodec.lib ffmpeg/lib/avutil.lib libfaac/lib/libfaac.lib)

