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
	#include "../libs/cspice/include/SpiceCK.h" // must be before 
	#include "../libs/cspice/include/SpiceZdf.h"
	#include "../libs/cspice/include/SpiceZpr.h"
}

/*
	3. Download required ephemeris data file, such as "de430t.bsp"
	from ftp://ssd.jpl.nasa.gov/pub/eph/planets/bsp
*/

int main()
{
	/* an example of ephemeris calculation with cspice and DE430.bsp */
	SpiceDouble   et;
	SpiceDouble   state[6];
	SpiceDouble   lt;

	furnsh_c("naif0008.tls");
	furnsh_c("de430t.bsp");
	furnsh_c("mgs_ext22.bsp");

	str2et_c("2006 JAN 31 01:00", &et);
	spkezr_c("MGS", et, "J2000", "NONE", "MARS", state, &lt);

	return 0;
}