/*****************************************************************************\
 *  Copyright (c) 2014 Lawrence Livermore National Security, LLC.  Produced at
 *  the Lawrence Livermore National Laboratory (cf, AUTHORS, DISCLAIMER.LLNS).
 *  LLNL-CODE-658032 All rights reserved.
 *
 *  This file is part of the Flux resource manager framework.
 *  For details, see https://github.com/flux-framework.
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the license, or (at your option)
 *  any later version.
 *
 *  Flux is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the terms and conditions of the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *  See also:  http://www.gnu.org/licenses/
\*****************************************************************************/

/* flux-peer.c - flux peer subcommand */

#if HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <getopt.h>
#include <assert.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdbool.h>
#include <czmq.h>
#include <json.h>

#include "argv.h"
#include "log.h"
#include "shortjson.h"

#include "flux.h"
#include "api.h"
#include "live.h"

#define OPTIONS "+hr:"
static const struct option longopts[] = {
    {"help",       no_argument,        0, 'h'},
    {"rank",       required_argument,  0, 'r'},
    { 0, 0, 0, 0 },
};

void usage (void)
{
    fprintf (stderr,
"Usage: flux-comms [-r N] idle\n"
"       flux-comms [-r N] getattr attr\n"
"       flux-comms        info\n"
"       flux-comms [-r N] reparent new-parent-uri\n"
"       flux-comms [-r N] panic [msg ...]\n"
"       flux-comms [-r N] failover\n"
"       flux-comms [-r N] recover\n"
"       flux-comms        recover-all\n"
);
    exit (1);
}

int main (int argc, char *argv[])
{
    flux_t h;
    int ch;
    int rank = -1; /* local */
    char *cmd;

    log_init ("flux-comms");

    while ((ch = getopt_long (argc, argv, OPTIONS, longopts, NULL)) != -1) {
        switch (ch) {
            case 'h': /* --help */
                usage ();
                break;
            case 'r': /* --rank N */
                rank = strtoul (optarg, NULL, 10);
                break;
            default:
                usage ();
                break;
        }
    }
    if (optind == argc)
        usage ();
    cmd = argv[optind++];
    if (rank != -1 && (!strcmp (cmd, "recover-all") || !strcmp (cmd, "info")))
        usage ();

    if (!(h = flux_api_open ()))
        err_exit ("flux_api_open");

    if (!strcmp (cmd, "reparent")) {
        if (optind != argc - 1)
            usage ();
        if (flux_reparent (h, rank, argv[optind]) < 0)
            err_exit ("flux_reparent");
    } else if (!strcmp (cmd, "idle")) {
        if (optind != argc)
            usage ();
        JSON peers;
        if (!(peers = flux_lspeer (h, rank)))
            err_exit ("flux_peer");
        printf ("%s\n", Jtostr (peers));
        Jput (peers);
    } else if (!strcmp (cmd, "getattr")) {
        char *s;
        if (optind != argc - 1)
            msg_exit ("getattr cmbd-snoop-uri, cmbd-parent-uri, or cmbd-request-uri");
        if (!(s = flux_getattr (h, rank, argv[optind])))
            err_exit ("%s", argv[optind]);
        printf ("%s\n", s);
        free (s);
    } else if (!strcmp (cmd, "panic")) {
        char *msg = NULL;
        if (optind < argc)
            msg = argv_concat (argc - optind, argv + optind, " ");
        flux_panic (h, rank, msg);
        if (msg)
            free (msg);
    } else if (!strcmp (cmd, "failover")) {
        if (optind != argc)
            usage ();
        if (flux_failover (h, rank) < 0)
            err_exit ("flux_failover");
    } else if (!strcmp (cmd, "recover")) {
        if (optind != argc)
            usage ();
        if (flux_recover (h, rank) < 0)
            err_exit ("flux_recover");
    } else if (!strcmp (cmd, "allrecover")) {
        if (optind != argc)
            usage ();
        if (flux_recover_all (h) < 0)
            err_exit ("flux_recover_all");
    } else if (!strcmp (cmd, "info")) {
        int rank, size;
        bool treeroot;
        if (flux_info (h, &rank, &size, &treeroot) < 0)
            err_exit ("flux_info");
        printf ("rank=%d\n", rank);
        printf ("size=%d\n", size);
        printf ("treeroot=%s\n", treeroot ? "true" : "false");
    } else
        usage ();

    flux_api_close (h);
    log_fini ();
    return 0;
}

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */