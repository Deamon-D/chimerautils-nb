stat_prog = executable(
    'stat',
    ['stat.c'],
    include_directories: [inc, cinc],
    c_args : ['-DHAVE_NBTOOL_CONFIG_H'],
    link_with: [libcompat],
    install: true,
)

install_man('stat.1')

if not chimera_realpath.enabled()
    install_symlink('readlink', pointing_to: 'stat', install_dir: bindir)
    install_symlink('readlink.1', pointing_to: 'stat.1', install_dir: man1dir)
endif
