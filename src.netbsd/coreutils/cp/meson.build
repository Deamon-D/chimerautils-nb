cp_prog = executable(
    'cp',
    ['cp.c', 'utils.c'],
    include_directories: [inc, cinc],
    c_args : ['-DSMALL'],
    link_with: [libcompat, libutil_static],
    install: true,
)

install_man('cp.1')
