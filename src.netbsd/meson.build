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
subdir('bc')
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

if not get_option('zlib').disabled() and zlib.found()
    subdir('gzip')
endif

if tinfo.found()
    subdir('telnet')
endif

# tool collections

subdir('coreutils')
subdir('diffutils')
subdir('findutils')
subdir('miscutils')

# generic utilities
subdir('genutils')
