sort_srcs = [
    'append.c', 'fields.c', 'files.c', 'fsort.c',
    'init.c', 'msort.c', 'sort.c', 'tmp.c',
    'radix_sort.c',
]

sort_prog = executable(
    'sort', sort_srcs,
    include_directories: [inc],
    link_with: [libcompat],
    install: true,
)

install_man('sort.1')
