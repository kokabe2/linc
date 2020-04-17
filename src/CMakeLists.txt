include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    ${PROJECT_SOURCE_DIR}/external
    ${PROJECT_SOURCE_DIR}/external/bleu/v1
    )

add_library(
    linc
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/gcc/heap.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/heap_usage.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list_node.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/string/path.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/string/str.c
    )

add_executable(
    gtests
    main.cpp
    )

add_dependencies(gtests googletest)

target_link_libraries(
    gtests
    googletest
    linc
    pthread
    )

include(CTest)

add_test(linc_test ${PROJECT_BINARY_DIR}/gtests)
