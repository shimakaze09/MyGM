IF ("${MY_USE_XSIMD}" STREQUAL "ON")
    DOWNLOAD_ZIP(
            https://cdn.jsdelivr.net/gh/shimakaze09/MyData@main/MyGM/include/_deps/xsimd.zip
            xsimd.zip
            SHA256 77EFEE86C767C2DE08D59160FF0B686155DAF558BB3FDD944A9D4E290B499BC6
    )
endif ()