SET(xsimd_define "")

IF (MY_USE_XSIMD)
LIST(APPEND xsimd_define MY_USE_XSIMD)
ENDIF()

IF(MY_USE_SSE_4_1)
  LIST(APPEND xsimd_define MY_USE_SSE_4_1)
ENDIF ()

ADD_TARGET(
        MODE HEAD
        LIB My::MyTemplate_core
        DEFINE ${xsimd_define}
        INC include
)