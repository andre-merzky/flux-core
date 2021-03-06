/************************************************************\
 * Copyright 2018 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef _FLUX_JOB_MANAGER_KILL_H
#define _FLUX_JOB_MANAGER_KILL_H

#include <stdint.h>
#include "job-manager.h"

/* Handle a request to raise an exception on job.
 */
void kill_handle_request (flux_t *h,
                          flux_msg_handler_t *mh,
                          const flux_msg_t *msg,
                          void *arg);


/* exposed for unit testing only */
int kill_check_signal (int signum);
int kill_allow (uint32_t rolemask, uint32_t userid, uint32_t job_userid);

#endif /* ! _FLUX_JOB_MANAGER_RAISE_H */
/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
