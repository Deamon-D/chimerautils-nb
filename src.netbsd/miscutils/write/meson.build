write_prog = executable(
    'write',
    [ 'write.c',
      'term_chk.c', 
      '../../coreutils/who/utmpentry.c'
    ],
    include_directories : [ inc, '../../coreutils/who' ],
    link_with : [ libcompat ],
    c_args : [ '-DSUPPORT_UTMP', '-DSUPPORT_UTMPX' ],
    install : true,
)

install_man('write.1')
