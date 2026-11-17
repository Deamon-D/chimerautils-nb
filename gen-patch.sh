#!/bin/sh
#
# this just generates a clean patch between src.orig and src.netbsd

diff -Naur -x meson.build -x '*.orig' src.orig src.netbsd | \
    sed -e '/^diff -Naur/d' \
        -e 's/^\([+-][+-][+-][[:space:]][a-zA-Z0-9/._]*\).*/\1/g'
