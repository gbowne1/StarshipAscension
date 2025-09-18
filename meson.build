project('StarshipAscension', 'cpp',
  version : '0.0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

inc = include_directories('include')

exe = executable('StarshipAscension', 'src/main.cpp', 'src/game.cpp', 'src/util.cpp',
  include_directories : inc,
  install : true)

# For debug/release, use meson configure -Dbuildtype=debug or release
