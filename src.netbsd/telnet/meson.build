extra_cargs = [
    # PAM is only relevant for telnetd and we don't have that
    '-DUSE_TERMIO', '-DKLUDGELINEMODE', '-DENV_HACK', '-DNOPAM',
    '-Wno-pointer-sign', '-Wno-cast-function-type'
]

if libcrypto.found()
    extra_cargs += [
        '-DENCRYPTION', '-DAUTHENTICATION', '-DSRA',
        # TODO
        #'-DIPSEC_POLICY_IPSEC=IPSEC_POLICY_IPSEC',
    ]
    # TODO: get rid of low level DES API usage
    if cc.has_argument('-Wdeprecated-declarations')
        extra_cargs += ['-Wno-deprecated-declarations']
    endif
endif

telnet_prog = executable(
    'telnet',
    [
        'telnet/commands.c', 'telnet/main.c', 'telnet/network.c',
        'telnet/ring.c', 'telnet/sys_bsd.c', 'telnet/telnet.c',
        'telnet/terminal.c', 'telnet/utilities.c', 'telnet/authenc.c',
        # libtelnet
        'libtelnet/genget.c', 'libtelnet/misc.c', 'libtelnet/encrypt.c',
        'libtelnet/auth.c', 'libtelnet/enc_des.c', 'libtelnet/sra.c',
        'libtelnet/pk.c',
    ],
    include_directories: [
        inc, cinc,
        include_directories('libtelnet'), include_directories('.')
    ],
    dependencies: [tinfo, libcrypto],
    link_with: [libcompat],
    c_args: extra_cargs,
    install: true,
)

install_man('telnet/telnet.1')

