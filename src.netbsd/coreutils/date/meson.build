date_prog = executable(
    'date',
    ['date.c', 'netdate.c',],
    include_directories: [ inc, cinc ],
    link_with: [libcompat],
    install: true,
)

install_man('date.1')
