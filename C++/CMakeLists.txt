cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

INCLUDE_DIRECTORIES("include" ${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE(Threads)
IF (NOT Threads_FOUND)
    MESSAGE(FATAL_ERROR "Package Threads not found.")
ENDIF(NOT Threads_FOUND)

FIND_PACKAGE(OpenCV)
IF (NOT OpenCV_FOUND)
    MESSAGE(FATAL_ERROR "Package OpenCV not found.")
ENDIF(NOT OpenCV_FOUND)



file(GLOB CAP_CROP_SRC "cap_crop_src/*.cpp")

ADD_EXECUTABLE(Cap_crop_demo ${CAP_CROP_SRC})
TARGET_LINK_LIBRARIES(Cap_crop_demo ${OpenCV_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})



file(GLOB IMENCODE_DECODE_SRC "imencode_decode_src/*.cpp")

ADD_EXECUTABLE(Imenc_dec_test ${IMENCODE_DECODE_SRC})
TARGET_LINK_LIBRARIES(Imenc_dec_test ${OpenCV_LIBRARIES})