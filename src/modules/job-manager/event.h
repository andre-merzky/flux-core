/************************************************************\
 * Copyright 2019 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef _FLUX_JOB_MANAGER_EVENT_H
#define _FLUX_JOB_MANAGER_EVENT_H

#include <stdarg.h>
#include <flux/core.h>
#include <jansson.h>

#include "job.h"
#include "job-manager.h"

/* Take any action for 'job' currently needed based on its internal state.
 * Returns 0 on success, -1 on failure with errno set.
 * This function is idempotent.
 */
int event_job_action (struct event *event, struct job *job);

/* Call to update 'job' internal state based on 'event'.
 * Returns 0 on success, -1 on failure with errno set.
 */
int event_job_update (struct job *job, json_t *event);

/* Add notification of job's state transition to its current state
 * to batch for publication.
 */
int event_batch_pub_state (struct event *event, struct job *job);

/* Post event 'name' and optionally 'context' to 'job'.
 * Internally, calls event_job_update(), then event_job_action(), then commits
 * the event to job KVS eventlog.  The KVS commit completes asynchronously.
 * The future passed in as an argument should not be destroyed.
 * Returns 0 on success, -1 on failure with errno set.
 */
int event_job_post_pack (struct event *event,
                         struct job *job,
                         const char *name,
                         const char *context_fmt,
                         ...);

void event_ctx_destroy (struct event *event);
struct event *event_ctx_create (struct job_manager *ctx);

#endif /* _FLUX_JOB_MANAGER_EVENT_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */

