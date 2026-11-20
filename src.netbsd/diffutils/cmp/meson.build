cmp_prog = executable(
    'cmp',
    [ 'cmp.c', 'misc.c', 'regular.c', 'special.c', ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('cmp.1')
