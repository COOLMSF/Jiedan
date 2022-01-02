cmake_minimum_required(VERSION 3.18)
project(Shell C)

set(CMAKE_C_STANDARD 99)

add_executable(Shell main.c shell.h sig_int_handler.c clear_variables.c print_history_list.c shell_prompt.c skipwhite.c skip_double_quote.c change_directory.c execute_inbuild_commands.c tokenize_redirect_input_output.c tokenize_redirect_input.c execute_command.c tokenize_by_space.c check_for_bckgrnd.c tokenize_by_pipe.c tokenize_redirect_output.c)

include_directories(/home/coolder/learning/programming/c/header)

include_directories(${PCAP_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} readline)

