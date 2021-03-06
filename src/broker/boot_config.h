/************************************************************\
 * Copyright 2018 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef BROKER_BOOT_CONFIG_H
#define BROKER_BOOT_CONFIG_H

/* boot_config - bootstrap broker/overlay from config file */

/* Usage: flux broker -Sboot.method=config
 *
 * Example config file (TOML):
 *
 *   [bootstrap]

 *   # tbon-endpoints array is ordered by rank (zeromq URI format)
 *   tbon-endpoints = [
 *       "tcp://192.168.1.100:8020",  # rank 0
 *       "tcp://192.168.1.101:8020",  # rank 1
 *       "tcp://192.168.1.102:8020",  # rank 2
 *   ]
 *
 *   # if commented out, rank is determined by scanning tbon-endpoints
 *   # for a local address
 *   rank = 2
 *
 *   # if commented out, instance size is the size of tbon-endpoints.
 *   size = 3
 *
 * Caveat: the tbon-endpoints array entries specify a ZMQ endpoint used
 * in both "bind" and "connect" API calls.  ZMQ "bind" endpoints accept
 * an IP address or an interface name.  ZMQ "connect" endpoints accept
 * an IP address or hostname.  Therefore only IPs -- not hostnames, and not
 * interface names -- may be used here.
 */

#include "attr.h"
#include "overlay.h"

/* Broker attributes read/written directly by this method:
 *   tbon.endpoint (w)
 *   instance-level (w)
 */

int boot_config (flux_t *h, overlay_t *overlay, attr_t *attrs, int tbon_k);

#endif /* BROKER_BOOT_CONFIG_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
