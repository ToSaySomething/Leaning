SET(PROJ_NAME logex_test)

# gtest tuple
# Summary of tuple support for Microsoft Visual Studio:
# Compiler    version(MS)  version(cmake)  Support
# ----------  -----------  --------------  -----------------------------
# <= VS 2010  <= 10        <= 1600         Use Google Tests's own tuple.
# VS 2012     11           1700            std::tr1::tuple + _VARIADIC_MAX=10
# VS 2013     12           1800            std::tr1::tuple
if (MSVC AND MSVC_VERSION EQUAL 1700)
    add_definitions(/D _VARIADIC_MAX=10)
endif()

include_directories(${PROJECT_SOURCE_DIR}/vendor/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJ_NAME})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../vendor)

if (MSVC)
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/${PLATFORMTARGET}/$(PlatformToolset)_xp")
else()
    link_directories("${PROJECT_SOURCE_DIR}/vendor/lib/${CW_SYSTEM_NAME}/${CW_SYSTEM_PROCESSOR}")
endif()

set(CPP_TEST_SOURCES
    ../logex/logex_test.cpp
)

add_executable(${PROJ_NAME} ${CPP_TEST_SOURCES})

target_link_libraries(${PROJ_NAME} logex gtest gtest_main)
