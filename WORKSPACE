workspace(name = "re2c")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_skylib",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
    ],
    sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

_RULES_FOREIGN_CC_VER = "0.5.1"
_RULES_FOREIGN_CC_SHA = {
    # 0.5.1 is needed for MacOS
    "0.5.1": "33a5690733c5cc2ede39cb62ebf89e751f2448e27f20c8b2fbbc7d136b166804",
    "0.6.0": "69023642d5781c68911beda769f91fcbc8ca48711db935a75da7f6536b65047f",
    "0.7.0": "1df78c7d7eed2dc21b8b325a2853c31933a81e7b780f9a59a5d078be9008b13a",
    "0.7.1": "bcd0c5f46a49b85b384906daae41d277b3dc0ff27c7c752cc51e43048a58ec83",
    "0.8.0": "6041f1374ff32ba711564374ad8e007aef77f71561a7ce784123b9b4b88614fc",
    "0.9.0": "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
}
http_archive(
    name = "rules_foreign_cc",
    sha256 = _RULES_FOREIGN_CC_SHA.get(_RULES_FOREIGN_CC_VER, ""),
    strip_prefix = "rules_foreign_cc-" + _RULES_FOREIGN_CC_VER,
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/{}.tar.gz".format(
        _RULES_FOREIGN_CC_VER),
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()
