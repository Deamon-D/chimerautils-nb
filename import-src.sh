#!/bin/sh
#
# import-src.sh - Import specific release of NetBSD source in to
#                 this tree.  Primarily for maintenance use when
#                 a new version of NetBSD comes out.
#
# Original author: David Cantrell <david.l.cantrell@gmail.com>
# Adapted by: littlefly365
set -e

PATH=/bin:/usr/bin
CWD="$(pwd)"
TMPDIR="$(mktemp -d -p ${CWD})"
. ${CWD}/upstream.conf

fail_exit() {
    cd ${CWD}
    rm -rf ${TMPDIR}
    exit 1
}

rm -rf src.orig
mkdir -p src.orig src.netbsd

SRCTAR=
if [ -n "$1" ]; then
    [ -r "$1" ] || fail_exit
    SRCTAR=$(realpath "$1")
fi

cd ${TMPDIR}
if [ -z "$SRCTAR" ]; then
    SRCTAR="src.tgz"
    curl -L --retry 3 --ftp-pasv -o "$SRCTAR" "$SRC" || fail_exit
    echo "SHA512 ($SRCTAR) = $SHA512" | cksum -a sha512 -c >/dev/null 2>&1 || fail_exit
fi
tar -xf "$SRCTAR"

copy_cmd() {
    p="$1"
    sd="$2"
    dn="$3"
    rp="usr/src/${p}"
    sp="$(basename ${p})"
    [ -z "$dn" ] && dn="$sp"
    if [ -n "$sd" ]; then
        dp="${sd}/${dn}"
    else
        dp="$dn"
    fi

    # Drop the tests directories
    [ -d ${rp}/test ] && rm -rf ${rp}/test
    [ -d ${rp}/TEST ] && rm -rf ${rp}/TEST

    # Drop the CVS directories
    [ -d ${rp}/CVS ] && rm -rf ${rp}/CVS

    # Rename the upstream Makefile for later manual checking.  We don't
    # commit these to our tree, but just look at them when rebasing and
    # pick up any rule changes to put in our Makefile.am files.
    if [ -f "${rp}/Makefile" ]; then
        mv ${rp}/Makefile ${rp}/Makefile.bsd
    fi

    # Copy in the upstream files
    [ -d ${CWD}/src.orig/${dp} ] || mkdir -p ${CWD}/src.orig/${dp}
    [ -d ${CWD}/src.netbsd/${dp} ] || mkdir -p ${CWD}/src.netbsd/${dp}
    cp -pr ${rp}/* ${CWD}/src.orig/${dp}
    cp -pr ${rp}/* ${CWD}/src.netbsd/${dp}
}

# coreutils
CMDS_CORE="
bin/cat
bin/chmod
bin/cp
bin/date
bin/dd
bin/df
bin/echo
bin/expr
bin/hostname
bin/ln
bin/ls
bin/mkdir
bin/mv
bin/pwd
bin/rm
bin/rmdir
bin/sleep
bin/stty
bin/sync
bin/test
sbin/chown
sbin/mknod
usr.bin/base64
usr.bin/basename
usr.bin/cksum
usr.bin/comm
usr.bin/csplit
usr.bin/cut
usr.bin/dirname
usr.bin/du
usr.bin/env
usr.bin/expand
usr.bin/false
usr.bin/fmt
usr.bin/fold
usr.bin/head
usr.bin/id
usr.bin/join
usr.bin/logname
usr.bin/mkfifo
usr.bin/mktemp
usr.bin/nice
usr.bin/nl
usr.bin/nohup
usr.bin/paste
usr.bin/pathchk
usr.bin/pr
usr.bin/printenv
usr.bin/printf
usr.bin/realpath
usr.bin/seq
usr.bin/sort
usr.bin/split
usr.bin/stat
usr.bin/tail
usr.bin/tee
usr.bin/timeout
usr.bin/touch
usr.bin/tr
usr.bin/true
usr.bin/tsort
usr.bin/tty
usr.bin/uname
usr.bin/unexpand
usr.bin/uniq
usr.bin/users
usr.bin/wc
usr.bin/who
usr.bin/yes
usr.bin/xinstall
usr.sbin/chroot
usr.sbin/link
usr.sbin/unlink
games/factor
"

# diffutils
CMDS_DIFF="
usr.bin/cmp
usr.bin/sdiff
"
#usr.bin/diff
#usr.bin/diff3


# findutils
CMDS_FIND="
usr.bin/find
usr.bin/xargs
"
CMDS_FIND_LOCATE="
usr.bin/locate/bigram
usr.bin/locate/code
usr.bin/locate/locate
"

# mostly util-linux
CMDS_MISC="
bin/kill
usr.bin/calendar
usr.bin/col
usr.bin/colrm
usr.bin/column
usr.bin/flock
usr.bin/getopt
usr.bin/hexdump
usr.bin/indent
usr.bin/logger
usr.bin/look
usr.bin/mesg
usr.bin/cal
usr.bin/renice
usr.bin/rev
usr.bin/script
usr.bin/time
usr.bin/ul
usr.bin/wall
usr.bin/whereis
usr.bin/write
"

for p in ${CMDS_CORE}; do
    copy_cmd "$p" coreutils
done

for p in ${CMDS_DIFF}; do
    copy_cmd "$p" diffutils
done

for p in ${CMDS_FIND}; do
    copy_cmd "$p" findutils
done

for p in ${CMDS_FIND_LOCATE}; do
    copy_cmd "$p" findutils/locate
done

for p in ${CMDS_MISC}; do
    copy_cmd "$p" miscutils
done

# equivalents of standalone projects
copy_cmd bin/ed
copy_cmd bin/sh
copy_cmd usr.bin/apply
copy_cmd usr.bin/compress
copy_cmd usr.bin/gencat
copy_cmd usr.bin/grep
copy_cmd usr.bin/gzip
copy_cmd usr.bin/jot
copy_cmd usr.bin/m4
copy_cmd usr.bin/patch
copy_cmd usr.bin/sed
copy_cmd usr.bin/su
copy_cmd usr.bin/tip
copy_cmd usr.bin/vis
copy_cmd usr.bin/unvis
copy_cmd usr.bin/nc "" netcat
#copy_cmd contrib/nvi
copy_cmd external/historical/nawk/dist "" awk
#copy_cmd contrib/telnet

# 'compat' is our static library with a subset of BSD library functions
mkdir -p ${CWD}/src.orig/compat ${CWD}/src.orig/include
cp -p usr/src/lib/libc/gen/getbsize.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/humanize_number.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libutil/parsedate.y ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/stdlib/merge.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/setmode.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/string/strmode.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/vis.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/unvis.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/pwcache.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libutil/strpct.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/stdlib/strtonum.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/stdio/fparseln.c ${CWD}/src.orig/compat
cp -p usr/src/lib/libc/gen/pwcache.h ${CWD}/src.orig/include
cp -p usr/src/include/vis.h ${CWD}/src.orig/include

# 'util' is our public library with stuff that may be missing in libc
mkdir -p ${CWD}/src.orig/util
cp -p usr/src/lib/libc/gen/fts.c ${CWD}/src.orig/util
cp -p usr/src/lib/libc/gen/fts.3 ${CWD}/src.orig/util
cp -p usr/src/include/fts.h ${CWD}/src.orig/include

mkdir -p ${CWD}/src.netbsd/compat ${CWD}/src.netbsd/include ${CWD}/src.netbsd/util
cp -p ${CWD}/src.orig/compat/* ${CWD}/src.netbsd/compat
cp -p ${CWD}/src.orig/include/* ${CWD}/src.netbsd/include
cp -p ${CWD}/src.orig/util/* ${CWD}/src.netbsd/util

# 'dbcompat' is our subset of berkeley db 1.85
mkdir -p ${CWD}/src.orig/dbcompat/btree ${CWD}/src.orig/dbcompat/recno ${CWD}/src.orig/dbinclude
cp -p usr/src/lib/libc/db/db/db.c ${CWD}/src.orig/dbcompat
cp -p usr/src/lib/libc/db/mpool/mpool.c ${CWD}/src.orig/dbcompat
cp -p usr/src/lib/libc/db/btree/*.[ch] ${CWD}/src.orig/dbcompat/btree
cp -p usr/src/lib/libc/db/recno/*.[ch] ${CWD}/src.orig/dbcompat/recno
cp -p usr/src/include/db.h ${CWD}/src.orig/dbinclude
cp -p usr/src/include/mpool.h ${CWD}/src.orig/dbinclude

mkdir -p ${CWD}/src.netbsd/dbcompat ${CWD}/src.netbsd/dbinclude
cp -pr ${CWD}/src.orig/dbcompat/* ${CWD}/src.netbsd/dbcompat
cp -pr ${CWD}/src.orig/dbinclude/* ${CWD}/src.netbsd/dbinclude

# These files are needed for the factor command
cp -p usr/src/games/primes/primes.h ${CWD}/src.orig/coreutils/factor
cp -p usr/src/games/primes/pr_tbl.c ${CWD}/src.orig/coreutils/factor
cp -p usr/src/games/primes/primes.h ${CWD}/src.netbsd/coreutils/factor
cp -p usr/src/games/primes/pr_tbl.c ${CWD}/src.netbsd/coreutils/factor

# This function is needed for the wall command
cp -p usr/src/lib/libutil/ttymsg.c ${CWD}/src.orig/miscutils/wall
cp -p usr/src/lib/libutil/ttymsg.c ${CWD}/src.netbsd/miscutils/wall

# This file is needed for the time command
cp -p usr/src/bin/csh/time.c ${CWD}/src.orig/miscutils/time/csh_time.c
cp -p usr/src/bin/csh/time.c ${CWD}/src.netbsd/miscutils/time/csh_time.c

# xinstall uses functions of this file
cp -p usr/src/usr.sbin/mtree/getid.c ${CWD}/src.orig/coreutils/xinstall/
cp -p usr/src/usr.sbin/mtree/mtree.h ${CWD}/src.orig/coreutils/xinstall/
cp -p usr/src/usr.sbin/mtree/getid.c ${CWD}/src.netbsd/coreutils/xinstall/
cp -p usr/src/usr.sbin/mtree/mtree.h ${CWD}/src.netbsd/coreutils/xinstall/

# fmt uses this file from mail
cp -p usr/src/usr.bin/mail/head.c ${CWD}/src.orig/coreutils/fmt
cp -p usr/src/usr.bin/mail/head.c ${CWD}/src.netbsd/coreutils/fmt

# This header is required for some programs
cp -p usr/src/include/tzfile.h ${CWD}/src.orig/include
cp -p usr/src/include/tzfile.h ${CWD}/src.netbsd/include

# sh uses this internal header
cp -p usr/src/lib/libedit/filecomplete.h ${CWD}/src.orig/include
cp -p usr/src/lib/libedit/filecomplete.h ${CWD}/src.netbsd/include

# These are not used
rm -rf ${CWD}/src.orig/coreutils/sort/nls
rm -rf ${CWD}/src.netbsd/coreutils/sort/nls
rm -rf ${CWD}/src.orig/grep/nls
rm -rf ${CWD}/src.netbsd/grep/nls

# fix sh generator permissions
chmod 755 ${CWD}/src.orig/sh/mkbuiltins
chmod 755 ${CWD}/src.orig/sh/mktokens
chmod 755 ${CWD}/src.netbsd/sh/mkbuiltins
chmod 755 ${CWD}/src.netbsd/sh/mktokens

# remove sh files we don't want
rm -rf ${CWD}/src.orig/sh/dot.*
rm -rf ${CWD}/src.orig/sh/funcs
rm -f ${CWD}/src.orig/sh/profile
rm -rf ${CWD}/src.netbsd/sh/dot.*
rm -rf ${CWD}/src.netbsd/sh/funcs
rm -f ${CWD}/src.netbsd/sh/profile

# tip cap parser
cp -p usr/src/lib/libc/gen/getcap.c ${CWD}/src.orig/tip
cp -p usr/src/lib/libc/gen/getcap.c ${CWD}/src.netbsd/tip
rm -f ${CWD}/src.netbsd/tip/getcap.h

# temove telnetd
rm -rf ${CWD}/src.orig/telnet/telnetd
rm -rf ${CWD}/src.netbsd/telnet/telnetd

# meh
rm -rf ${CWD}/src.orig/awk/testdir
rm -rf ${CWD}/src.netbsd/awk/testdir
rm -rf ${CWD}/src.orig/m4/lib/strtonum.c
rm -rf ${CWD}/src.netbsd/m4/lib/strtonum.c

#####################
# APPLY ANY PATCHES #
#####################

cd ${CWD}/patches

for p in *.patch; do
    [ -f "$p" ] || continue
    patch -d ${CWD}/src.netbsd -p1 < $p
done

# Clean up
rm -rf ${TMPDIR}
