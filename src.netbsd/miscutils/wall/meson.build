wall_prog = executable(
    'wall',
    [ 'wall.c',
      'ttymsg.c',
      '../../coreutils/who/utmpentry.c',
      '../write/term_chk.c'
    ],
    include_directories : [ inc, '../write', '../../coreutils/who' ],
    c_args : [ '-DSUPPORT_UTMP', '-DSUPPORT_UTMPX' ],
    link_with : [ libcompat ],
    install : true,
)

install_man('wall.1')
