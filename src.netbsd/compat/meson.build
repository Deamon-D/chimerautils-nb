libcompat_sources = [
    'getbsize.c',
    'humanize_number.c',
    'merge.c',
     yacc.process('parsedate.y'),
    'pwcache.c',
    'setmode.c',
    'strmode.c',
    'strpct.c',
    'unvis.c',
    'vis.c',
    '../../src.compat/b64.c',
    '../../src.compat/heapsort.c',
    '../../src.compat/err.c',
    '../../src.compat/strlfuncs.c',
    '../../src.compat/signames.c',
    '../../src.compat/strtoi.c',
]

libcompat = static_library(
    'compat',
    libcompat_sources,
    include_directories: [inc, cinc],
    c_args: ['-D_DIAGASSERT(x)='],
)
