project('qnes', 'cpp',
    version: '1.0',
    meson_version: '>= 0.50.0',
    default_options: ['warning_level=3', 'buildtype=debugoptimized', 'cpp_std=c++17']
)

# Variables tracking sources and libraries
library_path = []
project_sources = []
project_header_files = []
# project_test_sources = []
# project_benchmark_sources = []

inc = [include_directories('include')]

# Trigger builds for project subdirectories
subdir('include')
subdir('src')
subdir('docs')

# Dependencies and libs
qnes_bin_deps = []
qnes_bin_dep_libs = []

qnes_bin = executable('qnes',
    main_source,
    include_directories: inc,
    dependencies: qnes_bin_deps,
    link_with: qnes_bin_dep_libs)

# clang-format support
clang_format = find_program('clang-format')

if clang_format.found()
    configure_file(input: '.clang-format',
        output: '.clang-format',
        copy: true)
    run_target('format',
        command: [clang_format, '-i', '-style=file', project_sources, project_header_files])
endif

# clang-tidy support
clang_tidy = find_program('run-clang-tidy')

if clang_tidy.found()
    configure_file(input: '.clang-tidy',
        output: '.clang-tidy',
        copy: true)
    run_target('tidy',
        command: [clang_tidy, '-p='+ meson.build_root()])
endif