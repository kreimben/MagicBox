project('MagicBoxWM', 'cpp', 'c', default_options: [ 'c_std=c18', 'cpp_std=c++2a' ])

wayland_dep = dependency('wayland-client')
thread_dep = dependency('threads')

executable('MagicBoxWM',
    'src/main.cpp',

    'src/MBApp.h',
    'src/MBApp.cpp',

    dependencies: [ wayland_dep, thread_dep ]
)
