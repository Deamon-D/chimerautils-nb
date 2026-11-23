dc_prog = executable(
    'dc',
    ['main.c', 'dc.c', 'bcode.c', 'inout.c', 'mem.c', 'stack.c'],
    include_directories : inc,
    c_args : ['-Wno-calloc-transposed-args'],
    dependencies: [libcrypto],
    link_with : [libcompat],
    install : true,
)

install_man('dc.1')
