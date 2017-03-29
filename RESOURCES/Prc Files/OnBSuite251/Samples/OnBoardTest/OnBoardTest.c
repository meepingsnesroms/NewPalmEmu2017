
#define MAINFORM 1000

#include "EventLoop.c"

#define TEST(t, x) test++; if (t != x) error(t, x); else pass++

int curY = 20;
int pass = 0;
int test = 0;

void printString(char *s)
{
	WinDrawChars(s, StrLen(s), 4, curY);
	curY += 12;
	if (curY > 160) curY = 20;
}

void error(long value, long expected)
{
	char buffer[64];
	StrPrintF(buffer, "test #%d, Expected %ld, got %ld", test, expected, value);
	printString(buffer);
}

void report()
{
	char buffer[64];
	StrPrintF(buffer, "Passed %d", pass);
	printString(buffer);
}

void testOperators()
{
	int i1 = 12344;
	int i2 = 3;
	
	int t;
	
	t = i1 + i2;
	TEST(t, 12347);
	
	t = i1 - i2;
	TEST(t, 12341);
	
	t = i1 * i2;
	TEST(t, -28504);
	
	t = i1 / i2;
	TEST(t, 4114);
	
	t = i1 % i2;
	TEST(t, 2);
	
	t = i1 & i2;
	TEST(t, 0);
	
	t = i1 | i2;
	TEST(t, 12347);
	
	t = i1 ^ i2;
	TEST(t, 12347);
	
	t = -i1;
	TEST(t, -12344);
	
	t = ~i1;
	TEST(t, -12345);
	
	t = !i1;
	TEST(t, 0);
	
	t = i1 > i2;
	TEST(t, 1);
	
	t = i1 < i2;
	TEST(t, 0);
	
	t = i1 >= i2;
	TEST(t, 1);
	
	t = i1 <= i2;
	TEST(t, 0);
	
	t = i1 == i2;
	TEST(t, 0);
	
	t = i1 != i2;
	TEST(t, 1);
	
	t = i1++;
	TEST(t, 12344);
	TEST(i1, 12345);
	
	t = ++i1;
	TEST(t, 12346);
	TEST(i1, 12346);
	
	t = --i1;
	TEST(t, 12345);
	TEST(i1, 12345);
	
	t = i1--;
	TEST(t, 12345);
	TEST(i1, 12344);
	
	t = i1 << i2;
	TEST(t, -32320);
	
	t = i1 >> i2;
	TEST(t, 1543);
	
	report();
	
}

void testLongOperators()
{
	long i1 = 8012344;
	long i2 = 13;
	
	long t;
	
	t = i1 + i2;
	TEST(t, 8012357);
	
	t = i1 - i2;
	TEST(t, 8012331);
	
	t = i1 * i2;
	TEST(t, 104160472);
	
	t = i1 / i2;
	TEST(t, 616334);
	
	t = i1 % i2;
	TEST(t, 2);
	
	t = i1 & i2;
	TEST(t, 8);

	t = i1 | i2;
	TEST(t, 8012349);
	
	t = i1 ^ i2;
	TEST(t, 8012341);
	
	t = -i1;
	TEST(t, -8012344);
	
	t = ~i1;
	TEST(t, -8012345);
	
	t = !i1;
	TEST(t, 0);
	
	t = i1 > i2;
	TEST(t, 1);
	
	t = i1 < i2;
	TEST(t, 0);
	
	t = i1 >= i2;
	TEST(t, 1);
	
	t = i1 <= i2;
	TEST(t, 0);
	
	t = i1 == i2;
	TEST(t, 0);
	
	t = i1 != i2;
	TEST(t, 1);
	
	t = i1++;
	TEST(t, 8012344);
	TEST(i1, 8012345);
	
	t = ++i1;
	TEST(t, 8012346);
	TEST(i1, 8012346);
	
	t = --i1;
	TEST(t, 8012345);
	TEST(i1, 8012345);
	
	t = i1--;
	TEST(t, 8012345);
	TEST(i1, 8012344);
	
	t = i1 << i2;
	TEST(t, 1212612608);
	
	t = i1 >> i2;
	TEST(t, 978);
	
	report();
	
}

void testAssignments()
{
	int i1 = 12344;
	int i2 = 3;
	
	i1 += i2;
	TEST(i1, 12347);
	
	i1 -= i2;
	TEST(i1, 12344);
	
	i1 *= i2;
	TEST(i1, -28504);
	
	i1 /= i2;
	TEST(i1, -9501);
	
	i1 = 12344;
	
	i1 %= i2;
	TEST(i1, 2);

	i1 &= i2;
	TEST(i1, 2);
	
	i1 |= i2;
	TEST(i1, 3);
	
	i1 ^= i2;
	TEST(i1, 0);
	
	i1 = 12344;
	i1 >>= i2;
	TEST(i1, 1543);
	
	i1 <<= i2;
	TEST(i1, 12344);

	report();	
}

void testLongAssignments()
{
	long i1 = 8012344;
	long i2 = 13;
	
	i1 += i2;
	TEST(i1, 8012357);
	
	i1 -= i2;
	TEST(i1, 8012344);
	
	i1 *= i2;
	TEST(i1, 104160472);
	
	i1 /= i2;
	TEST(i1, 8012344);
	
	i1 %= i2;
	TEST(i1, 2);

	i1 &= i2;
	TEST(i1, 0);
	
	i1 |= i2;
	TEST(i1, 13);
	
	i1 ^= i2;
	TEST(i1, 0);
	
	i1 = 8012344;
	
	i1 <<= i2;
	TEST(i1, 1212612608);

	i1 >>= i2;
	TEST(i1, 148024);

	report();	
}

float f_array[] = { 0.1, 2.2, 3.4 };

void regress()
{
	float f0 = f_array[0];
	float f1 = f_array[1];
	float f2 = f_array[2];
	
	int t;
	
	t = (f1 < f2);
	TEST(t, 1);
	
	t = (f0 > f2);
	TEST(t, 0);
}

void testStrings()
{
	char *str[] = { 
	
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001",
	"string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001", "string 0001"

	};
}

Boolean mainFormEventHandler(EventPtr evt)
{
	Boolean handled = false;
	FormPtr frm = FrmGetActiveForm();
	switch (evt->eType) {
		case frmOpenEvent :
			handled = true;
			break;
		case penUpEvent :
			testOperators();
			testLongOperators();
			testAssignments();
			testLongAssignments();
			handled = true;
			break;
	}
	return handled;		
}