GET_TARGET_NAME(CORE "${PROJECT_SOURCE_DIR}/src/core")
ADD_TARGET(
        TEST
        MODE EXE
        SOURCE
        "${PROJECT_SOURCE_DIR}/include/MyGM"
        LIB
        ${CORE}
)