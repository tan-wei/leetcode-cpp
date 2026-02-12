from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualBuildEnv


class Example(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    languages = "C", "C++"
    options = {
        "fPIC": [True, False],
    }
    default_options = {
        "fPIC": True,
        "libcurl/*:with_brotli": True,
        "libcurl/*:with_zstd": True,
        "libcurl/*:with_zlib": True,
        "libcurl/*:with_ssl": "openssl",
    }

    def layout(self):
        cmake_layout(self)

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.settings.os == "Windows":
            self.options["libcurl/*"].with_ssl = "schannel"

    def requirements(self):
        self.requires("nlohmann_json/3.12.0")
        self.requires("libcurl/8.18.0")
        self.requires("gtest/1.17.0")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()
        be = VirtualBuildEnv(self)
        be.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()

    def package(self):
        CMake(self).install()
