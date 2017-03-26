#ifndef DBALLPORTS
#define DBALLPORTS

#define DB 0xFFFF0000

/* SIM - System Integration Module */
#define SCR       0xF000 /* System Control Register */

/* CS - Chip Select */
#define GRPBASEA  0xF100 /* Chip Select Group A Base Register */
#define GRPBASEC  0xF104 /* Chip Select Group C Base Register */
#define GRPMASKC  0xF10C /* Chip Select Group C Mask Register */
#define CSAx      0xF110 /* Group A Chip Select x Register */
#define CSGBB	  0xF102 //16
#define CSGBD	  0xF106 //16
#define CSCR	  0xF10A //16
#define CSA		  0xF110 //16
#define CSB		  0xF112 //16
#define CSC		  0xF114 //16
#define CSD		  0xF116 //16

/* PLL - Phase Locked Loop */
#define PLLCR     0xF200 /* PLL Control Register */
#define PLLFSR    0xF202 /* PLL Frequency Select Register */
#define PCTLR     0xF207 /* Power Control Register */

/* INTR - Interrupt controller */
#define IVR       0xF300 /* Interrupt Vector Register */
#define ICR       0xF302 /* Interrupt Control Register */
#define IMR       0xF304 /* Interrupt Mask Register */
#define IWR       0xF308 /* Interrupt Wakeup Enable Register */
#define ISR       0xF30C /* Interrupt Status Register */
#define IPR       0xF310 /* Interrupt Pending Register */

/* PIO - Parallel IO */
#define PBDIR	  0xF408 //8
#define PBDATA	  0xF409 //8
#define PBSEL	  0xF40B //8
#define PBPUEN	  0xF40A //8
#define PCDIR     0xF410 /* Port C Direction Register */
#define PCDATA    0xF411 /* Port C Data Register */
#define PCPDEN	  0xF412 //8
#define PCSEL     0xF413 /* Port C Select Register */
#define PDDIR     0xF418 /* Port D Direction Register */
#define PDDATA    0xF419 /* Port D Data Register */
#define PDPUEN    0xF41A /* Port D Pullup Enable Register */
#define PDPOL     0xF41C /* Port D Polarity Register */
#define PDIRQEN   0xF41D /* Port D IRQ Enable Register */
#define PDIRQEDGE 0xF41F /* Port D IRQ Edge Register */
#define PDSEL	  0xF41B //8
#define PDKBEN	  0xF41E //8
#define PEDIR     0xF420 /* Port E Direction Register */
#define PEDATA    0xF421 /* Port E Data Register */
#define PEPUEN    0xF422 /* Port E Pullup Enable Register */
#define PESEL     0xF423 /* Port E Select Register */
#define PFDIR     0xF428 /* Port F Direction Register */
#define PFDATA    0xF429 /* Port F Data Register */
#define PFPUEN    0xF42A /* Port F Pullup Enable Register */
#define PFSEL     0xF42B /* Port F Select Register */
#define PGDIR     0xF430 /* Port G Direction Register */
#define PGDATA    0xF431 /* Port G Data Register */
#define PGPUEN    0xF432 /* Port G Pullup Enable Register */
#define PGSEL     0xF433 /* Port G Select Register */
#define PJDIR     0xF438 /* Port J Direction Register */
#define PJDATA    0xF439 /* Port J Data Register */
#define PJSEL     0xF43B /* Port J Select Register */
#define PJPUEN	  0xF43A //8
#define PKDIR     0xF440 /* Port K Direction Register */
#define PKDATA    0xF441 /* Port K Data Register */
#define PKPUEN    0xF442 /* Port K Pullup Enable Register */
#define PKSEL     0xF443 /* Port K Select Register */
#define PMDIR     0xF448 /* Port M Direction Register */
#define PMDATA    0xF449 /* Port M Data Register */
#define PMPUEN    0xF44A /* Port M Pullup Enable Register */
#define PMSEL     0xF44B /* Port M Select Register */

//audio
#define PWMC1 0xF500 //16
#define PWMS1 0xF502 //16
#define PWMP1 0xF504 //8

/* Timer */
#define TCTL1     0xF600 /* Timer Unit 1 Control Register */
#define TPRER1    0xF602 /* Timer Unit 1 Prescaler Register */
#define TCMP1     0xF604 /* Timer Unit 1 Compare Register */
#define TCN1      0xF608 /* Timer Unit 1 Counter */
#define TSTAT1    0xF60A /* Timer Unit 1 Status Register */
#define TCTL2     0xF610 /* Timer Unit 2 Control Register */


/* SPIM - Serial Peripheral Interface Master */
#define SPIMDATA  0xF800 /* SPIM Data Register */
#define SPIMCONT  0xF802 /* SPIM Control/Status Register */

/* UART - Universal Asynchronous Receiver/Transmitter */
#define USTCNT    0xF900 /* UART Status/Control Register */
#define UBAUD     0xF902 /* UART Baud Control Register */
#define URX       0xF904 /* UART RX Register */
#define UTX       0xF906 /* UART TX Register */
#define UMISC     0xF908 /* UART Misc Register */

/* LCDC - LCD Controller */
#define LSSA      0xFA00 /* Screen Starting Address Register */
#define LVPW      0xFA05 /* Virtual Page Width Register */
#define LXMAX     0xFA08 /* Screen Width Register */
#define LYMAX     0xFA0A /* Screen Height Register */
#define LCXP      0xFA18 /* Cursor X Position */
#define LCYP      0xFA1A /* Cursor Y Position */
#define LCWCH     0xFA1C /* Cursor Width & Height Register */
#define LBLKC     0xFA1F /* Blink Control Register */
#define LPICF     0xFA20 /* Panel Interface Config Register */
#define LPXCD     0xFA25 /* Pixel Clock Divider Register */
#define LCKCON    0xFA27 /* Clocking Control Register */
#define LPOSR     0xFA2D /* Panning Offset Register */
#define LFRCM     0xFA31 /* Frame Rate Control Modulation Register */
#define LGPMR     0xFA32 /* Gray Palette Mapping Register */

/* RTC - Real Time Clock */
#define RTCHMS    0xFB00 /* RTC Hours Minutes Seconds Register */
#define RTCALARM  0xFB04 /* RTC Alarm Register */
#define WATCHDOG  0xFB0A //16 bits
#define RTCCTL    0xFB0C /* RTC Control Register */
#define RTCISR    0xFB0E /* RTC Interrupt Status Register */
#define RTCIENR   0xFB10 /* RTC Interrupt Enable Register */
#define RTCMSW    0xFB12 /* RTC Minute Stopwatch */
#define RTCDAYS	  0xFB1A

//68VZ328 registers
//name/number/size
#define DRAMMC 0xFC00 //16
#define DRAMC 0xFC02 //16
#define SDCTRL 0xFC04 //16

//emuirq incircuit debugger
#define ICEMCR 0xFD0C
#define ICEMSR 0xFD0E

//address 0x10800000 has something todo with irq3


//68vz328 bootloader stuff
#define BOOTLOADER(x) ((x)>=0xFFFFFE00)

//interrupt bit nums
#define UARTINT 2
#define PENINT 20
#define WATCHDOGINT 3
#define TMR1INT 1
#define TMR2INT 5
#define RTCINT 0

#endif // DBALLVZ

