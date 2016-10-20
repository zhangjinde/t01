/*
 * Copyright (c) 2016, YAO Wei <njustyw at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef IO_IOENGINE_H
#define IO_IOENGINE_H

#define io_init	__attribute__((constructor))
#define io_exit	__attribute__((destructor))

#include "list.h"

struct ioengine_ops;

struct ioengine_data {
	void *private;
	struct ioengine_ops* io_ops;
};

struct ioengine_ops {
	struct list_head list;
	const char *name;
	int (*connect)(struct ioengine_data *, const char *);
	int (*disconnect)(struct ioengine_data *);
	int (*show_help)();
	int (*write)(struct ioengine_data *, const char *, int);
};


extern int load_ioengine(struct ioengine_data *, const char *);
extern int init_ioengine(struct ioengine_data *, const char *);
extern void close_ioengine(struct ioengine_data *);
extern int store_via_ioengine(struct ioengine_data *, void *, const char *, const char *, int);

extern void register_ioengine(struct ioengine_ops *);
extern void unregister_ioengine(struct ioengine_ops *);

extern int fio_show_ioengine_help(const char *engine);


#endif