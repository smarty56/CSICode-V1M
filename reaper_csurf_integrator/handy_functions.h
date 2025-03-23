//
//  handy_reaper_functions.h
//  reaper_csurf_integrator
//
//

#ifndef handy_functions_h
#define handy_functions_h

#include "../WDL/db2val.h"

static double int14ToNormalized(unsigned char msb, unsigned char lsb)
{
    int val = lsb | (msb<<7);
    double normalizedVal = val/16383.0;
    
    normalizedVal = normalizedVal < 0.0 ? 0.0 : normalizedVal;
    normalizedVal = normalizedVal > 1.0 ? 1.0 : normalizedVal;
    
    return normalizedVal;
}

static double normalizedToVol(double val)
{
    double pos=val*1000.0;
    pos=SLIDER2DB(pos);
    return DB2VAL(pos);
}

static double volToNormalized(double vol)
{
    double d=(DB2SLIDER(VAL2DB(vol))/1000.0);
    if (d<0.0)d=0.0;
    else if (d>1.0)d=1.0;
    
    return d;
}

static double normalizedToPan(double val)
{
    return 2.0 * val - 1.0;
}

static double panToNormalized(double val)
{
    return 0.5 * (val + 1.0);
}

static void WindowsDebugOutput(const char * format, ...)
{
    #if defined (_WIN32) && defined (_DEBUG)  
        char buffer             [2056];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);
        OutputDebugString(buffer);
    #endif
}
#endif /* handy_functions_h */
