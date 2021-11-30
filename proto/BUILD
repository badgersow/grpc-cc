load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "proto_library",
    srcs = ["message.proto"]
)

cc_proto_library(
    name = "cc_proto_library",
    deps = [":proto_library"]
)

cc_grpc_library(
    name = "proto",
    srcs = [":proto_library"],
    deps = [":cc_proto_library"],
    grpc_only = True,
    visibility = ["//visibility:public"]
)