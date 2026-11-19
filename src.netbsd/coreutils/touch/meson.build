touch_prog = executable(
    'touch',
    ['touch.c'],
    dependencies : [libm],
    include_directories: [inc, cinc],
    link_with: [libcompat],
    install: true,
)

install_man('touch.1')
