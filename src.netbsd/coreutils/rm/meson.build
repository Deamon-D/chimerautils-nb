rm_prog = executable(
    'rm',
    [ 'rm.c' ],
    include_directories : [ inc, cinc ],
    link_with : [ libcompat, libutil_static ],
    install : true,
)

install_man('rm.1')
