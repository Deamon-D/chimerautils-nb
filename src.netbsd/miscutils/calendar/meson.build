calendar_prog = executable(
    'calendar',
    [ 'calendar.c' ],
    include_directories: [inc, cinc],
    link_with: [libcompat],
    dependencies: [libm],
    c_args: ['-DWITH_ICONV'],
    install: true,
)

install_man('calendar.1')
