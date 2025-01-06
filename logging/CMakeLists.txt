project(bb-logger)

find_package(fmt REQUIRED)
find_package(automotive-dlt REQUIRED)

add_library(${PROJECT_NAME}
    src/logger_adapter_dlt.cpp
    src/logger_context.cpp
    src/logger_instance.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
    PRIVATE
        src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt::fmt
        Genivi::dlt
)

add_library(${PROJECT_NAME}_testing
    src/logger_adapter_console.cpp
    src/logger_context.cpp
    src/logger_instance.cpp
)

target_include_directories(${PROJECT_NAME}_testing
    PUBLIC
        include
    PRIVATE
        src
)

target_link_libraries(${PROJECT_NAME}_testing
    PRIVATE
        fmt::fmt
)