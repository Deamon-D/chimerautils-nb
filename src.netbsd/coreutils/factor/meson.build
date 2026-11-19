factor_prog = executable(
    'factor',
    [ 'factor.c',
      'pr_tbl.c',
    ],
    include_directories: inc,
    dependencies : [libcrypto],
    c_args : ['-DHAVE_OPENSSL', '-Wno-deprecated-declarations'],
    install : true,
)

install_man('factor.6')
