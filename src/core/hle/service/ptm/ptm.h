// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "core/hle/ipc_helpers.h"

namespace Service {

class Interface;

namespace PTM {

/// Charge levels used by PTM functions
enum class ChargeLevels : u32 {
    CriticalBattery = 1,
    LowBattery = 2,
    HalfFull = 3,
    MostlyFull = 4,
    CompletelyFull = 5,
};

/**
 * Represents the gamecoin file structure in the SharedExtData archive
 * More information in 3dbrew
 * (http://www.3dbrew.org/wiki/Extdata#Shared_Extdata_0xf000000b_gamecoin.dat)
 */
struct GameCoin {
    u32 magic;               ///< Magic number: 0x4F00
    u16 total_coins;         ///< Total Play Coins
    u16 total_coins_on_date; ///< Total Play Coins obtained on the date stored below.
    u32 step_count;          ///< Total step count at the time a new Play Coin was obtained.
    u32 last_step_count;     ///< Step count for the day the last Play Coin was obtained
    u16 year;
    u8 month;
    u8 day;
};

/**
 * It is unknown if GetAdapterState is the same as GetBatteryChargeState,
 * it is likely to just be a duplicate function of GetBatteryChargeState
 * that controls another part of the HW.
 * PTM::GetAdapterState service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Output of function, 0 = not charging, 1 = charging.
 */
void GetAdapterState(Interface* self);

/**
 * PTM::GetShellState service function.
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Whether the 3DS's physical shell casing is open (1) or closed (0)
 */
void GetShellState(Interface* self);

/**
 * PTM::GetBatteryLevel service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Battery level, 5 = completely full battery, 4 = mostly full battery,
 *          3 = half full battery, 2 =  low battery, 1 = critical battery.
 */
void GetBatteryLevel(Interface* self);

/**
 * PTM::GetBatteryChargeState service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Output of function, 0 = not charging, 1 = charging.
 */
void GetBatteryChargeState(Interface* self);

/**
 * PTM::GetPedometerState service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Output of function, 0 = not counting steps, 1 = counting steps.
 */
void GetPedometerState(Interface* self);

/**
 * PTM::GetStepHistory service function
 *  Inputs:
 *      1 : Number of hours
 *    2-3 : Start time
 *      4 : Buffer mapping descriptor
 *      5 : (short*) Buffer for step counts
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 */
void GetStepHistory(Interface* self);

/**
 * PTM::GetTotalStepCount service function
 *  Outputs:
 *      1 : Result of function, 0 on success, otherwise error code
 *      2 : Output of function, * = total step count
 */
void GetTotalStepCount(Interface* self);

/**
 * PTM::GetSoftwareClosedFlag service function
 *  Outputs:
 *      1: Result code, 0 on success, otherwise error code
 *      2: Whether or not the "software closed" dialog was requested by the last FIRM
 *         and should be displayed.
 */
void GetSoftwareClosedFlag(Interface* self);

/**
 * PTM::CheckNew3DS service function
 *  Inputs:
 *      0 : Header code [0x040A0000]
 *  Outputs:
 *      0 : Header code
 *      1: Result code, 0 on success, otherwise error code
 *      2: u8 output: 0 = Old3DS, 1 = New3DS.
 */
void CheckNew3DS(Interface* self);
void CheckNew3DS(IPC::RequestBuilder& rb);

/*
 * PTM::ConfigureNew3DSCPU service function
 * Inputs:
 *      0 : Header code [0x08180040]
 *      1 : u8 value, only bit0-1 are used here.
 *          Bit 0 enables higher core clock, and bit 1 enables additional (L2) cache.
 * Outputs:
 *      0 : Header code
 *      1 : Result code
 * Note:
 *     This just uses svcKernelSetState with Type10 where Param0=<input u8 value from the cmd>.
 *     This command is implemented in the Old3DS PTM sysmodule too,
 *     but the above type is only implemented in the New3DS ARM11-kernel.
 */
void ConfigureNew3DSCPU(Interface* self);

/// Initialize the PTM service
void Init();

/// Shutdown the PTM service
void Shutdown();

} // namespace PTM
} // namespace Service
