SET(CORE_DEFINE "")
SET(core_c_option "")

IF (MSVC)
    LIST(APPEND CORE_C_OPTION "/fp:fast;/permissive-")
ENDIF ()

IF (MY_USE_SIMD)
    LIST(APPEND CORE_DEFINE MY_USE_SIMD)
ENDIF ()

IF (MY_USE_SSE_4_1)
    LIST(APPEND CORE_DEFINE MY_USE_SSE_4_1)
ENDIF ()

ADD_TARGET(
        MODE HEAD
        LIB My::MyTemplate_core
        DEFINE ${CORE_DEFINE}
        C_OPTION ${CORE_C_OPTION}
        INC include
)