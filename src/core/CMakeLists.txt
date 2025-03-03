IF (MY_USE_XSIMD)
    SET(xsimd_define MY_USE_XSIMD)
ELSE ()
    SET(xsimd_define "")
ENDIF ()

ADD_TARGET(
        MODE HEAD
        LIB My::MyTemplate_core
        DEFINE ${xsimd_define}
        INC include
)