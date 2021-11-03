// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// License: 0BSD

#include <cstddef>
#include <cstdio>

#include <orbis/SystemService.h>
#include <orbis/libkernel.h>

#include "libLog_stub.h"
#include "libjbc_stub.h"
#include "notifi.h"

// Handles for the libraries
int g_LibLogHandle = -1;
int g_LibJbcHandle = -1;

// Variables for (un)jailbreaking
jbc_cred g_Cred;
jbc_cred g_RootCreds;

// Verify jailbreak
bool is_jailbroken() {
  FILE *s_FilePointer = fopen("/user/.jailbreak", "w");
  if (!s_FilePointer) {
    return false;
  }

  fclose(s_FilePointer);
  remove("/user/.jailbreak");
  return true;
}

// Jailbreaks creds
void jailbreak() {
  if (is_jailbroken()) {
    return;
  }

  jbc_get_cred(&g_Cred);
  g_RootCreds = g_Cred;
  jbc_jailbreak_cred(&g_RootCreds);
  jbc_set_cred(&g_RootCreds);
}

// Restores original creds
void unjailbreak() {
  if (!is_jailbroken()) {
    return;
  }

  jbc_set_cred(&g_Cred);
}

// Unload loaded libraries
void terminate() {
  if (g_LibLogHandle >= 0) {
    sceKernelStopUnloadModule(g_LibLogHandle, 0, 0, 0, NULL, NULL);
  }
  if (g_LibJbcHandle >= 0) {
    sceKernelStopUnloadModule(g_LibJbcHandle, 0, 0, 0, NULL, NULL);
  }
}

// This function will display p_Message, then "cleanly" close the application
void fail(const char *p_Message) {
  printf("%s", p_Message);
  notifi(NULL, "%s", p_Message);
  terminate();
  sceSystemServiceLoadExec("exit", NULL);
}

// Initalize libraries (PRXs)
void initialize() {
  if ((g_LibLogHandle = sceKernelLoadStartModule("/app0/sce_module/libLog.prx", 0, 0, 0, NULL, NULL)) < 0) {
    fail("Failed to start the libLog library");
  }

  if (logInitalize(g_LibLogHandle) != 0) {
    fail("Failed to initialize the libLog library's functions");
  }

  // We know the logging is initalized here so we can use it after this point
  logKernel(LL_Info, "%s", "libLog.prx Initialized");

  if ((g_LibJbcHandle = sceKernelLoadStartModule("/app0/sce_module/libjbc.prx", 0, 0, 0, NULL, NULL)) < 0) {
    fail("Failed to start the libjbc library");
  }

  if (jbcInitalize(g_LibJbcHandle) != 0) {
    fail("Failed to initialize the libjbc library's functions");
  }

  logKernel(LL_Info, "%s", "libjbc.prx Initialized");
}

int main() {
  // Initialize libraries
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

  // Unload libraries
  terminate();

  // "Clean" close
  sceSystemServiceLoadExec("exit", NULL);

  // We should never get here
  for (;;) {
  }

  return 0;
}
