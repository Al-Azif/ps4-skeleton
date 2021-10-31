// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

// License: LGPL-3.0

#ifndef LIBLOG_H
#define LIBLOG_H

#ifdef __cplusplus
// TODO: C++ stream bindings includes here

extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef __LIBLOG_PC__
#include <orbis/libkernel.h>
#endif

enum LogLevels {
  LL_None,
  LL_Fatal,
  LL_Error,
  LL_Warn,
  LL_Info,
  LL_Debug,
  LL_Trace,
  LL_All
};

enum PrintTypes {
  PT_Print,
  PT_Kernel,
  PT_Socket,
  PT_File,
};

#ifndef __LIBLOG_PC__
void (*_logPrint)(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, bool p_Meta, const char *p_File, int p_Line, const char *p_Format, ...) = NULL;
void (*_logPrintHex)(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, bool p_Meta, const char *p_File, int p_Line, const void *p_Pointer, int p_Length) = NULL;
void (*_logPrintBin)(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, const char *p_Input, uint16_t p_Port, const void *p_Pointer, int p_Length) = NULL;

bool (*logSocketOpen)(const char *p_IpAddress, uint16_t p_Port) = NULL;
bool (*logSocketClose)() = NULL;
bool (*logSocketIsOpen)() = NULL;

const char *(*logSocketGetIpAddress)() = NULL;
uint16_t (*logSocketGetPort)() = NULL;

bool (*logFileOpen)(const char *p_Path) = NULL;
bool (*logFileClose)() = NULL;
const char *(*logFileGetFilename)() = NULL;

void (*logSetLogLevel)(enum LogLevels p_LogLevel) = NULL;
enum LogLevels (*logGetLogLevel)() = NULL;

void (*logPrintSetLogLevel)(enum LogLevels p_LogLevel) = NULL;
enum LogLevels (*logPrintGetLogLevel)() = NULL;

void (*logKernelSetLogLevel)(enum LogLevels p_LogLevel) = NULL;
enum LogLevels (*logKernelGetLogLevel)() = NULL;

void (*logFileSetLogLevel)(enum LogLevels p_LogLevel) = NULL;
enum LogLevels (*logFileGetLogLevel)() = NULL;

void (*logSocketSetLogLevel)(enum LogLevels p_LogLevel) = NULL;
enum LogLevels (*logSocketGetLogLevel)() = NULL;

int logInitalize(int handle) {
  if (sceKernelDlsym(handle, "_logPrint", (void **)&_logPrint) != 0 ||
      sceKernelDlsym(handle, "_logPrintHex", (void **)&_logPrintHex) != 0 ||
      sceKernelDlsym(handle, "_logPrintBin", (void **)&_logPrintBin) != 0 ||

      sceKernelDlsym(handle, "logSocketOpen", (void **)&logSocketOpen) != 0 ||
      sceKernelDlsym(handle, "logSocketClose", (void **)&logSocketClose) != 0 ||
      sceKernelDlsym(handle, "logSocketIsOpen", (void **)&logSocketIsOpen) != 0 ||

      sceKernelDlsym(handle, "logSocketGetIpAddress", (void **)&logSocketGetIpAddress) != 0 ||
      sceKernelDlsym(handle, "logSocketGetPort", (void **)&logSocketGetPort) != 0 ||

      sceKernelDlsym(handle, "logFileOpen", (void **)&logFileOpen) != 0 ||
      sceKernelDlsym(handle, "logFileClose", (void **)&logFileClose) != 0 ||
      sceKernelDlsym(handle, "logFileGetFilename", (void **)&logFileGetFilename) != 0 ||

      sceKernelDlsym(handle, "logSetLogLevel", (void **)&logSetLogLevel) != 0 ||
      sceKernelDlsym(handle, "logGetLogLevel", (void **)&logGetLogLevel) != 0 ||

      sceKernelDlsym(handle, "logPrintSetLogLevel", (void **)&logPrintSetLogLevel) != 0 ||
      sceKernelDlsym(handle, "logPrintGetLogLevel", (void **)&logPrintGetLogLevel) != 0 ||

      sceKernelDlsym(handle, "logKernelSetLogLevel", (void **)&logKernelSetLogLevel) != 0 ||
      sceKernelDlsym(handle, "logKernelGetLogLevel", (void **)&logKernelGetLogLevel) != 0 ||

      sceKernelDlsym(handle, "logFileSetLogLevel", (void **)&logFileSetLogLevel) != 0 ||
      sceKernelDlsym(handle, "logFileGetLogLevel", (void **)&logFileGetLogLevel) != 0 ||

      sceKernelDlsym(handle, "logSocketSetLogLevel", (void **)&logSocketSetLogLevel) != 0 ||
      sceKernelDlsym(handle, "logSocketGetLogLevel", (void **)&logSocketGetLogLevel) != 0) {
    return -1;
  }

  return 0;
}

#else

void _logPrint(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, bool p_Meta, const char *p_File, int p_Line, const char *p_Format, ...);
void _logPrintHex(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, bool p_Meta, const char *p_File, int p_Line, const void *p_Pointer, int p_Length);
void _logPrintBin(enum LogLevels p_LogLevel, enum PrintTypes p_PrintType, const char *p_Input, uint16_t p_Port, const void *p_Pointer, int p_Length);

bool logSocketOpen(const char *p_IpAddress, uint16_t p_Port);
bool logSocketClose();
bool logSocketIsOpen();

const char *logSocketGetIpAddress();
uint16_t logSocketGetPort();

bool logFileOpen(const char *p_Path);
bool logFileClose();
const char *logFileGetFilename();

void logSetLogLevel(enum LogLevels p_LogLevel);
enum LogLevels logGetLogLevel();

void logPrintSetLogLevel(enum LogLevels p_LogLevel);
enum LogLevels logPrintGetLogLevel();

void logKernelSetLogLevel(enum LogLevels p_LogLevel);
enum LogLevels logKernelGetLogLevel();

void logFileSetLogLevel(enum LogLevels p_LogLevel);
enum LogLevels logFileGetLogLevel();

void logSocketSetLogLevel(enum LogLevels p_LogLevel);
enum LogLevels logSocketGetLogLevel();

#endif

#define logPrint(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Print, true, __FILE__, __LINE__, __VA_ARGS__)
#define logPrintUnformatted(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Print, false, __FILE__, __LINE__, __VA_ARGS__)
#define logPrintHexdump(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Print, true, __FILE__, __LINE__, p_Pointer, p_Length)
#define logPrintHexdumpUnformatted(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Print, false, __FILE__, __LINE__, p_Pointer, p_Length)

#define logKernel(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Kernel, true, __FILE__, __LINE__, __VA_ARGS__)
#define logKernelUnformatted(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Kernel, false, __FILE__, __LINE__, __VA_ARGS__)
#define logKernelHexdump(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Kernel, true, __FILE__, __LINE__, p_Pointer, p_Length)
#define logKernelHexdumpUnformatted(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Kernel, false, __FILE__, __LINE__, p_Pointer, p_Length)

#define logSocket(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Socket, true, __FILE__, __LINE__, __VA_ARGS__)
#define logSocketUnformatted(p_LogLevel, ...) _logPrint(p_LogLevel, PT_Socket, false, __FILE__, __LINE__, __VA_ARGS__)
#define logSocketHexdump(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Socket, true, __FILE__, __LINE__, p_Pointer, p_Length)
#define logSocketHexdumpUnformatted(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_Socket, false, __FILE__, __LINE__, p_Pointer, p_Length)

#define logFile(p_LogLevel, ...) _logPrint(p_LogLevel, PT_File, true, __FILE__, __LINE__, __VA_ARGS__)
#define logFileUnformatted(p_LogLevel, ...) _logPrint(p_LogLevel, PT_File, false, __FILE__, __LINE__, __VA_ARGS__)
#define logFileHexdump(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_File, true, __FILE__, __LINE__, p_Pointer, p_Length)
#define logFileHexdumpUnformatted(p_LogLevel, p_Pointer, p_Length) _logPrintHex(p_LogLevel, PT_File, false, __FILE__, __LINE__, p_Pointer, p_Length)

#define logSocketBindump(p_LogLevel, p_IpAddress, p_Port, p_Pointer, p_Length) _logPrintBin(p_LogLevel, PT_Socket, p_IpAddress, p_Port, p_Pointer, p_Length)
#define logFileBindump(p_LogLevel, p_Path, p_Pointer, p_Length) _logPrintBin(p_LogLevel, PT_File, p_Path, 0, p_Pointer, p_Length)

#ifdef __cplusplus
}

// TODO: C++ stream bindings here

#endif

#endif
