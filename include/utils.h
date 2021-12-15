#include "libjbc.h"

extern jbc_cred g_Cred;
extern jbc_cred g_RootCreds;

bool is_jailbroken();
void jailbreak();
void unjailbreak();

uint16_t get_firmware();
uint64_t get_xfast();
