cmake_minimum_required(VERSION 3.7)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

PROJECT(MLProjects)

###QT5.7.0
find_package(Qt5 COMPONENTS Widgets Gui Core Sql REQUIRED)

###openCV4.1.2
FIND_PACKAGE(OpenCV REQUIRED)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	#${OPENCV_INCLUDE_DIR}
	)

SET(Demo_SRCS 
	main.cpp
    mainInterface.h
    mainInterface.cpp
	)
	
SET(Demo_MOC_SRCS 
  	mainInterface.h
	)

SET(Demo_UI_SRCS
	mainInterface.ui
	)

SET(Demo_RCC_SRCS
	
	)
# SET(Demo_HEADER_SRCS

	# )
	
qt5_wrap_cpp(Demo_MOC_CXX ${Demo_MOC_SRCS})
qt5_wrap_ui(Demo_UI_CXX ${Demo_UI_SRCS})
qt5_add_resources(Demo_RCC_CXX ${Demo_RCC_SRCS})

source_group("Resources" FILES
	${Demo_UI_SRCS}
	${Demo_RCC_SRCS}
	)
source_group("Generated" FILES
	${Demo_MOC_CXX}
	${Demo_UI_CXX}
	${Demo_RCC_CXX}
	)
# source_group("INCLUDE" FILES
	# ${Demo_HEADER_SRCS}
	# )
	
# file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
# source_group("Include" FILES ${CURRENT_HEADERS}) 

add_executable(${PROJECT_NAME}
	#${WIN32_EXE_OPTIONS}    ##Win32平台下启动时去除黑窗口
	${Demo_SRCS}
	${Demo_MOC_CXX}
	${Demo_RCC_SRCS}
	${Demo_UI_CXX}
	${Demo_RCC_CXX}
	${CURRENT_HEADERS}
	)

target_link_libraries(${PROJECT_NAME}
	${OpenCV_LIBS}	
	${Qt5Core_LIBRARIES}  
	${Qt5Widgets_LIBRARIES}  
	${Qt5Gui_LIBRARIES}
	${Qt5Sql_LIBRARIES}
	)