AMOT
====

advanced memory operation tech

You can use AMOT to improve your C/C++ application performance.

"wanna run bloody fast"

The following data is from a simple test:

*Allocate/Free*  
`AMOT GP` 153.658(ms)  
`CRT` 5724.77(ms)  
**FASTER: 3725%**

`AMOT FL` 82.6153(ms)  
`CRT` 16785.7(ms)  
**FASTER: 20317%**

*ctor/dtor*  
`AMOT GP` 3.52484(ms)  
`CRT` 70.2803(ms)  
**FASTER: 1993%**

*Resize*  
`AMOT GP` 6.70616(ms)  
`CRT` 1310.64(ms)  
**FASTER: 19543%**

**Test data is NOT always like this, performance is relative to real code.**  
**However, in most cases AMOT works well.**