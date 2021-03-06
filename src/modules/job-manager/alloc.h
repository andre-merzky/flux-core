/************************************************************\
 * Copyright 2019 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef _FLUX_JOB_MANAGER_ALLOC_H
#define _FLUX_JOB_MANAGER_ALLOC_H

#include <flux/core.h>

#include "job.h"
#include "job-manager.h"

void alloc_ctx_destroy (struct alloc *alloc);
struct alloc *alloc_ctx_create (struct job_manager *ctx);

/* Call from SCHED state to put job in queue to request resources.
 * This function is a no-op if job->alloc_queued or job->alloc_pending is set.
 */
int alloc_enqueue_alloc_request (struct alloc *alloc, struct job *job);

/* Dequeue job from sched inqueue, e.g. on exception.
 * This function is a no-op if job->alloc_queued is not set.
 */
void alloc_dequeue_alloc_request (struct alloc *alloc, struct job *job);

/* Call from CLEANUP state to release resources.
 * This function is a no-op if job->free_pending is set.
 */
int alloc_send_free_request (struct alloc *alloc, struct job *job);

/* List pending jobs
 */
struct job *alloc_pending_first (struct alloc *alloc);
struct job *alloc_pending_next (struct alloc *alloc);

/* Reorder job in scheduler queue, e.g. after priority change.
 */
void alloc_pending_reorder (struct alloc *alloc, struct job *job);

#endif /* ! _FLUX_JOB_MANAGER_ALLOC_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
