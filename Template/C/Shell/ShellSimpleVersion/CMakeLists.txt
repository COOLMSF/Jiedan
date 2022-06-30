project(SimpleShell)

file(GLOB c_file ./**.c)
file(GLOB h_file ./**.h)


add_executable(${PROJECT_NAME}
${c_file}
${h_file})

find_package(readline)

target_link_libraries(${PROJECT_NAME} readline)