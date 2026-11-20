xargs_prog = executable(
    'xargs',
    ['xargs.c', 'strnsubst.c'],
    include_directories: inc,
    link_with: [libcompat],
    install: true,
)

install_man('xargs.1')
