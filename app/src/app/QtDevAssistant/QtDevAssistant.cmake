
set(QtDevAssistantDir ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB_RECURSE QtDevAssistant_SRC
    ${QtDevAssistantDir}/*.h
    ${QtDevAssistantDir}/*.hpp

    ${QtDevAssistantDir}/*.c
    ${QtDevAssistantDir}/*.cc
    ${QtDevAssistantDir}/*.cpp
    )

FILE(GLOB_RECURSE QtDevAssistant_FORMs 
    ${QtDevAssistantDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtDevAssistant_RES
    ${QtDevAssistantDir}/Res/*.qrc
    ${QtDevAssistantDir}/Res/*.qml
    ${QtDevAssistantDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtDevAssistantDir}
        PREFIX "QtDevAssistant"
        FILES ${QtDevAssistant_SRC} ${QtDevAssistant_FORMs} ${QtDevAssistant_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtDevAssistant_RES_UIC ${QtDevAssistant_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtDevAssistant_SRC
set(QtDevAssistant_SRC ${QtDevAssistant_SRC} ${QtDevAssistant_FORMs} ${QtDevAssistant_RES} ${QtDevAssistant_RES_UIC})