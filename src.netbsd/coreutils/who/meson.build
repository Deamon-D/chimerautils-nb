who_prog = executable(
    'who',
    ['who.c', 'utmpentry.c'],
    include_directories: [inc],
    c_args : [ '-DSUPPORT_UTMP', '-DSUPPORT_UTMPX' ],
    link_with: [libcompat],
    install: true,
)

install_man('who.1')
