tip_prog = executable(
    'tip',
    [
	'acu.c', 'acutab.c', 'cmds.c', 'cmdtab.c', 'cu.c', 'hunt.c',
        'partab.c', 'remote.c', 'tip.c', 'tipout.c', 'value.c', 'vars.c',
        # aculib
	'aculib/hayes.c',
        # from netbsd libc
        'getcap.c',
    ],
    include_directories: [inc],
    link_with: [libcompat],
    c_args : ['-DDEFBR=9600', '-DDEFFS=BUFSIZ', '-DHAYES', '-DSMALL',
              '-D_DIAGASSERT(x)=', '-D__type_fit(a, b)='],
    install: true,
)

install_man('tip.1')

install_symlink('cu', pointing_to: 'tip', install_dir: bindir)
install_symlink('cu.1', pointing_to: 'tip.1', install_dir: man1dir)
