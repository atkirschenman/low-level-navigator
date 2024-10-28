#pragma once


namespace nav_define
{
    enum class Nav_state
    {
        NS_STARTUP,
        NS_PRECALIBRATION,
        NS_CALIBRATION,
        NS_IDLE_NAV,
        NS_NAVIGATION_ACTIVE
    };
}