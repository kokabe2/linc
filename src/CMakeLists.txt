include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external
    ${PROJECT_SOURCE_DIR}/external/bleu/v1
    )

add_library(
    linc
    request/default_request.c
    request/http_method_request.c
    request/request_base.c
    responder/default_responder.c
    responder/responder_base.c
    response/default_response.c
    response/response_base.c
    response/simple_response.c
    router/router_base.c
    phttp.c
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
    request/default_request_test.cpp
    request/http_method_request_test.cpp
    responder/default_responder_test.cpp
    response/default_response_test.cpp
    response/simple_response_test.cpp
    phttp_test.cpp
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
