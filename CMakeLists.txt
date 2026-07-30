cmake_minimum_required(VERSION 3.21)


add_library(Polychrome SHARED
    src/main.c
    src/colors.c
)
target_include_directories(Polychrome PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Polychrome/src
)
set_target_properties(Polychrome PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/Polychrome
    PREFIX ""
    OUTPUT_NAME "Polychrome"
)
target_link_options(Polychrome PRIVATE
    -static
)

add_custom_command(
    OUTPUT ${BIN_DIR}/Polychrome/config.json
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/config.json
        ${BIN_DIR}/Polychrome/config.json
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/config.json
    COMMENT "Copying Polychrome config.json"
)
add_custom_target(Polychrome_config ALL
    DEPENDS ${BIN_DIR}/Polychrome/config.json
)
