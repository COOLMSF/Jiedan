add_executable(client 
            src/client.c
            src/client.h)

add_executable(server 
            src/server.c
            src/server.h)

set(CMAKE_BUILD_TYPE Debug)

find_package(sqlite3 REQUIRED)
target_link_libraries(server PRIVATE sqlite3)
