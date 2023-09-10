/*	
	1. Be adviced, that several settings are changed
	in the project:
		1.1) "C/C++" ==> "Code Generation" ==> "Spectre Mitigation" is set to "Disabled"
*/

#include <iostream>

/*
	2. Be adviced, that use of cspice.lib from arhive from https://naif.jpl.nasa.gov/naif/toolkit_C.html
	leads to multiple link errors (at least in March, 2020), such are
	- error LNK2001: unresolved external symbol fprintf
	- error LNK2001: unresolved external symbol sprintf
	- error LNK2001: unresolved external symbol __iob_func ... etc.
	You must rebuild cspice.lib from source with your current version of Visual Studio
	as adviced in https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-change-history-2003-2015?redirectedfrom=MSDN&view=vs-2019#stdio_and_conio
	
	To rebuild cspice.lib
	- start "Native tools x64 for VS2017" or higher form system all programs menu.
	- within "Native tools ..." console go to cspice directory with CD command.
	- enter makeall.bat command, which will rebuild all cspice binaries, includes cspice.lib,
	- or alternatively enter "cd src&&cd cspice&&call mkprodct.bat" command to fast build cspice.lib only.
*/

// #pragma comment(lib, "../libs/cspice/lib/cspice.lib")

//extern "C" { // old version, Visual Studio build system
//	#include "../libs/cspice/include/SpiceCK.h" // must be before SpiceZdf.h and SpiceZpr.h
//	#include "../libs/cspice/include/SpiceZdf.h"
//	#include "../libs/cspice/include/SpiceZpr.h"
//}

// new CMake build system
extern "C" {
    #include <SpiceCK.h>
    #include <SpiceUsr.h>
    #include <SpiceZdf.h>
    #include <SpiceZpr.h>
}

// old version, Visual Studio build system
//#include "../libs/ephemeris-access/libephaccess/ephaccess.h" // https://gitlab.iaaras.ru/iaaras/ephemeris-access

// new CMake build system
#include <ephaccess.h>

/*
	3. Download required ephemeris data file, such as "de430t.bsp"
	from ftp://ssd.jpl.nasa.gov/pub/eph/planets/bsp
*/

//typedef struct
//{
//	double jd0, jd1;	// julian dates
//	double interval_days;
//	double step_days;	// days
//	int width;
//	int positions_only;
//} EphConfig;

//void init_eph_config(EphConfig *config)
//{
//	memset(config, 0, sizeof(EphConfig));
//	config->width = 20;
//	config->step_days = 1.0;
//}


int main()
{
    /* Example of CSPICE ephemeris calculation with NASA JPL DE4xx ephemeris by DE430.bsp data file*/
    std::cout << "NASA JPL NAIF CSPICE calculated ephemeris" << std::endl;
    furnsh_c("naif0012.tls"); //	leapseconds kernel, https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/
    furnsh_c("de440.bsp"); // planetary ephemeris SPK file, https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/


    SpiceDouble   et_s;
    str2et_c("2023 Jan 01 00:00", &et_s); // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/str2et_c.html
    SpiceDouble   state[6] = {0.0};
    SpiceDouble   lt_s;
    spkezr_c("MOON",    // target body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
             et_s,      // s, seconds past J2000 epoch, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/time.html
             "J2000",   // reference frame, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
             "NONE",
             "EARTH",   // observer body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
             state,     // output parameter, body state, wich is [X km, Y km, Z km, Vx km/s, Vy km/s, Vz km/s]
             &lt_s);    // s, the one-way light time between the observer and target

    std::cout
        << "X = " << state[0] << " km" << std::endl
		<< "Y = " << state[1] << " km" << std::endl
		<< "Z = " << state[2] << " km" << std::endl
		<< "Vx = " << state[3] << " km/s" << std::endl
		<< "Vy = " << state[4] << " km/s" << std::endl
        << "Vz = " << state[5] << " km/s" << std::endl << std::endl;


    /* to check JPL ephemeris values, use online JPL HORIZONS system
     * https://ssd.jpl.nasa.gov/horizons/app.html */

    /* Example of IAA RAS EPM 2017 ephemeris calculation
     * https://gitlab.iaaras.ru/iaaras/ephemeris-access */

    /* data files are loaded from https://ftp.iaaras.ru/pub/epm/<CHOOSE_VERSION >    */
    std::cout << "IAA RAS libephaccess calculated ephemeris" << std::endl;
    int result = 0;
	EphAccess *eph = ephCreate();
    if (eph == NULL){
        std::cout << "ephCreate() error: " << ephLastError(eph) << std::endl;
        return -1;
    }

    result = ephLoadFile(eph, "epm2021.bsp" );
    if(result < 0){
        std::cout << "ephLoadFile() error: " << ephLastError(eph) << std::endl;
        return result;
    }
    ephSetDistanceUnits(eph, EPH_KM); // EPH_AU
    ephSetTimeUnits(eph, EPH_SEC); // EPH_DAY

    // target_object = Moonlibr | Earth | Moon | EMB | Sun | Venus |  Mars_bc | Jupiter_bc | ...
    char target_object[] = "Moon";
    int id_object = ephObjectByName(target_object);
    if(id_object == -1){
        std::cout << "ephObjectByName(\"Moon\") error: "
                  << ephLastError(eph) << std::endl;
        return id_object;
    }

    // reference_object = EMB | Earth | Sun | SSB | ...
    char reference_object[] = "Earth";
    int id_reference = ephObjectByName(reference_object);
    if(id_reference == -1){
        std::cout << "ephObjectByName(\"Earth\") error: "
                  << ephLastError(eph) << std::endl;
        return id_reference;
    }

    double jd0 = 2459945.0; // JD 2459945.5 = 2023-Jan-01 00:00:00.0 TDB
    double jd1 = 0.5;
    double posvel[6] = {0.0};
    bool positions_only = false;

    result = ephCalculateRectangular(
        eph,
        id_object,
        id_reference,
        jd0,
        jd1,
        posvel,
        positions_only ? NULL : posvel + 3);
    if(result !=0){
        std::cout << "ephCalculateRectangular() error: "
                  << ephLastError(eph) << std::endl;
        return result;
    }
    ephDestroy(eph);

    std::cout
        << "X = " << posvel[0] << " km" << std::endl
        << "Y = " << posvel[1] << " km" << std::endl
        << "Z = " << posvel[2] << " km" << std::endl
        << "Vx = " << posvel[3] << " km/s" << std::endl
        << "Vy = " << posvel[4] << " km/s" << std::endl
        << "Vz = " << posvel[5] << " km/s" << std::endl;
	/* to check IAA RAS EPM 2xxx ephemeride values, use online http://iaaras.ru/en/dept/ephemeris/online/ */

	/* 6. An examp CALCEPH toolkit use https://www.imcce.fr/fr/presentation/equipes/ASD/inpop/calceph/ */


	std::system("pause");
	return 0;
}
