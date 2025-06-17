#include "plugin.h"
#include "undocumented.h"

void* GetKUSDLocation()
{
#ifdef _WIN64
    return (void*)0x7FFE0000ULL;
#else
    return (void*)0x7FFE0000UL;
#endif
}

template<size_t Size>
static bool getLabelKUSD(duint addr, char(&label)[Size])
{
    const duint kusd = (duint)GetKUSDLocation();
    const duint size = DbgMemGetPageSize(kusd); // Arbitrary page size to keep within known range

    if (addr >= kusd && addr < kusd + size)
    {
        duint offset = addr - kusd;
        bool match = false;

#define CASE(member) \
    if (offset == offsetof(KUSD, member)) { \
        strcpy_s(label, Size, "KUSER_SHARED_DATA." #member); \
        match = true; \
    } else
#include "kusdcases.h"
#undef CASE

        return match;
    }

    return false;
}

//called from CBVALFROMSTRING
static bool valkusdtostring(const char* name, duint* value, int* value_size, bool* isvar)
{
#define CASE(member) if(_stricmp(name, "KUSER_SHARED_DATA." #member) == 0) { *value = offsetof(KUSD, member); } else
#include "kusdcases.h"
#undef CASE
    *value += (duint)GetKUSDLocation();
    if (value_size)
        *value_size = sizeof(duint);
    if (isvar)
        *isvar = true;
    return true;
}

//called from CBVALTOSTRING
static bool valkusdtostring(const char* name, duint value)
{
#define CASE(member) if(_stricmp(name, "KUSER_SHARED_DATA." #member) == 0) { value = offsetof(KUSD, member); } else
#include "kusdcases.h"
#undef CASE
    value += (duint)GetKUSDLocation();
    return true;
}

PLUG_EXPORT void CBADDRINFO(CBTYPE cbType, PLUG_CB_ADDRINFO* info)
{
    if (!info->retval && (info->addrinfo->flags & flaglabel))
        info->retval = getLabelKUSD(info->addr, info->addrinfo->label);
}

PLUG_EXPORT void CBVALFROMSTRING(CBTYPE cbType, PLUG_CB_VALFROMSTRING* info)
{
    if (!info->retval)
        info->retval = valkusdtostring(info->string, &info->value, info->value_size, info->isvar);
}

PLUG_EXPORT void CBVALTOSTRING(CBTYPE cbType, PLUG_CB_VALTOSTRING* info)
{
    if (!info->retval)
        info->retval = valkusdtostring(info->string, info->value);
}

bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    return true;
}

bool pluginStop()
{
    return true;
}

void pluginSetup()
{
}
