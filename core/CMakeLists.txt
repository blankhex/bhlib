set(BH_SOURCES
    src/algo.c
    src/ds.c
)

SET(BH_HEADERS
    include/bh/algo.h
    include/bh/bh.h
    include/bh/ds.h
)

add_library(bh STATIC ${BH_SOURCES} ${BH_HEADERS})
target_include_directories(bh PUBLIC include)
