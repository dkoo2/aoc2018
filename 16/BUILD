cc_library(
    name = "opcode",
    hdrs = [
        "opcode.h",
    ],
    srcs = [
        "opcode.cc",
    ],
)

cc_library(
    name = "classifier",
    hdrs = [
        "classifier.h",
    ],
    srcs = [
        "classifier.cc",
    ],
    deps = [
        ":opcode",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":classifier",
    ],
)