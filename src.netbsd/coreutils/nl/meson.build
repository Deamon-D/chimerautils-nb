nl_prog = executable(
    'nl',
    ['nl.c'],
    include_directories: inc,
    c_args : ['-Wno-format-nonliteral', '-Wno-missing-field-initializers'],
    link_with: [libcompat],
    install: true,
)

install_man('nl.1')
