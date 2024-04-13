cc_library(
    name = "types",
    hdrs = ["types.h"],
)

cc_library(
    name = "sleep_study",
    hdrs = ["sleep_study.h"],
    srcs = ["sleep_study.cc"],
    deps = [
        ":types",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":sleep_study",
    ],
)