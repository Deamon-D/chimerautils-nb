# chimerautils-nb

An unofficial flavor of the Chimera Linux's core userland. It consists of the following:

* Ports of NetBSD tools
* An internal library providing a compat interface to simplify porting
* Custom-made new tools
* A Meson-based build system

It replaces the following GNU projects:

* coreutils
* findutils
* diffutils
* grep
* sed
* ed
* m4
* patch
* gzip
* gawk

It also provides the following functionality:

* apply
* tip/cu
* gencat
* jot
* nc
* sh
* vis
* unvis
* compress
* uncompress
* portions of util-linux
* and additional custom tools

In a way, `chimerautils-nb` is also an alternative to projects like Busybox.

## chimerautils-nb

Chimerautils-nb is a fork of [chimerautils](https://github.com/chimera-linux/chimerautils) that
uses NetBSD as base instead of FreeBSD.

## bsdutils

Chimerautils itself is a fork of [bsdutils](https://codeberg.org/dcantrell/bsdutils)
by David Cantrell. Chimerautils were created in order to provide a more
complete package that prioritizes Chimera's needs and development pace.

## Building

Chimerautils-nb requires a Linux system with a Clang or GCC compiler.

You will also need the following:

* `meson` and `ninja`
* `flex` (or another `lex`)
* `byacc` (`bison` has not been tested)
* `libcrypto` (for xinstall, cksum and others)
* `ncurses` or another provider of `terminfo` (for cal and others)

To build:

```
$ mkdir build && cd build
$ meson ..
$ ninja all
```

## Importing a new NetBSD release

When a new release of NetBSD is made, the import-src.sh script should
be used to update the source tree.  First edit upstream.conf and then
run the import-src.sh script.  The script will fetch the new release
source and copy in the source for the commands we have.  Any patches
in patches/ will be applied.  These may need updating between
releases, so keep that in mind.  The workflow is basically:

1) Change VER in upstream.conf

2) Verify URL in upstream.conf works (NetBSD may move things around).

3) Run ./import-src.sh.  It is adviseable to capture stdout and stderr
to see what patches fail to apply.  Any that fail, you want to
manually fix and then run import-src.sh again to get a clean import of
the version you are updating to.

4) Now build all the commands and fix any new build errors.

Once this is clean, you can commit the import of the new version of
NetBSD code.  The import-src.sh and patches step is meant to make it
more clear what changes I apply to NetBSD code from release to
release and also if any external projects want to use these patches
and the NetBSD source directly.
