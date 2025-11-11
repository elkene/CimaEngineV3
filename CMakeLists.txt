cmake_minimum_required(VERSION 3.20)

project(CimaEngine3v LANGUAGES CXX)

set(BIN "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")

add_compile_definitions(ASSETS="${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions("DEBUG=$<CONFIG:Debug>")


include(FetchContent)

# ---------------------------
# SFML (desde GitHub)
# ---------------------------
message(STATUS "Descargando SFML desde GitHub...")
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SFML)

# ---------------------------
# ImGui
# ---------------------------
message(STATUS "Descargando ImGui desde GitHub...")
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.1-docking
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(imgui)

# ---------------------------
# ImGui-SFML
# ---------------------------
message(STATUS "Descargando ImGui-SFML desde GitHub...")
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v3.0
        GIT_PROGRESS TRUE
)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_MakeAvailable(imgui-sfml)

# ---------------------------
# Incluir carpeta src (donde se crea el target CimaEngine3v)
# ---------------------------
add_subdirectory(src)

# ---------------------------
# Configurar target después de que exista
# ---------------------------
target_include_directories(CimaEngine3v PRIVATE ${SFML_SOURCE_DIR}/include)
target_include_directories(CimaEngine3v PRIVATE ${IMGUI_DIR})

target_link_libraries(
        CimaEngine3v
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
        ImGui-SFML::ImGui-SFML
)

target_compile_features(CimaEngine3v PUBLIC cxx_std_17)