/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2026 littlefly365
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef PWD_H
#define PWD_H

#include <stdint.h>
#include_next <pwd.h>
#include_next <grp.h>

const char *user_from_uid(uid_t uid, int noname);
int uid_from_user(const char *name, uid_t *uid);
int pwcache_userdb(
	int		(*a_setpassent)(int),
	void		(*a_endpwent)(void),
	struct passwd *	(*a_getpwnam)(const char *),
	struct passwd *	(*a_getpwuid)(uid_t));

const char *group_from_gid(gid_t gid, int noname);
int gid_from_group(const char *name, gid_t *gid);
int pwcache_groupdb(
	int		(*a_setgroupent)(int),
	void		(*a_endgrent)(void),
	struct group *	(*a_getgrnam)(const char *),
	struct group *	(*a_getgrgid)(gid_t));

#ifndef UID_MAX
#define UID_MAX UINT_MAX
#endif

#ifndef GID_MAX
#define GID_MAX UINT_MAX
#endif
#endif
