# PakReader
add_executable(PakReader PakReader.c)
target_link_libraries(PakReader BHLib)

add_executable(Utf8Test Utf8Test.c)
target_link_libraries(Utf8Test BHLib)