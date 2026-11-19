ls_prog = executable(
    'ls', ['cmp.c', 'ls.c', 'main.c', 'print.c', 'util.c'],
    c_args: ['-DSMALL'],
    include_directories: [inc, cinc],
    link_with: [libcompat, libutil_static],
    install: true,
)

install_man('ls.1')
