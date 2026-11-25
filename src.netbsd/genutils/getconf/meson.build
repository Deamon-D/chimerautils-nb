getconf_prog = executable(
    'getconf',
    ['getconf.c'],
    include_directories: [inc],
    c_args : ['-D_NETBSD_SOURCE'],
    install: true,
    install_dir: bindir,
)

install_man('getconf.1')
