#ifndef _UNDOCUMENTED_H
#define _UNDOCUMENTED_H

#include <windows.h>

// Source: https://github.com/x64dbg/TitanEngine/blob/x64dbg/TitanEngine/ntdll.h

#define PROCESSOR_FEATURE_MAX       64

typedef struct _KSYSTEM_TIME
{
    DWORD LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME;

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE
{
    StandardDesign,
    NEC98x86,
    EndAlternatives
} ALTERNATIVE_ARCHITECTURE_TYPE;

#pragma pack(push, 4)
typedef struct _KUSER_SHARED_DATA
{
    ULONG TickCountLowDeprecated;
    ULONG TickCountMultiplier;

    volatile KSYSTEM_TIME InterruptTime;
    volatile KSYSTEM_TIME SystemTime;
    volatile KSYSTEM_TIME TimeZoneBias;

    USHORT ImageNumberLow;
    USHORT ImageNumberHigh;

    WCHAR NtSystemRoot[260];

    ULONG MaxStackTraceDepth;

    ULONG CryptoExponent;

    ULONG TimeZoneId;
    ULONG LargePageMinimum;
    ULONG AitSamplingValue;
    ULONG AppCompatFlag;
    ULONGLONG RNGSeedVersion;
    ULONG GlobalValidationRunlevel;
    LONG TimeZoneBiasStamp;

    ULONG NtBuildNumber;
    ULONG NtProductType;
    BOOLEAN ProductTypeIsValid;
    UCHAR Reserved0[1];
    USHORT NativeProcessorArchitecture;

    ULONG NtMajorVersion;
    ULONG NtMinorVersion;

    BOOLEAN ProcessorFeatures[PROCESSOR_FEATURE_MAX];

    ULONG Reserved1;
    ULONG Reserved3;

    volatile ULONG TimeSlip;

    ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
    ULONG BootId;

    LARGE_INTEGER SystemExpirationDate;

    ULONG SuiteMask;

    BOOLEAN KdDebuggerEnabled;
    union
    {
        UCHAR MitigationPolicies;
        struct
        {
            UCHAR NXSupportPolicy : 2;
            UCHAR SEHValidationPolicy : 2;
            UCHAR CurDirDevicesSkippedForDlls : 2;
            UCHAR Reserved : 2;
        } s1;
    } u1;
    UCHAR Reserved6[2];

    volatile ULONG ActiveConsoleId;

    volatile ULONG DismountCount;

    ULONG ComPlusPackage;

    ULONG LastSystemRITEventTickCount;

    ULONG NumberOfPhysicalPages;

    BOOLEAN SafeBootMode;
    UCHAR VirtualizationFlags;
    UCHAR Reserved12[2];

    union
    {
        ULONG SharedDataFlags;
        struct
        {
            ULONG DbgErrorPortPresent : 1;
            ULONG DbgElevationEnabled : 1;
            ULONG DbgVirtEnabled : 1;
            ULONG DbgInstallerDetectEnabled : 1;
            ULONG DbgLkgEnabled : 1;
            ULONG DbgDynProcessorEnabled : 1;
            ULONG DbgConsoleBrokerEnabled : 1;
            ULONG DbgSecureBootEnabled : 1;
            ULONG DbgMultiSessionSku : 1;
            ULONG DbgMultiUsersInSessionSku : 1;
            ULONG SpareBits : 22;
        } s2;
    } u2;
    ULONG DataFlagsPad[1];

    ULONGLONG TestRetInstruction;
    LONGLONG QpcFrequency;
    ULONG SystemCall;
    ULONG SystemCallPad0;
    ULONGLONG SystemCallPad[2];

    union
    {
        volatile KSYSTEM_TIME TickCount;
        volatile ULONG64 TickCountQuad;
        ULONG ReservedTickCountOverlay[3];
    };
    ULONG TickCountPad[1];

    ULONG Cookie;
    ULONG CookiePad[1];

    LONGLONG ConsoleSessionForegroundProcessId;
    ULONGLONG TimeUpdateLock;
    ULONGLONG BaselineSystemTimeQpc;
    ULONGLONG BaselineInterruptTimeQpc;
    ULONGLONG QpcSystemTimeIncrement;
    ULONGLONG QpcInterruptTimeIncrement;
    UCHAR QpcSystemTimeIncrementShift;
    UCHAR QpcInterruptTimeIncrementShift;

    USHORT UnparkedProcessorCount;
    ULONG EnclaveFeatureMask[4];
    ULONG Reserved8;
    USHORT UserModeGlobalLogger[16];
    ULONG ImageFileExecutionOptions;

    ULONG LangGenerationCount;
    ULONGLONG Reserved4;
    volatile ULONG64 InterruptTimeBias;
    volatile ULONG64 QpcBias;

    ULONG ActiveProcessorCount;
    volatile UCHAR ActiveGroupCount;
    UCHAR Reserved9;
    union
    {
        USHORT QpcData;
        struct
        {
            UCHAR QpcBypassEnabled : 1;
            UCHAR QpcShift : 1;
        } s3;
    } u3;

    LARGE_INTEGER TimeZoneBiasEffectiveStart;
    LARGE_INTEGER TimeZoneBiasEffectiveEnd;
    XSTATE_CONFIGURATION XState;
} KUSER_SHARED_DATA, * PKUSER_SHARED_DATA;

typedef KUSER_SHARED_DATA KUSD;

#pragma pack(pop)

// http://stackoverflow.com/questions/36961152/detect-windows-kit-8-0-and-windows-kit-8-1-sdks
#if defined(WINAPI_PARTITION_APP)
#if (WINAPI_PARTITION_APP == 0x00000002)
#define USING_WINDOWS_8_0_SDK
#define USING_WINDOWS_8_x_SDK
#endif
#if defined(WINAPI_FAMILY_SYSTEM)
#define USING_WINDOWS_10_SDK
#else
#if (WINAPI_PARTITION_APP == 1)
#define USING_WINDOWS_8_1_SDK
#define USING_WINDOWS_8_x_SDK
#endif
#endif
#endif

// This struct was included in winnt.h starting in the windows 8 toolkit
#if !(defined(USING_WINDOWS_8_x_SDK) || defined(USING_WINDOWS_10_SDK))
typedef struct _EXCEPTION_REGISTRATION_RECORD
{
    _EXCEPTION_REGISTRATION_RECORD* Next;
    _EXCEPTION_DISPOSITION Handler;
} EXCEPTION_REGISTRATION_RECORD, *PEXCEPTION_REGISTRATION_RECORD;
#endif

#endif // _UNDOCUMENTED_H