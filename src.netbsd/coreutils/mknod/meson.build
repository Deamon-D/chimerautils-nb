mknod_prog = executable(
    'mknod',
    [ 'mknod.c', 'pack_dev.c' ],
    include_directories: [inc],
    link_with : [libcompat],
    install : true,
    install_dir : sbindir,
)

install_man('mknod.8')
