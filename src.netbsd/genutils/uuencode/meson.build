uuencode_prog = executable(
    'uuencode',
    [ 'uuencode.c' ],
    include_directories : [ inc, ],
    link_with : [libcompat],
    install : true,
)

install_man('uuencode.1')
install_man('uuencode.5')
install_symlink('uudecode1', pointing_to: 'uuencode.1', install_dir: man1dir)
install_symlink('uudecode5', pointing_to: 'uuencode.5', install_dir: man5dir)
