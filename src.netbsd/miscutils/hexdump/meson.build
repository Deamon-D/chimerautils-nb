hexdump_prog = executable(
    'hexdump',
    [ 'conv.c', 'display.c', 'hexdump.c', 'hexsyntax.c', 'odsyntax.c', 'parse.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat ],
    install : true,
)

install_man('od.1')
install_man('hexdump.1')

install_symlink('od', pointing_to: 'hexdump', install_dir: bindir)
