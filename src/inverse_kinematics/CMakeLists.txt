cmake_minimum_required(VERSION 3.8)
project(inverse_kinematics)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_lint_common)
find_package(ament_lint_auto)

include_directories(include)

add_library(${PROJECT_NAME}
        src/robot_kinematics.cpp
        include/inverse_kinematics/robot_kinematics.h
        include/inverse_kinematics/posrot_vector.h
)

install(TARGETS ${PROJECT_NAME}
        EXPORT "export_${PROJECT_NAME}"
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
        INCLUDES DESTINATION include
)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION include/${PROJECT_NAME}
)

ament_export_include_directories(include)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_targets("export_${PROJECT_NAME}")
ament_package()