# Add hpp and cpp files to Snake variable
file(GLOB EmeraldScavenger
        "*.hpp"
        "*.h"
        "*.cpp"
        )

# Compile cpp files
add_executable(EmeraldScavenger ${EmeraldScavenger})
target_link_libraries(EmeraldScavenger ${all_libs})

# copy files to dest
file(COPY platformer-art-deluxe.json platformer-art-deluxe.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY platformer-art-deluxe.json platformer-art-deluxe.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

IF (WIN32)
    # Copy dll files to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)

    # Set working directory to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    set_target_properties(EmeraldScavenger PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)
ENDIF(WIN32)
