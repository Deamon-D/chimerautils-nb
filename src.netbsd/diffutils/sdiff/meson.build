sdiff_prog = executable(
    'sdiff',
    [ 'common.c', 'edit.c', 'sdiff.c' ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('sdiff.1')
