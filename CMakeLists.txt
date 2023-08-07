cmake_minimum_required(VERSION 3.26)
project(SplitVedio)

set(CMAKE_CXX_STANDARD 17)
set(SELFHEAD "D:/OneDrive - jxstnu.edu.cn/c++/socket/socket_include/")
include_directories(opencv2)
set(LINK_DIR "D:/BaiduNetdiskDownload/opencv-4.x/opencv-4.x/cmake-build-release/lib")
INCLUDE_DIRECTORIES("D:/OneDrive - jxstnu.edu.cn/c++/socket/socket_include")
link_directories(${LINK_DIR})
set(OpenCV_LIBS opencv_core455 opencv_imgproc455 opencv_highgui455 opencv_imgcodecs455 opencv_videoio455 opencv_objdetect455 )

add_executable(SplitVedio main.cpp
        "${SELFHEAD}Logger.cpp")
target_link_libraries(SplitVedio ${OpenCV_LIBS})
add_executable(Form form.cpp
        "${SELFHEAD}Logger.cpp"
        ../../socket/socket_include/MyFile.cpp)
target_link_libraries(Form ${OpenCV_LIBS})