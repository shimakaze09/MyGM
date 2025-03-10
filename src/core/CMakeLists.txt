SET(CORE_DEFINES "")
SET(CORE_C_OPTIONS "")
SET(SOURCES "")

IF (MSVC)
    LIST(APPEND CORE_C_OPTION "/fp:fast;/permissive-")
    LIST(APPEND SOURCES "${PROJECT_SOURCE_DIR}/vs/MyGM.natvis")
ENDIF ()

IF (MY_USE_SIMD)
    LIST(APPEND CORE_DEFINES MY_USE_SIMD)
    IF (MY_USE_SSE_4_1)
        LIST(APPEND CORE_DEFINE MY_USE_SSE_4_1)
    ENDIF ()
ENDIF ()

ADD_TARGET(
        MODE INTERFACE
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