project('StarshipAscension', 'cpp',
  version : '0.0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

inc = include_directories('include')

glog_dep = dependency('glog', required: true)

exe = executable('StarshipAscension', 'src/main.cpp', 'src/game.cpp', 'src/util.cpp', 'src/ship.cpp',
  include_directories : inc,
  dependencies: [glog_dep],
  install : true)

# For debug/release, use meson configure -Dbuildtype=debug or release
