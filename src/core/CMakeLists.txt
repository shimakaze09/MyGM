SET(core_define "")
SET(core_c_option "")

IF (MSVC)
    LIST(APPEND core_c_option "/fp:fast;/permissive-")
ENDIF ()

IF (MY_USE_SIMD)
    LIST(APPEND core_define MY_USE_SIMD)
ENDIF ()

IF (MY_USE_SSE_4_1)
    LIST(APPEND core_define MY_USE_SSE_4_1)
ENDIF ()

ADD_TARGET(
        MODE HEAD
        LIB My::MyTemplate_core
        DEFINE ${core_define}
        C_OPTION ${core_c_option}
        INC include
)