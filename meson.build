project('MagicBoxWM', 'cpp', 'c', default_options: [ 'c_std=c18', 'cpp_std=c++2a' ])

wayland_dep = dependency('wayland-client')
thread_dep = dependency('threads')

executable('MagicBoxWM',
    'src/main.cpp',

    'src/MBApp.h',
    'src/MBApp.cpp',

    'src/client/MBCompositor.h',
    'src/client/MBCOmpositor.cpp',

    'src/client/MBDisplay.h',
    'src/client/MBDisplay.cpp',

    'src/client/MBRegistry.h',
    'stc/client/MBRegistry.cpp',

    dependencies: [ wayland_dep, thread_dep ]
)
