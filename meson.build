project('MagicBoxWM', 'cpp')

xcb_dep = dependency('xcb')

executable('MagicBoxWM',
    'src/main.cpp',

    'src/MBApp.h',
    'src/MBApp.cpp',

    'src/MBWindow.h',
    'src/MBWindow.cpp',

    'src/MBTopBar.h',
    'src/MBTopBar.cpp',

    dependencies: xcb_dep
)
