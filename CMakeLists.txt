cmake_minimum_required(VERSION 3.12)
project(wordle CXX)

include_directories(src)

# Enable userver libraries that are needed in this project
set(USERVER_FEATURE_POSTGRESQL ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 20)

# Compatibility mode: some systems don't support these features
set(USERVER_FEATURE_CRYPTOPP_BLAKE2 OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_GRPC_CHANNELZ OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_REDIS_HI_MALLOC ON CACHE BOOL "" FORCE)


# Adding userver dependency
add_subdirectory(third_party/userver)
userver_setup_environment()

# Common sources
add_library(${PROJECT_NAME}_objs
        src/constants_storage.h
        src/model/game.h
        src/model/game.cpp

        src/model/dictionary.h
        src/infrastructure/dictionary/in-memory/naive_dictionary.h
        src/infrastructure/dictionary/in-memory/naive_dictionary.cpp
        src/infrastructure/dictionary/dictionary_component.h
        src/infrastructure/dictionary/dictionary_component.cpp

        src/app/application.h
        src/app/application.cpp
        src/app/use-cases/scenarios.h
        src/app/use-cases/check-word/word_checker.h
        src/app/use-cases/check-word/word_checker.cpp
        src/app/use-cases/start-game/game_starter.h
        src/app/use-cases/start-game/game_starter.cpp

        src/app/players/player.h
        src/app/players/players.h
        src/infrastructure/players/players_component.h
        src/infrastructure/players/players_component.cpp
        src/infrastructure/players/in-memory/memory_mapped_player.h
        src/infrastructure/players/in-memory/memory_mapped_player.cpp
        src/infrastructure/players/in-memory/memory_mapped_players.h
        src/infrastructure/players/in-memory/memory_mapped_players.cpp
        src/app/players/game-session/game_session.h

        src/app/players/game-session/game_session.cpp

        src/handlers/auth/start_game_handler.hpp
        src/handlers/auth/start_game_handler.cpp
        src/handlers/api/check_handler.hpp
        src/handlers/api/check_handler.cpp)

target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-postgresql)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
        "tests/unit_tests/eng_game_test.cpp"
        )
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)


## Benchmarks
#add_executable(${PROJECT_NAME}_benchmark
#    src/hello_benchmark.cpp
#)
#target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver-ubench)
#add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


# Functional Tests
include(UserverTestsuite)

userver_testsuite_add_simple()


# Install
include(GNUInstallDirs)

if (DEFINED ENV{PREFIX})
    message(STATUS "Set install prefix: $ENV{PREFIX}")
    file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
    set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif ()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
