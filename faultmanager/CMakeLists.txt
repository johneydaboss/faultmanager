add_library(faultmanager STATIC
    src/faultmanager.c
    cnf/faultmanager_cnf_gen.c
)

target_include_directories(faultmanager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cnf>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stubs>
)
