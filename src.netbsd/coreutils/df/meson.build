df_prog = executable(
    'df', ['df.c'],
    include_directories: inc,
    link_with: [libcompat],
    install: true,
)

install_man('df.1')
