# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(hellovulkantriangle LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/vulkan/hellovulkantriangle")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Widgets QML)

qt_standard_project_setup()

qt_add_executable(hellovulkantriangle
    trianglerenderer.cpp trianglerenderer.h
    main.cpp
)
#add console to the target
if(WIN32)
    target_link_options(hellovulkantriangle PRIVATE "/SUBSYSTEM:CONSOLE")
endif()
set_target_properties(hellovulkantriangle PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(hellovulkantriangle PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Widgets
    Qt6::Qml
)

# Resources:
set_source_files_properties("../shared/color_frag.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_frag.spv"
)

set_source_files_properties("../shared/color_vert.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_vert.spv"
)

set(hellovulkantriangle_resource_files
    "../shared/color_frag.spv"
    "../shared/color_vert.spv"
)
qt_add_qml_module(hellovulkantriangle
    URI demo
    VERSION 1.0
    QML_FILES main.qml
)
qt_add_resources(hellovulkantriangle "hellovulkantriangle"
    PREFIX
        "/"
    FILES
        ${hellovulkantriangle_resource_files}
)

install(TARGETS hellovulkantriangle
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

include_directories(.)