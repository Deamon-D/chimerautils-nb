tsort_prog = executable(
    'tsort',
    [ 'tsort.c' ],
    include_directories : [ inc, dbinc ],
    link_with : [libdbcompat],
    install : true,
)

install_man('tsort.1')
