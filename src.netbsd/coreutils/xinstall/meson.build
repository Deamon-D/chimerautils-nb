xinstall_prog = executable(
    'xinstall',
    ['xinstall.c', 'getid.c'],
    include_directories: [inc, cinc],
    c_args : ['-DHAVE_NBTOOL_CONFIG_H', '-Wno-format-truncation'],
    link_with: [libcompat],
    dependencies: [libcrypto],
)

meson.add_install_script(install_as, bindir, xinstall_prog, 'install', 'xinstall')

install_man('install.1')
install_symlink('xinstall.1', pointing_to: 'install.1', install_dir: man1dir)
