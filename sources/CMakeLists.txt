# Sources.

add_executable(minirt_test
  WIN32
    miniRT_cam.cpp
    miniRT_cam.h
    miniRT_icosahedron.cpp
    miniRT_icosahedron.h
    miniRT_index_buffer.cpp
    miniRT_index_buffer.h
    miniRT_light.h
    miniRT_main.cpp
    miniRT_main.h
    miniRT_math.cpp
    miniRT_math.h
    miniRT_new.cpp
    miniRT_new.h
    miniRT_pixel_buffer.h
    miniRT_render.cpp
    miniRT_render.h
    miniRT_screen_buffer.h
    miniRT_teapot.cpp
    miniRT_teapot.h
    miniRT_triangle.cpp
    miniRT_triangle.h
    miniRT_vertex.h
    miniRT_vertex_buffer.cpp
    miniRT_vertex_buffer.h
    miniRT_win.cpp
    miniRT_win.h)

target_link_libraries(minirt_test
  PUBLIC
    GLEW::GLEW
    SDL2::SDL2
    SDL2::SDL2main)

