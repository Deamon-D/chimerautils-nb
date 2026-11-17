jot_prog = executable(
    'jot',
    ['jot.c'],
    dependencies : [libm],
    include_directories: [inc],
    link_with: [libcompat],
    install: true,
    install_dir: bindir,
)

install_man('jot.1')
