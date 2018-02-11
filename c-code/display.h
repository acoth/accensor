// Index in pixel array is
// [R=0,G=1,B=2] * 96
// + [Left=0 to right=15]*6
// + [Bottom=0 to top = 5]

// Constants to control data to write;
// usually you'll want c=PIXEL|ENABLE
#define PIXEL 0
#define DOT_CORRECTION 1
#define ENABLE 2
#define DISABLE 0

void WriteDisplay(unsigned short pixel[288], char c);
