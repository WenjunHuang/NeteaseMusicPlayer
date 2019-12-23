
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE})
set(CMAKE_MODULE_PATH ${QT_CMAKE})
add_compile_definitions(QT_NO_FOREACH)
find_package(Qt5 REQUIRED Core Network Quick QuickControls2)
find_package(QtAV REQUIRED)

function(create_test_targets)
    set(prefix ARG)
    set(multiValues SOURCES ADDITIONAL_FILES LIBRARIES)

    include(CMakeParseArguments)
    cmake_parse_arguments(${prefix} "" "" "${multiValues}" ${ARGN})

    message("${${prefix}_ADDITIONAL_FILES}")
    set(TARGETS "")
    foreach (SRC_FILE IN LISTS ${prefix}_SOURCES)
        get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)
        string(REGEX MATCHALL "([A-Za-z0-9_]+)-?.*" MATCHES "${FILE_NAME}")
        if (MATCHES)
            set(TARGET_NAME ${CMAKE_MATCH_1})
            list(FIND TARGETS ${TARGET_NAME} IDX)
            if (IDX EQUAL "-1")
                list(APPEND TARGETS ${TARGET_NAME})
                set(${TARGET_NAME}_files ${SRC_FILE})
            else ()
                list(APPEND ${TARGET_NAME}_files ${SRC_FILE})
            endif ()
        endif ()
    endforeach ()


    foreach (TARGET IN LISTS TARGETS)
        add_executable(${TARGET} main.cc ${${TARGET}_files} ${${prefix}_ADDITIONAL_FILES})
        target_link_libraries(${TARGET} PRIVATE ${${prefix}_LIBRARIES})
        if (WIN32)
            if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
                target_link_options(${TARGET} PRIVATE "/DEBUG:FASTLINK")
            endif ()
        endif ()
    endforeach ()

endfunction()

file(GLOB_RECURSE TEST_SRCS test_*.cc)
create_test_targets(SOURCES ${TEST_SRCS} ADDITIONAL_FILES ${CMAKE_SOURCE_DIR}/resources.qrc LIBRARIES application)

#file(GLOB_RECURSE UI_SRCS ui_*.cc)
#create_test_targets(SOURCES ${UI_SRCS}
#        ADDITIONAL_FILES ${CMAKE_SOURCE_DIR}/resources.qrc
#        LIBRARIES application)