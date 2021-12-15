// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// License: 0BSD

#include "utils.h"

#include "libLog.h"
#include "notifi.h"

#include <orbis/SystemService.h>
#include <orbis/libkernel.h>

#include <stddef.h>

// Terminate
void terminate() {
  // Cleanup whatever you initialized in `initialize()`
}

// This function will display p_Message, then "cleanly" close the application
void fail(const char *p_Message) {
  printf("%s", p_Message);
  notifi(NULL, "%s", p_Message);
  terminate();
  sceSystemServiceLoadExec("exit", NULL);
}

// Initalize
void initialize() {
  // Initialize libraries and whatnot here
}

int main() {
  // Initialize
  initialize();

  // Jailbreak
  jailbreak();

  // Pop notification depending on jailbreak result
  if (is_jailbroken()) {
    notifi(NULL, "%s", "Jailbreak succeeded!");
  } else {
    notifi(NULL, "%s", "Jailbreak failed!");
  }

  // Back to jail
  unjailbreak();

  // Sleep for 7 seconds so the system has time to display the notification
  sceKernelSleep(7);

  // Terminate
  terminate();

  // "Clean" close
  sceSystemServiceLoadExec("exit", NULL);

  // We should never get here
  for (;;) {
  }

  return 0;
}
