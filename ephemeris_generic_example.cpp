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

#pragma comment(lib, "../libs/cspice/lib/cspice.lib")

extern "C" {
	#include "../libs/cspice/include/SpiceCK.h" // must be before SpiceZdf.h and SpiceZpr.h
	#include "../libs/cspice/include/SpiceZdf.h"
	#include "../libs/cspice/include/SpiceZpr.h"
}

/*
	3. Download required ephemeris data file, such as "de430t.bsp"
	from ftp://ssd.jpl.nasa.gov/pub/eph/planets/bsp
*/

int main()
{
	/* 4. An example of ephemeris calculation with cspice and DE430.bsp */

	SpiceDouble   et_s;
	SpiceDouble   state[6];
	SpiceDouble   lt_s;

	furnsh_c("naif0012.tls");	//	leapseconds kernel, https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/
	furnsh_c("de430.bsp");	// planetary ephemeris SPK file, https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/

	str2et_c("2020 March 15 00:00", &et_s); // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/str2et_c.html
	spkezr_c("MOON",// target body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
		et_s,		// s, seconds past J2000 epoch, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/time.html
		"J2000",	// reference frame, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
		"NONE",		
		"EARTH",	// observer body name or NAIF ID, https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
		state,		// output parameter, body state, wich is [X km, Y km, Z km, Vx km/s, Vy km/s, Vz km/s]
		&lt_s);		// s, the one-way light time between the observer and target

	std::cout << "X = " << state[0] << " km" << std::endl
		<< "Y = " << state[1] << " km" << std::endl
		<< "Z = " << state[2] << " km" << std::endl
		<< "Vx = " << state[3] << " km/s" << std::endl
		<< "Vy = " << state[4] << " km/s" << std::endl
		<< "Vz = " << state[5] << " km/s" << std::endl;

	/* to check values use online JPL HORIZONS system https://ssd.jpl.nasa.gov/horizons.cgi */

	std::system("pause");
	return 0;
}