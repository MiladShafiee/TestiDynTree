cmake_minimum_required(VERSION 3.5)

project(debug_RPY_iDyn)

find_package(YARP 3.1 REQUIRED)
find_package(ICUBcontrib REQUIRED)
find_package(iDynTree REQUIRED)

# extend the current search path used by cmake to load helpers
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

include(ICUBcontribHelpers)
include(ICUBcontribOptions)

# specify to install in $ICUBcontrib_DIR/bin
icubcontrib_set_default_prefix()

add_executable(${PROJECT_NAME} main.cpp Module.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${YARP_LIBRARIES} ${iDynTree_LIBRARIES})

# Use M_PI in Windows Visual Studio
if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# generate ad-hoc project to perform "make uninstall"
icubcontrib_add_uninstall_target()


file(GLOB scripts ${CMAKE_SOURCE_DIR}/app/scripts/*.xml)
file(GLOB urdf ${CMAKE_CURRENT_SOURCE_DIR}/app/robots/iCubGazeboV2_5/model.urdf)

yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_INSTALL_DIR})
yarp_install(FILES ${urdf} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/iCubGazeboV2_5)

