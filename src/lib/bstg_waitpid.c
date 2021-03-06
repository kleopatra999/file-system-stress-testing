/*
 * Copyright 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/cdefs.h>

#include "bstg.h"

__RCSID("$Id$");


pid_t
bstg_waitpid(pid_t childpid, int *status, int ticks)
{
    int count;

    /* parent should busywait for the child to terminate */
    for(count = 0; ;count++) {
        if (count > ticks) {
            kill(childpid, SIGKILL);
        }

        if (waitpid(childpid, status, WNOHANG) == childpid) {
            return childpid;
        }

        usleep(250000);
    }

    return -1;
}

