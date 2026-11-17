ncal_prog = executable(
    'cal',
    'cal.c',
    include_directories: [inc, cinc],
    link_with: [libcompat],
    dependencies: [tinfo],
    install: true,
)

install_man('cal.1')
