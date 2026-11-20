users_prog = executable(
    'users',
    [ 'users.c', '../../coreutils/who/utmpentry.c'],
    include_directories : [inc, '../who'],
    c_args : [ '-DSUPPORT_UTMP', '-DSUPPORT_UTMPX' ],
    install : true,
)

install_man('users.1')
