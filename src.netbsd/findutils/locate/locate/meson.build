locate_prog = executable(
    'locate',
    ['locate.c'],
    include_directories: [inc],
    install: true,
    install_dir: get_option('bindir'),
)

install_man('locate.1')
install_man('locate.updatedb.8')

install_symlink(
    'updatedb.8', pointing_to: 'locate.updatedb.8', install_dir: man8dir
)

install_data(
    'updatedb.sh',
    rename : 'locate.updatedb',
    install_dir: get_option('libexecdir'),
    install_mode: 'rwxr-xr-x'
)
