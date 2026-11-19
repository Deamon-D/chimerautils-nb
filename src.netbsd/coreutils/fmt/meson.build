fmt_prog = executable(
    'fmt',
    [ 'fmt.c', 'head.c' ],
    include_directories : inc,
    c_args : ['-DFMT_PROG'],
    install : true,
)

install_man('fmt.1')
