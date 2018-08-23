
aux_source_directory(. SRC)

add_library(echo ${SRC} i_sock.hpp utils.hpp)
