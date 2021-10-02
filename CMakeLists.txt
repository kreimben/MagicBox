cmake_minimum_required(VERSION 3.21)
project(MagicBox)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Wayland)

add_executable(MagicBox
        Wayland/header.h
        Wayland/module.modulemap
        Wayland/Package.swift
        Wayland/README.md
        Main.swift
        README.md)
