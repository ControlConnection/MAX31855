MAX31855 Arduino Library
========================

This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/">Creative Commons Attribution-ShareAlike 3.0 Unported License</a>.

	<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/88x31.png" /></a>
	
Developed By:

*   Alec N., Control Connection
*	Ryan McLaughlin <ryan@ryanjmclaughlin.com>


Summary
-------

The primary use of the library is to easily interface with a MAX31855 chip via the SPI interface.  Use the following code to initialize the library.

	MAX31855 temp(SCK,SO,CS);
	
Variables:	

*	CS is chip select pin of chip
*	SO is data out of the chip
*	SCK is the clock pin of the chip

Functions
---------

### readMAX31855
### readCelsius
### readFarenheit
### readCJC
### readFaultCode
