cmake_minimum_required(VERSION 4.0)

project(DSharp LANGUAGES CXX)

include(GNUInstallDirs)

add_executable(dsharp 
    main.cpp 
    tokenizer.h
    parser.h
    interpreter.h
)

install(TARGETS dsharp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)