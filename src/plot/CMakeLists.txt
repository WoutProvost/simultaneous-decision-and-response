# Find the Qt5 package with required components
find_package(Qt5 REQUIRED COMPONENTS Widgets PrintSupport)

# Automatically parse .ui files and generate .h files from them
set(CMAKE_AUTOUIC ON)

# Add these libraries to be built
add_library(main_window SHARED MainWindow.h MainWindow.cpp)
add_library(qcustomplot SHARED lib/qcustomplot.h lib/qcustomplot.cpp)
add_library(axistag SHARED lib/axistag.h lib/axistag.cpp)

# Define the dependencies of these libraries
target_link_libraries(qcustomplot
	Qt5::Widgets
	Qt5::PrintSupport)
target_link_libraries(axistag
	qcustomplot)
target_link_libraries(main_window
	axistag)

# Add these executables to be built
add_executable(coldecplot Application.h Application.cpp)

# Define the dependencies of these executables
target_link_libraries(coldecplot
	main_window)