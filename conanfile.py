import os

from conans import ConanFile, CMake, tools


class JepluConan(ConanFile):
    name = "Jeplu"
    version = "0.0.1a"
    description = "A lightweight plugin manager framework which helps the creation and \
                   the load of dynamic libraries for cross-plataform applications."
    url = "https://github.com/caioss/jeplu"
    author = "Eric Menezes <eirc.m@protonmail.com>"

    scm = {
        "type": "git",
        "subfolder": "jeplu",
        "url": "https://github.com/caioss/jeplu.git",
        "revision": "setup-conan"}
    requires = "Qt/5.8.0@osechet/stable", "libzip/1.5.1@bincrafters/stable"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_paths", "cmake_find_package"
    options = {"shared": [True, False],
               "test": [True, False],
               "noqtloader": [True, False],
               "nodlloader": [True, False],
               "nolibfinder": [True, False]}
    default_options = {"Qt:shared": True,
                       "shared": True,
                       "test": True,
                       "noqtloader": False,
                       "nodlloader": False,
                       "nolibfinder": False}

    def requirements(self):
        if self.options.test:
            self.requires.add('gtest/1.7.0@bincrafters/stable')

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['test'] = self.options.test
        cmake.definitions['no-qt-loader'] = self.options.noqtloader
        cmake.definitions['no-dlopen-loader'] = self.options.nodlloader
        cmake.definitions['no-default-libfinder'] = self.options.nolibfinder

        self.output.info('CMake configure flags: %s\n CMake build flags: %s' %
                         (cmake.command_line, cmake.build_config))

        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.configure(source_folder='jeplu')
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def imports(self):
        if self.settings.build_type == 'Release':
            bindir = 'bin/Release'
        if self.settings.build_type == 'Debug':
            bindir = 'bin/Debug'

        self.copy("*.dll", dst=bindir, src="bin")
        self.copy("*.dylib*", dst=bindir, src="lib")
        self.copy('*.so*', dst=bindir, src='lib')
