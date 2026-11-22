
curdir = meson.current_source_dir()
bldir = meson.current_build_dir()

mkbuiltins_gen = custom_target('builtins',
    output : [ 'builtins.h', 'builtins.c' ],
    command : [
        curdir / 'mkbuiltins',
        curdir / 'shell.h',
        curdir / 'builtins.def',
        bldir,
    ],
)

mknodes_gen = custom_target('nodes',
    output : [ 'nodes.h', 'nodes.c' ],
    command : [
        curdir / 'mknodes.sh',
        curdir / 'nodetypes',
        curdir / 'nodes.c.pat',
        bldir,
    ],
)

mknodenames_gen = custom_target('nodenames',
    input : mknodes_gen[0],
    output : 'nodenames.h',
    command : [
        curdir / 'mknodenames.sh',
        bldir / 'nodes.h',
    ],
    capture : true,
)

mktokens_gen = custom_target('tokens',
    output : 'token.h',
    command : [
        './mktokens',
        bldir,
    ],
)

sh_sources = files(
    'alias.c',
    'arith_token.c',
    'arithmetic.c',
    'cd.c',
    'error.c',
    'eval.c',
    'exec.c',
    'expand.c',
    'histedit.c',
    'input.c',
    'jobs.c',
    'mail.c',
    'main.c',
    'memalloc.c',
    'miscbltin.c',
    'mystring.c',
    'options.c',
    'parser.c',
    'redir.c',
    'show.c',
    'trap.c',
    'output.c',
    'var.c',
    'syntax.c',
)

sh_bltins = files(
    'bltin/echo.c',
    '../miscutils/kill/kill.c',
    '../coreutils/test/test.c',
    '../coreutils/printf/printf.c'
)

sh_init_gen = custom_target('init',
    input : sh_sources + sh_bltins,
    output : 'init.c',
    command : [
        curdir / 'mkinit.sh',
        '-o', '@OUTPUT@',
        '@INPUT@',
    ],
)

sh_optinit_gen = custom_target('optinit',
    input : 'option.list',
    output : 'optinit.h',
    command : [
        curdir / 'mkoptions.sh',
        '@INPUT@',
        'optinit.h',
        bldir,
    ],
)

gen_headers = declare_dependency(
    sources : [
        mkbuiltins_gen[0],
        mknodes_gen[0],
        mknodenames_gen,
        mktokens_gen,
        sh_optinit_gen,
    ]
)

sh_prog = executable(
    'sh',
    sh_sources + sh_bltins + [
        mkbuiltins_gen,
        mknodes_gen,
        mknodenames_gen,
        mktokens_gen,
        sh_init_gen,
        sh_optinit_gen,
    ],
    c_args : [
        '-DSHELL',
        '-DUSE_LRAND48',
        '-DREJECT_NULS',
        '-Wno-unused-but-set-variable',
    ],
    include_directories : [ inc, cinc, 'bltin' ],
    link_with : [libcompat],
    dependencies : [ libedit, tinfo, gen_headers ],
    install : true,
)

install_man('sh.1')
