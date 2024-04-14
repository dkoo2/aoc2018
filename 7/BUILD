cc_library(
    name = "dependency",
    hdrs = [
        "dependency.h",
    ],
    srcs = [
        "dependency.cc",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":dependency",
    ],
)