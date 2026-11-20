find_prog = executable(
    'find',
    ['find.c', 'function.c', 'ls.c', 'main.c', 'misc.c', 'operator.c', 'option.c'],
    include_directories: [inc, cinc],
    link_with: [libcompat],
    install: true,
)

install_man('find.1')
