
include_directories(
        inc
        /home/zx/anaconda3/envs/ope/include/python3.7m)

aux_source_directory(src CPYTHON_OPE_CORE_SRCS)

add_library(cpython_ope_core SHARED ${CPYTHON_OPE_CORE_SRCS})

target_link_libraries(cpython_ope_core ope_core)
