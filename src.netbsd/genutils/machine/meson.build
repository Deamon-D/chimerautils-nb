install_data(['machine.sh'],
    rename: ['machine'],
    install_dir: get_option('bindir'),
    install_mode: 'rwxr-xr-x'
)

install_man('machine.1')
install_symlink('arch', pointing_to: 'machine', install_dir: bindir)
