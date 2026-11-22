libcompat_sources = [
    'getbsize.c',
    'humanize_number.c',
    'merge.c',
    'strtonum.c',
     yacc.process('parsedate.y'),
    'fparseln.c',
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
    '../../src.compat/signals.c',
    '../../src.compat/strtoi.c',
]

libcompat = static_library(
    'compat',
    libcompat_sources,
    include_directories: [inc, cinc],
    c_args: ['-D_DIAGASSERT(x)=', '-Wno-array-bounds', '-Wno-unused-but-set-variable'],
)
