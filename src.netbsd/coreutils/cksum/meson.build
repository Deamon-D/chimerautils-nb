cksum_prog = executable(
    'cksum',
    [
     'cksum.c',
     'crc.c',
     'md5.c',
     'sha1.c',
     'print.c',
     'sum1.c',
     'sum2.c',
     'sha256.c',
     'sha384.c',
     'sha512.c',
    ],
    dependencies : [libcrypto],
    c_args : ['-Wno-unused-but-set-variable'],
    link_with : [libcompat],
    include_directories: [inc, cinc],
    install: true,
)

install_man('cksum.1')

foreach l: [ 'sum', 'md5', 'sha1', 'sha256', 'sha384', 'sha512']
    install_symlink(l, pointing_to: 'cksum', install_dir: bindir)
    install_symlink(l + '.1', pointing_to: 'cksum.1', install_dir: man1dir)
endforeach
