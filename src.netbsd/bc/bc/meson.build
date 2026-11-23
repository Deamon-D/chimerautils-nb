bc_srcs = [ 'global.c', 'load.c', 'util.c', 'execute.c', 'main.c', 'number.c', 'storage.c',
	  yacc.process('bc.y'), lex.process('scan.l'), 'warranty.c' ]

bc_prog = executable(
    'bc',
    bc_srcs,
    include_directories : inc,
    c_args : ['-funsigned-char', '-Wno-array-bounds'],
    dependencies: [libedit, tinfo],
    install : true,
)

install_man('bc.1')
