/**
 * ecutools: IoT Automotive Tuning, Diagnostics & Analytics
 * Copyright (C) 2014  Jeremy Hahn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include "j2534.h"

int main_exit(int exit_status) {
  syslog(LOG_DEBUG, "exiting j2534_client");
  closelog();
  return exit_status;
}

int main(int argc, char **argv) {

  openlog("ecutune", LOG_CONS | LOG_PERROR, LOG_USER);
  syslog(LOG_DEBUG, "starting j2534_client");

  unsigned long *pDeviceCount = 0;
  unsigned long rc = PassThruScanForDevices(&pDeviceCount);
  syslog(LOG_DEBUG, "PassThruScanForDevices: pDeviceCount=%d, error: %d", pDeviceCount, rc);

  if(rc != STATUS_NOERROR) {
    char errmsg[80] = "\0";
    PassThruGetLastError(&errmsg);
    syslog(LOG_ERR, "PassThruGetLastError: %s", errmsg);
  }

  return main_exit(EXIT_SUCCESS);
}
