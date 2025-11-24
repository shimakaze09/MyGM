SET(CORE_DEFINES "")
SET(CORE_C_OPTIONS "")
SET(SOURCES "")

IF (MSVC)
    LIST(APPEND CORE_C_OPTIONS "/fp:fast" "/permissive-")
    LIST(APPEND SOURCES "${PROJECT_SOURCE_DIR}/vs/MyGM.natvis")
ELSE()
    LIST(APPEND CORE_C_OPTIONS "-Wno-gnu-anonymous-struct" "-Wno-nested-anon-types" "-Wno-missing-braces")
ENDIF ()

IF (NOT MYGM_USE_SIMD)
    LIST(APPEND CORE_DEFINES MYGM_NOT_USE_SIMD)
ELSEIF (NOT MYGM_USE_SSE_4_1)
    LIST(APPEND CORE_DEFINES MYGM_NOT_USE_SSE_4_1)
    IF (NOT MSVC)
        LIST(APPEND CORE_C_OPTIONS "-msse2")
    ENDIF()
ELSE()
    IF (NOT MSVC)
        LIST(APPEND CORE_C_OPTIONS "-msse4.1")
    ENDIF()
ENDIF ()

ADD_TARGET(
        MODE INTERFACE
        RET_TARGET_NAME targetName
        SOURCE
        ${SOURCES}
        DEFINE
        ${CORE_DEFINES}
        C_OPTION
        ${CORE_C_OPTIONS}
        INC
        "${PROJECT_SOURCE_DIR}/include"
        LIB
        My::MyTemplate_core
)