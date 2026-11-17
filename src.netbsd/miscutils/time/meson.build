time_prog = executable(
    'time',
    ['time.c', 'xtime.c'],
    include_directories: inc,
    link_with : [libcompat],
    c_args : ['-DNOT_CSH'],
    install: true,
)

install_man('time.1')
