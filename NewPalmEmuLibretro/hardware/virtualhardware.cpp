//taken from xcopilot

#include "m68k.h"
#include "minifunc.h"
#include "memmap.h"
#include "newcpu.h"
#include "dballvz.h"
#include "virtualhardware.h"

shared_img* CustShptr = nullptr;
unsigned long specialflags;

/* dragonball register definitions */

union {
	UBYTE x;
	struct {
		unsigned WDTH8	:1;
		unsigned RSVD	:1;
		unsigned DMAP	:1;
		unsigned SO		:1;
		unsigned BETEN	:1;
		unsigned PRV	:1;
		unsigned WPV	:1;
		unsigned BETO	:1;
	} anon;
} db_SCR;

union {
	UWORD x;
	struct {
		unsigned V	:1;
		unsigned 	:3;
		unsigned GMA	:12;
	} anon;
} db_GRPBASEA, db_GRPBASEC;

union {
	UWORD x;
	struct {
		unsigned 	:4;
		unsigned GMA	:12;
	} anon;
}db_GRPMASKC;

union {
	UBYTE x;
	struct {
		unsigned WIDTH	:5;
		unsigned 	:1;
		unsigned STOP	:1;
		unsigned PCEN	:1;
	} anon;
} db_PCTLR;

union {
	UBYTE x;
	struct {
		unsigned LEVEL	:3;
		unsigned VECTOR	:5;
	} anon;
} db_IVR;

union {
	UWORD x;
	struct {
		unsigned 	:8;
		unsigned POL6	:1;
		unsigned POL3	:1;
		unsigned POL2	:1;
		unsigned POL1	:1;
		unsigned ET6	:1;
		unsigned ET3	:1;
		unsigned ET2	:1;
		unsigned ET1	:1;
	} anon;
} db_ICR;

union {
	ULONG x;
	struct {
	  unsigned SPIM	:1;
	  unsigned TMR1	:1;
	  unsigned UART	:1;
	  unsigned WDT	:1;
	  unsigned RTC	:1;
	  unsigned TMR2	:1;
	  unsigned KB	:1;
	  unsigned PWM	:1;
	  unsigned INT0	:1;//keyboard column 0
	  unsigned INT1	:1;//keyboard column 1
	  unsigned INT2	:1;//keyboard column 2
	  unsigned INT3	:1;//keyboard column 3
	  unsigned INT4	:1;//uart2
	  unsigned INT5	:1;//pwm2
	  unsigned INT6	:1;//notused
	  unsigned INT7	:1;//notused
	  unsigned IRQ1	:1;//hotsync button irq
	  unsigned IRQ2	:1;//Radio Ring Indicate (no idea what that is)
	  unsigned IRQ3	:1;//usb irq
	  unsigned IRQ6	:1;//power fail irq
	  unsigned PEN	:1;//irq5 is bit name but it is used for pen
	  unsigned SPIS	:1;
	  unsigned RTI	:1;//mrti
	  unsigned IRQ7	:1;//emuirq used for cpu level debugging
		unsigned 	:8;
	} anon;
} db_IMR, db_IWR, db_ISR, db_IPR;

//audio pwm
union {
	UWORD x;
	struct {
		unsigned CLKSEL	:3;
		unsigned 	:1;
		unsigned PWMEN	:1;
		unsigned POL	:1;
		unsigned 	:1;
		unsigned PIN	:1;
		unsigned LOAD	:1;
		unsigned 	:5;
		unsigned IRQEN	:1;
		unsigned PWMIRQ	:1;
	} anon;
} db_PWMC;

union {
	UWORD x;
	struct {
		unsigned PERIOD	:16;
	} anon;
} db_PWMP;

union {
	UWORD x;
	struct {
		unsigned WIDTH	:16;
	} anon;
} db_PWMW;

union {
	ULONG x;
	struct {
		unsigned SSA	:32;
	} anon;
} db_LSSA;

union {
	UBYTE x;
	struct {
		unsigned VPW	:8;
	} anon;
} db_LVPW;

union {
	UWORD x;
	struct {
		unsigned XMAX	:10;
		unsigned 	:6;
	} anon;
} db_LXMAX;

union {
	UWORD x;
	struct {
		unsigned YMAX	:10;
		unsigned 	:6;
	} anon;
} db_LYMAX;

union {
	UWORD x;
	struct {
		unsigned CXP	:10;
		unsigned 	:4;
		unsigned CC	:2;
	} anon;
} db_LCXP;

union {
	UWORD x;
	struct {
		unsigned CYP	:10;
		unsigned 	:6;
	} anon;
} db_LCYP;

union {
	UWORD x;
	struct {
		unsigned CH	:5;
		unsigned 	:3;
		unsigned CW	:5;
		unsigned 	:3;
	} anon;
} db_LCWCH;

union {
	UBYTE x;
	struct {
		unsigned BD	:7;
		unsigned BKEN	:1;
	} anon;
} db_LBLKC;

union {
	UBYTE x;
	struct {
		unsigned GS	:1;
		unsigned PBSIZ	:2;
		unsigned 	:5;
	} anon;
} db_LPICF;

union {
	UBYTE x;
	struct {
		unsigned PCD	:6;
		unsigned 	:2;
	} anon;
} db_LPXCD;

union {
	UBYTE x;
	struct {
		unsigned PCDS	:1;
		unsigned DWIDTH	:1;
		unsigned WS	:4;
		unsigned DMA16	:1;
		unsigned LCDCON	:1;
	} anon;
} db_LCKCON;

union {
	UBYTE x;
	struct {
		unsigned POS	:3;
		unsigned BOS	:1;
		unsigned 	:4;
	} anon;
} db_LPOSR;

union {
	UBYTE x;
	struct {
		unsigned YMOD	:4;
		unsigned XMOD	:4;
	} anon;
} db_LFRCM;

union {
	UWORD x;
	struct {
		unsigned G2	:4;
		unsigned G3	:4;
		unsigned G0	:4;
		unsigned G1	:4;
	} anon;
} db_LGPMR;


//68VZ328 registers

//chip selects /provided for the processors comfort
UWORD db_CSGBB,db_CSGBD,db_CSCR,db_CSA,db_CSB,db_CSC,db_CSD;

//memory /provided for the processors comfort
UWORD db_DRAMMC,db_DRAMC,db_SDCTRL;

UBYTE db_PDKBEN,db_PDIRQEDGE,db_PDPOL,db_PDIRQEN;

enum{
	b,
	c,
	d,
	e,
	f,
	g,
	j,
	k,
	m
};

enum{
	pull,
	data,
	dir,
	sel
};

enum{
	up,
	down,
	none
};

typedef struct{
	 int pulltype;
	 UBYTE values[4];
}ports;

ports portX[9];

UBYTE getportdata(int dattype,int port){
	//reads port b,f,c,k,g, e,j,m for unknown reason
	//b sdram and usb chip select
	//f has pen interrupt
	//c is lcd something
	//k has chargeing and keyboard scaning
	//g rs232 usb and lcd
	//e spi
	//j serial port 2
	//m infrared uart2 and sdcard
	if(port == d && dattype == data){
		//fprintf(stderr,"Read PDDATA(buttons)\n");
		return 0x00;
	}
	//fprintf(stderr,"Read Port:%d\n",port);
	return portX[port].values[dattype];
}

void setportdata(UBYTE val,int dattype,int port){
	//if(port == d)fprintf(stderr,"Wrote PDDATA(buttons)\n");
	//fprintf(stderr,"Wrote Port:%d,Val:0x%02lx\n",port,val);
	portX[port].values[dattype] = val;
}

void portdefaults(){
	portX[b].pulltype = up;
	portX[b].values[pull] = 0xFF;

	portX[c].pulltype = down;
	portX[c].values[pull] = 0xFF;
	portX[c].values[dir] = 0x00;
	portX[c].values[sel] = 0xFF;
	portX[c].values[data] = 0x00;

	portX[d].pulltype = up;
	portX[d].values[dir] = 0x00;
	portX[d].values[pull] = 0xFF;
	portX[d].values[data] = 0xFF;
	portX[d].values[sel] = 0x00;//needs to be updataed

	portX[e].pulltype = up;
	portX[e].values[dir] = 0x00;
	portX[e].values[sel] = 0x87;
	portX[e].values[data] = 0xFF;
	portX[e].values[pull] = 0xFF;

	portX[f].pulltype = up;
	portX[f].values[dir] = 0x00;
	portX[f].values[pull] = 0xFF;
	portX[f].values[data] = 0xFF;
	portX[f].values[sel] = 0x87;

	portX[g].pulltype = up;
	portX[g].values[dir] = 0x00;
	portX[g].values[sel] = 0x08;
	portX[g].values[pull] = 0x3D;
	portX[g].values[data] = 0x3F;

	portX[j].pulltype = up;
	portX[j].values[pull] = 0xFF;
	portX[j].values[data] = 0xFF;
	portX[j].values[sel] = 0xEF;
	portX[j].values[dir] = 0x00;

	portX[k].pulltype = up;
	portX[k].values[data] = 0x0F;
	portX[k].values[pull] = 0xFF;
	portX[k].values[sel] = 0xFF;
	portX[k].values[dir] = 0x00;

	portX[m].pulltype = up;
	portX[m].values[pull] = 0x3F;
	portX[m].values[sel] = 0x3F;
	portX[m].values[data] = 0x20;
	portX[m].values[dir] = 0x00;

	db_PDPOL = 0x00;
	db_PDIRQEN = 0x00;
	db_PDIRQEDGE = 0x00;
	db_PDKBEN = 0x00;
}


static void db_reset(void){
	db_GRPBASEA.x = 0x0000;
	db_GRPBASEC.x = 0x0000;
	db_GRPMASKC.x = 0x0000;
	db_PCTLR.x = 0x1f;
	db_IVR.x = 0x00;
	db_ICR.x = 0x0000;
	db_IMR.x = 0x00ffffff;
	db_IWR.x = 0x00ffffff;
	db_ISR.x = 0x00000000;
	db_IPR.x = 0x00000000;

	//68VZ328 registers
	//chipselects /provided for the processors comfort
	db_CSGBB = 0x0000;
	db_CSGBD = 0x0000;
	db_CSCR = 0x0000;
	db_CSA = 0x00b0;
	db_CSB = 0x0000;
	db_CSC = 0x0000;
	db_CSD = 0x0200;
	//memory /provided for the processors comfort
	db_DRAMMC = 0x0000;
	db_DRAMC = 0x0000;
	db_SDCTRL = 0x003c;
	db_SCR.x = 0x1c;
	db_LXMAX.x = 0x03f0;
	db_LCKCON.x = 0x00;
	db_LFRCM.x = 0x00;

	db_LGPMR.x = 0x1073;//later

	db_PWMC.x = 0x0000;
	db_PWMP.x = 0x0000;
	db_PWMW.x = 0x0000;
	db_LSSA.x = 0x00000000;
	db_LVPW.x = 0xff;
	db_LYMAX.x = 0x01ff;
	db_LCXP.x = 0x0000;
	db_LCYP.x = 0x0000;
	db_LCWCH.x = 0x0101;
	db_LBLKC.x = 0x7f;
	db_LPICF.x = 0x00;
	db_LPXCD.x = 0x00;
	db_LPOSR.x = 0x00;
}

ULONG newinterrupt;
bool updateinterrupts;

void customreset(){
	specialflags = 0;
	newinterrupt = 0;
	updateinterrupts = false;
	/*
	db_reset();
	portdefaults();
	*/
}

//all hardware interupts are now triggered with setint(int num);
void setint(int num){
	newinterrupt |= (1 << num);
	updateinterrupts = true;
}

void unsetint(int num){
	newinterrupt &= ~(1 << num);
	if(newinterrupt == 0)updateinterrupts = false;
}

void updateisr(){

	if(updateinterrupts)db_IPR.x |= newinterrupt;

	db_ISR.x = db_IPR.x & ~db_IMR.x;
	if(db_ISR.x){
		specialflags |= SPCFLAG_INT;
	}
}

int intbase(){
	return db_IVR.anon.VECTOR << 3;
}

int intlev(){

	if (db_ISR.anon.IRQ7)	return 7;
	if (db_ISR.anon.SPIS)	return 6;
	if (db_ISR.anon.TMR1)	return 6;
	if (db_ISR.anon.IRQ6)	return 6;
	if (db_ISR.anon.PEN)	return 5;
	if (db_ISR.anon.SPIM)	return 4;
	if (db_ISR.anon.TMR2)	return 4;
	if (db_ISR.anon.UART)	return 4;
	if (db_ISR.anon.WDT)	return 4;
	if (db_ISR.anon.RTC)	return 4;
	if (db_ISR.anon.KB)		return 4;
	if (db_ISR.anon.PWM)	return 4;
	if (db_ISR.anon.INT0)	return 4;
	if (db_ISR.anon.INT1)	return 4;
	if (db_ISR.anon.INT2)	return 4;
	if (db_ISR.anon.INT3)	return 4;
	if (db_ISR.anon.INT4)	return 4;
	if (db_ISR.anon.INT5)	return 4;
	if (db_ISR.anon.INT6)	return 4;
	if (db_ISR.anon.INT7)	return 4;
	if (db_ISR.anon.IRQ3)	return 3;
	if (db_ISR.anon.IRQ2)	return 2;
	if (db_ISR.anon.IRQ1)	return 1;
	return -1;
}

/*
 * custptr is a pointer to a shared memory block which will "back-up"
 * the register values of the custom circuits, allowing other processes
 * to look at register values
 */
void custom_init(shared_img * shptr){

	CustShptr = shptr;
	CustShptr->PICF = 0;
	CustShptr->VPW = 0xff;
	CustShptr->POSR = 0;

	/*
	CustShptr->grpalette[0] = 1;
	CustShptr->grpalette[1] = 0;
	CustShptr->grpalette[2] = 3;
	CustShptr->grpalette[3] = 7;
	*/

	/*
	CustShptr->penx = 0;
	CustShptr->peny = 0;
	CustShptr->buttons = 0;
	*/

	//CustShptr->LcdPower = lcdOn;
	customreset();
}

ULONG custom_lget(CPTR addr){
	dbgprintf("Custom long read at:0x%08x\n", addr);
	switch (addr & 0xffff) {
		case IMR:
			return db_IMR.x;
		case IWR:
			return db_IWR.x;
		case ISR:
			return db_ISR.x;
		case IPR:
			return db_IPR.x;
		case LSSA:
			//dbgprintf("PC:%08x\n",MC68000_getpc());
			//return db_LSSA.x;
			return lcd_start;
		case RTCHMS:
			//return getrtc();
		case RTCALARM:
			//return getrtcalarm();
		default:
			//fprintf(stderr, "%s(0x%x) - %x\r\n",__FUNCTION__,addr,MC68000_getpc());
			//fatal(__FILE__, __LINE__);
			return 0;
	}
}

void custom_lput(CPTR addr, ULONG value){
	dbgprintf("Custom long write at:0x%08x,Value:0x%08x\n", addr,value);
	switch (addr & 0xffff) {
	case IMR:
		db_IMR.x = value;
		updateisr();
		break;
	case IWR:
		db_IWR.x = value;
		break;
	case ISR:
		if (db_ICR.anon.ET1 && (value & 0x00010000)) {
			db_IPR.anon.IRQ1 = 0;
			updateisr();
		}
		if (db_ICR.anon.ET2 && (value & 0x00020000)) {
			db_IPR.anon.IRQ2 = 0;
			updateisr();
		}
		if (db_ICR.anon.ET3 && (value & 0x00040000)) {
			db_IPR.anon.IRQ3 = 0;
			updateisr();
		}
		if (db_ICR.anon.ET6 && (value & 0x00080000)) {
			db_IPR.anon.IRQ6 = 0;
			updateisr();
		}
		if (value & 0x00800000) {
			db_IPR.anon.IRQ7 = 0;
			updateisr();
		}
		break;
	case IPR:
		/* do nothing */
		break;
	case LSSA:
		db_LSSA.x = value;
		//CustShptr->lssa = value;
		dbgprintf("Err lcd addr write\n");
		break;
	case RTCHMS:
		//setrtc(value);
		break;
	case RTCALARM:
		//setrtcalarm(value);
		break;
	default:
		//fprintf(stderr, "%s(0x%x, 0x%x) - %x\r\n", __FUNCTION__, addr, value,
		//		MC68000_getpc());
		//fatal(__FILE__, __LINE__);
		break;
	}
}

UWORD
custom_wget(CPTR addr)
{

	dbgprintf("Custom word read at:0x%08x\n", addr);
	switch (addr & 0xffff){
	case CSGBB:
		return db_CSGBB;
	case CSGBD:
		return db_CSGBD;
	case CSCR:
		return db_CSCR;
	case CSA:
		return db_CSA;
	case CSB:
		return db_CSB;
	case CSC:
		return db_CSC;
	case CSD:
		return db_CSD;
	case WATCHDOG:
		//return getwatchdog();
	case DRAMMC:
		return db_DRAMMC;
	case DRAMC:
		return db_DRAMC;
	case SDCTRL:
		return db_SDCTRL;
	case GRPBASEA:
		return db_GRPBASEA.x;
	case GRPBASEC:
		return db_GRPBASEC.x;
	case GRPMASKC:
		return db_GRPMASKC.x;
	case PLLCR:
		//return getpllcntrl();
	case PLLFSR:
		//return getpllfsr();
	case ICR:
		return db_ICR.x;
	case IMR:
		return db_IMR.x >> 16;
	case IMR + 2:
		return db_IMR.x;
	case IWR:
		return db_IWR.x >> 16;
	case IWR + 2:
		return db_IWR.x;
	case ISR:
		return db_ISR.x >> 16;
	case ISR + 2:
		return db_ISR.x;
	case IPR:
		return db_IPR.x >> 16;
	case TCTL1:
		//return gettmr1cfg();
	case TPRER1:
		//return db_TPRER1;
	case TCMP1:
		//return db_TCMP1;
	case TSTAT1:
		//return gettstat1();
	case TCTL2:
		//return gettmr2cfg();
	case SPIMDATA:
		//return spidata;
	case SPIMCONT:
		//return readspicontrol();
	case USTCNT:
		//return db_USTCNT.x;
	case UBAUD:
		//return db_UBAUD.x;
	case URX:
		//return uartrxvaluesread();
	case UTX:
		//return uarttxvaluesread();
	case UMISC:
		//return db_UMISC.x;
	case LXMAX:
		return db_LXMAX.x;
	case LYMAX:
		return db_LYMAX.x;
	case LCXP:
		return db_LCXP.x;
	case LCYP:
		return db_LCYP.x;
	case LCWCH:
		return db_LCWCH.x;
	case LGPMR:
		return db_LGPMR.x;
	case RTCCTL:
		//return getrtccntrl();
	case RTCISR:
		//return getrtcisr();
	case RTCIENR:
		//return getrtcienr();
	case PWMC1:
		//return rspkctl();
	default:
		//fprintf(stderr, "%s(0x%x) - %x\r\n",__FUNCTION__,addr,MC68000_getpc());
		//fatal(__FILE__, __LINE__);
		return 0;
	}
}

void
custom_wput(CPTR addr, UWORD value)
{
	dbgprintf("Custom word write at:0x%08x,Value:0x%04x\n", addr,value);
	switch (addr & 0xffff) {
	case CSGBB:
		db_CSGBB = value;
		break;
	case CSGBD:
		db_CSGBD = value;
		break;
	case CSCR:
		db_CSCR = value;
		break;
	case CSA:
		db_CSA = value;
		break;
	case CSB:
		db_CSB = value;
		break;
	case CSC:
		db_CSC = value;
		break;
	case CSD:
		db_CSD = value;
		//sram protect
		break;
	case WATCHDOG:
		//setwatchdog(value);
		break;
	case DRAMMC:
		db_DRAMMC = value;
		break;
	case DRAMC:
		db_DRAMC = value;
		break;
	case SDCTRL:
		db_SDCTRL = value;
		break;
	case GRPBASEA:
		db_GRPBASEA.x = value;
		break;
	case GRPBASEC:
		db_GRPBASEC.x = value;
		break;
	case GRPMASKC:
		db_GRPMASKC.x = value;
		break;
	case PLLCR:
		//setpllcntrl(value);
		break;
	case PLLFSR:
		//setpllfsr(value);
		break;
	case ICR:
		db_ICR.x = value;
		break;
	case IMR:
		db_IMR.x &= 0x0000ffff;
		db_IMR.x |= value << 16;
		updateisr();
		break;
	case IMR + 2:
		db_IMR.x &= 0xffff0000;
		db_IMR.x |= value;
		updateisr();
		break;
	case IWR:
		db_IWR.x &= 0x0000ffff;
		db_IWR.x |= value << 16;
		break;
	case IWR + 2:
		db_IWR.x &= 0xffff0000;
		db_IWR.x |= value;
		break;
	case ISR:
		if (db_ICR.anon.ET1 && (value & 0x0001)) {
			db_IPR.anon.IRQ1 = 0;
		}
		if (db_ICR.anon.ET2 && (value & 0x0002)) {
			db_IPR.anon.IRQ2 = 0;
		}
		if (db_ICR.anon.ET3 && (value & 0x0004)) {
			db_IPR.anon.IRQ3 = 0;
		}
		if (db_ICR.anon.ET6 && (value & 0x0008)) {
			db_IPR.anon.IRQ6 = 0;
		}
		if (value & 0x0080) {
			db_IPR.anon.IRQ7 = 0;
		}
		updateisr();
		break;
	case ISR + 2:
		/* updateisr(); */
		break;
	case IPR:
		db_IPR.x = db_IPR.x&(~(value<<16));
		updateisr();
		break;
	case TCTL1:
		//settmr1cfg(value);
		break;
	case TPRER1:
			/*
		waitforincrement.lock();
		db_TPRER1 = value;
		waitforincrement.unlock();*/
		break;
	case TCMP1:
			/*
		waitforincrement.lock();
		db_TCMP1 = value;
		waitforincrement.unlock();*/
		break;
	case TSTAT1:
		//settstat1(value);
		break;
	case TCTL2:
		//settmr2cfg(value);
		break;
	case LXMAX:
		db_LXMAX.x = value;
		break;
	case LYMAX:
		db_LYMAX.x = value;
		break;
	case LCXP:
		db_LCXP.x = value;
		break;
	case LCYP:
		db_LCYP.x = value;
		break;
	case LCWCH:
		db_LCWCH.x = value;
		break;
	case LGPMR:
		db_LGPMR.x = value;
		/*
		CustShptr->grpalette[0] = db_LGPMR.anon.G0;
		CustShptr->grpalette[1] = db_LGPMR.anon.G1;
		CustShptr->grpalette[2] = db_LGPMR.anon.G2;
		CustShptr->grpalette[3] = db_LGPMR.anon.G3;
		*/
		break;
	case RTCCTL:
		//setrtccntrl((UBYTE)value);
		break;
	case RTCISR:
		//setrtcisr((UBYTE)value);
		break;
	case RTCIENR:
		//setrtcienr((UBYTE)value);
		break;
	case ICEMCR:
	case ICEMSR:
		//it is just turning of incircuit debuging witch is not used anyway
		break;
	case PWMC1:
		//wspkctl(value);
		break;
	default:
		//fprintf(stderr, "%s(0x%x, 0x%x) - %x\r\n", __FUNCTION__, addr, value,
		//		MC68000_getpc());
		//fatal(__FILE__, __LINE__);
		break;
	}
}

UBYTE
custom_bget(CPTR addr)
{
	dbgprintf("Custom byte read at:0x%08x\n", addr);
	switch (addr & 0xffff) {
	case PBDIR:
		return getportdata(dir,b);
	case PBDATA:
		return getportdata(data,b);
	case PBSEL:
		return getportdata(sel,b);
	case PBPUEN:
		return getportdata(pull,b);
	case PCPDEN:
		return getportdata(pull,c);
	case SCR:
		return db_SCR.x;
	case PCTLR:
		return db_PCTLR.x;
	case IVR:
		return db_IVR.x;
	case PCDIR:
		return getportdata(dir,c);
	case PCDATA:
		//db_PCDATA.anon.NMI = 1;	/* who knows, this makes the power on key work */
		//this should just be set when you push the power button
		return getportdata(data,c);
	case PCSEL:
		return getportdata(sel,c);
	case PDDIR:
		return getportdata(dir,d);
	case PDDATA:
		return getportdata(data,d);
	case PDPUEN:
		return getportdata(pull,d);
	case PDSEL:
		return getportdata(sel,d);
	case PDKBEN:
		return db_PDKBEN;
	case PDPOL:
		return db_PDPOL;
	case PDIRQEN:
		return db_PDIRQEN;
	case PDIRQEDGE:
		return db_PDIRQEDGE;
	case PEDIR:
		return getportdata(dir,e);
	case PEDATA:
		return getportdata(data,e);
	case PEPUEN:
		return getportdata(pull,e);
	case PESEL:
		return getportdata(sel,e);
	case PFDIR:
		return getportdata(dir,f);
	case PFDATA:
		return getportdata(data,f);
	case PFPUEN:
		return getportdata(pull,f);
	case PFSEL:
		return getportdata(sel,f);
	case PGDIR:
		return getportdata(dir,g);
	case PGDATA:
		return getportdata(data,g);
	case PGPUEN:
		return getportdata(pull,g);
	case PGSEL:
		return getportdata(sel,g);
	case PJDIR:
		return getportdata(dir,j);
	case PJDATA:
		return getportdata(data,j);
	case PJPUEN:
		return getportdata(pull,j);
	case PJSEL:
		return getportdata(sel,j);
	case PKDIR:
		return getportdata(dir,k);
	case PKDATA:
		return getportdata(data,k);
	case PKPUEN:
		return getportdata(pull,k);
	case PKSEL:
		return getportdata(sel,k);
	case PMDIR:
		return getportdata(dir,m);
	case PMDATA:
		return getportdata(data,m);
	case PMPUEN:
		return getportdata(pull,m);
	case PMSEL:
		return getportdata(sel,m);
	case URX:
		//return uartrxvaluesreadcfgbyte();
	case LVPW:
		return db_LVPW.x;
	case LBLKC:
		return db_LBLKC.x;
	case LPICF:
		return db_LPICF.x;
	case LPXCD:
		return db_LPXCD.x;
	case LCKCON:
		return db_LCKCON.x;
	case LPOSR:
		return db_LPOSR.x;
	case LFRCM:
		return db_LFRCM.x;
	case RTCCTL:
		//return getrtccntrl();
	case RTCISR:
		//return getrtcisr();
	case RTCIENR:
		//return getrtcienr();
	default:
		//fprintf(stderr, "%s(0x%x) - %x\r\n",__FUNCTION__,addr,MC68000_getpc());
		//fatal(__FILE__, __LINE__);
		return 0;
	}
}

void
custom_bput(CPTR addr, UBYTE value)
{
	dbgprintf("Custom byte write at:0x%08x,Value:0x%02x\n", addr,value);
	switch (addr & 0xffff) {
	case SCR:
		db_SCR.x = value & ~(value & 0xe0);
		break;
	case PCTLR:
		db_PCTLR.x = value;
		break;
	case IVR:
		db_IVR.x = value;
		break;
	case PBDIR:
		setportdata(value,dir,b);
		break;
	case PBDATA:
		setportdata(value,data,b);
		break;
	case PBSEL:
		setportdata(value,sel,b);
		break;
	case PBPUEN:
		setportdata(value,pull,b);
		break;
	case PCPDEN:
		setportdata(value,pull,c);
		break;
	case PCDIR:
		setportdata(value,dir,c);
		break;
	case PCDATA:
		setportdata(value,data,c);
		break;
	case PCSEL:
		setportdata(value,sel,c);
		break;
	case PDDIR:
		setportdata(value,dir,d);
		break;
	case PDDATA:
		setportdata(value,data,d);
		break;
	case PDPUEN:
		setportdata(value,pull,d);
		break;
	case PDPOL:
		db_PDPOL = value;
		break;
	case PDIRQEN:
		break;
	case PDIRQEDGE:
		db_PDIRQEDGE = value;
		break;
	case PDSEL:
		setportdata(value,sel,d);
		break;
	case PDKBEN:
		db_PDKBEN = value;
		break;
	case PEDIR:
		setportdata(value,dir,e);
		break;
	case PEDATA:
		setportdata(value,data,e);
		break;
	case PEPUEN:
		setportdata(value,pull,e);
		break;
	case PESEL:
		setportdata(value,sel,e);
		break;
	case PFDIR:
		setportdata(value,dir,f);
		break;
	case PFDATA:
		setportdata(value,data,f);
		break;
	case PFPUEN:
		setportdata(value,pull,f);
		break;
	case PFSEL:
		setportdata(value,sel,f);
		break;
	case PGDIR:
		setportdata(value,dir,g);
		break;
	case PGDATA:
		setportdata(value,data,g);
		break;
	case PGPUEN:
		setportdata(value,pull,g);
		break;
	case PGSEL:
		setportdata(value,sel,g);
		break;
	case PJDIR:
		setportdata(value,dir,j);
		break;
	case PJDATA:
		setportdata(value,data,j);
		break;
	case PJSEL:
		setportdata(value,sel,j);
		break;
	case PJPUEN:
		setportdata(value,pull,j);
		break;
	case PKDIR:
		setportdata(value,dir,k);
		break;
	case PKDATA:
		setportdata(value,data,k);
		break;
	case PKPUEN:
		setportdata(value,pull,k);
		break;
	case PKSEL:
		setportdata(value,sel,k);
		break;
	case PMDIR:
		setportdata(value,dir,m);
		break;
	case PMDATA:
		setportdata(value,data,m);
		break;
	case PMPUEN:
		setportdata(value,pull,m);
		break;
	case PMSEL:
		setportdata(value,sel,m);
		break;
	case UTX + 1:
		//if(db_UMISC.anon.LOOP)fprintf(stderr,"What the hell is this for?(UART in loopback mode)\n");
		//uarttxvalueswritebyte(value);
		break;
	case LVPW:
		db_LVPW.x = value;
		CustShptr->VPW = value;
		break;
	case LBLKC:
		db_LBLKC.x = value;
		break;
	case LPICF:
		db_LPICF.x = value;
		CustShptr->PICF = value;
		break;
	case LPXCD:
		db_LPXCD.x = value;
		break;
	case LCKCON:
		db_LCKCON.x = value;
		//CustShptr->LcdPower = db_LCKCON.anon.LCDCON ? lcdOn : lcdOff;
		break;
	case LPOSR:
		db_LPOSR.x = value;
		CustShptr->POSR = value;
		break;
	case LFRCM:
		db_LFRCM.x = value;
		break;
	case RTCCTL:
		//setrtccntrl(value);
		break;
	default:
		//fprintf(stderr, "%s(0x%x, 0x%x) - %x\r\n", __FUNCTION__, addr, value,
		//		MC68000_getpc());
		//fatal(__FILE__, __LINE__);
		break;
	}
}

addrbank custom_bank = {
	custom_lget, custom_wget, custom_bget,
	custom_lput, custom_wput, custom_bput,
	default_xlate, default_check
};




//speaker
UBYTE period,counter;
UBYTE samples[2];
UWORD* speakerbuffer = nullptr;

void wspkctl(UWORD val){
	db_PWMC.x = val;
}

UWORD rspkctl(){
	return db_PWMC.x;
}



//display
WORD LCDW,LCDH;
size_t_68k LCDBYTES;
UWORD* framebuffer = nullptr;

void lcd_init(int w,int h){
	LCDBYTES = w * h * 2;
	LCDW = w;
	LCDH = h;
	framebuffer = new UWORD[LCDBYTES];//UWORD == (UBYTE * 2) DONT DIVIDE BY 2 (second half is for double buffering)
}

UBYTE lcd_bget(CPTR addr){
	addr -= lcd_start;
	if(addr & 1)return framebuffer[addr >> 1];
	return framebuffer[addr >> 1] >> 8;
}

UWORD lcd_wget(CPTR addr){
	addr -= lcd_start;
	return framebuffer[addr >> 1];
}

ULONG lcd_lget(CPTR addr){
	addr -= lcd_start;
	return (((ULONG)framebuffer[addr >> 1]) << 16) | framebuffer[(addr >> 1) + 1];
}

void lcd_bput(CPTR addr,UBYTE b){
	//dbgprintf("what does the fox eat? Bytes!\n");
	addr -= lcd_start;
	if(!(addr & 1)){
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF) | (((UWORD)b) << 8);
	}
	else{
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF00) | b;
	}
}

void lcd_wput(CPTR addr,UWORD w){
	//dbgprintf("what does the fox say? Words!\n");
	addr -= lcd_start;
	framebuffer[addr >> 1] = w;
}

void lcd_lput(CPTR addr,ULONG l){
	//dbgprintf("where does the fox shop? Longs!\n");
	addr -= lcd_start;
	framebuffer[addr >> 1] = l >> 16;
	framebuffer[(addr >> 1) + 1] = (UWORD)l;
}

UWORD* lcd_xlate(CPTR addr){
	return framebuffer + ((addr - lcd_start) >> 1);
}

int lcd_check(CPTR addr, ULONG offset){
	return 1;
}

addrbank lcd_bank = {
	lcd_lget, lcd_wget, lcd_bget,
	lcd_lput, lcd_wput, lcd_bput,
	lcd_xlate, lcd_check
};
