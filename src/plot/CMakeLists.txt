cmake_minimum_required(VERSION 3.10)
project(plot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

set(project_headers
	MainWindow.h
	lib/qcustomplot.h
	lib/axistag.h)

set(project_sources
	Application.cpp
	MainWindow.cpp
	lib/qcustomplot.cpp
	lib/axistag.cpp)

qt5_wrap_ui(project_wrapped mainwindow.ui)
qt5_wrap_cpp(project_moc ${project_headers})

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
	${project_wrapped}
	${project_moc})

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
	Qt5::PrintSupport)