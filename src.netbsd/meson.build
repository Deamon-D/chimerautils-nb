# compat library

cinc = include_directories('include')
subdir('compat')

# public util library
subdir('util')

# dbcompat library

dbinc = include_directories('dbinclude')
subdir('dbcompat')

# standalone toplevel projects

subdir('awk')
subdir('apply')
subdir('compress')
subdir('ed')
subdir('gencat')
subdir('grep')
subdir('jot')
subdir('m4')
subdir('netcat')
subdir('patch')
subdir('sed')
subdir('sh')
subdir('tip')
subdir('unvis')
subdir('vis')

# not ported
#if not get_option('pam').disabled() and pam.found()
#    subdir('su')
#endif

if not get_option('zlib').disabled() and zlib.found()
    subdir('gzip')
endif

# not ported
#if ncurses.found()
#    subdir('nvi')
#    subdir('telnet')
#endif

# tool collections

subdir('coreutils')
subdir('diffutils')
subdir('findutils')
subdir('miscutils')

# generic utilities
subdir('genutils')
