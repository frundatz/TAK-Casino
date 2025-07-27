#define NONE "-"
#define CHAT "+"
char uti_temps[81];

void printfile(char *s)
{
  char string[95];
  int abort=0;

  if ( (fptr=fopen(s,"r")) == NULL) {
    sprintf(string,"\"%s\" File Not Found.\n",s);
    pl(string);
    return;
  }

  while((fgets(string,94,fptr) != NULL) && (!abort)) {
    string[strlen(string)-1] = '\0';
    pla(string,&abort);
  }
  fclose(fptr);
}

void pausescr()
{
  if (okansi) {
    outstr("7®®0 \x1B[4mHit Any Key\x1B[0m 7¯¯0\x1b[17D");
    getkey();
    outstr("0                 \x1b[17D");
  } else {
    outstr("[Hit Any Key]");
    getkey();
    backspace(13);
  }
}

void backspace (int number)
{
  int count=1;

  do {
    outstr("\b \b");
    ++count;
  } while (count < number);
}

void write_points()
{
  fptr=fopen("READ.PNT","w");
  fputs("1",fptr);
  fclose(fptr);
  fptr=fopen("POINTS.PNT","w");
  fprintf(fptr,"%f",gold);
  fclose(fptr);
}

void itimer()
{
  outportb(0x43,0x34);
  outportb(0x40,0x00);
  outportb(0x40,0x00);

}

double timer()
{
  double cputim;
  unsigned short int h,m,l1,l2;

  disable();
  outportb(0x43,0x00);
  m=peek(0x0040,0x006c);
  h=peek(0x0040,0x006e);
  l1=inportb(0x40);
  l2=inportb(0x40);
  enable();
  l1=((l2*256)+l1) ^ 65535;
  cputim=((h*65536. + m)*65536. + l1)*8.380955e-7;
  return (cputim);
}

void period(int times)
{
  int count=0;

  do {
    outstr(".");
    ++count;
  } while (count < times);
}

void outstr(char *s)
{
  int count;

  for(count = 0; count < strlen(s); count++)
    printf("%c",s[count]);
}

void nl()
{
  printf("\n");
}

void pl(char *s)
{
  outstr(s);
  nl();
}

void top(char *s)
{
  int top_tempi;

  sprintf(uti_temps,"Current User: %s  Gold: %.0f",name,gold);
  top_tempi = strlen(uti_temps) - 7;
  do {
    strcat(uti_temps," ");
    ++top_tempi;
  } while (top_tempi < 41);

  bios_write(0);

  strcpy(uti_temps,s);
  if(strcmp(s,CHAT) == 0)
    strcpy(uti_temps,"< Hit [ESCAPE] To Exit Chat >");
  else
    if((strcmp(s,NONE)==0) || (!info.cheat_on))
      return;
  top_tempi = strlen(uti_temps);
  do {
    strcat(uti_temps," ");
    ++top_tempi;
  } while (top_tempi < 48);

  bios_write(1);
}

void bios_write(int i)
{
  int far *farptr;
  int count;
  char ch;

  if(info.monitor == 1)
    farptr = (int far *) 0xB0000000;
  if(info.monitor == 2)
    farptr = (int far *) 0xB8000000;
  count = 0;
  do {
    ch = uti_temps[count];
    *(farptr + count + (i*80)) = ch | 0x7000;
    ++count;
  } while (count < strlen(uti_temps));
}

char onek(char *s)
{
  char ch;

  top(NONE);
  do {
    ch = getkey();
    if((ch > 96) && (ch < 123))
      ch -= 32;
  } while((strchr(s,ch)==0) && (ch == 0));
  printf("%c\n",ch);
  return(ch);
}


void input1(char *s, int length, int type)
{
  int curpos=0,ok;
  char ch;

  top(NONE);
  do {
    ch = getkey();
    ok = 0;
    if((ch == 8) && (curpos > 0)) {
      backspace(1);
      --curpos;
    }
    if((ch == 23) && (curpos > 0))
      do {
        backspace(1);
	--curpos;
      } while((s[curpos] != 32) && (curpos > 0));
    if((ch == 24) && (curpos > 0)) {
      backspace(curpos+1);
      curpos = 0;
    }
    if(ch == 13) {
      s[curpos] = '\0';
      nl();
    }
    if(type == 0) {
      if((ch > 31) && (ch < 123))
	ok = 1;
    }
    if(type == 1) {
      if((ch > 96) && (ch < 123))
	ch -= 32;
      if((ch > 64) && (ch < 91))
	ok = 1;
    }
    if(type == 2) {
      if((ch > 47) && (ch < 58))
	ok = 1;
    }
    if(ch == 32)
      ok = 1;
    if(curpos > length)
      ok = 0;
    if(ok) {
      printf("%c",ch);
      s[curpos] = ch;
      ++curpos;
    }
  } while (ch != 13);
}

void input(char *s, int length)
{
  input1(s,length,0);
}

char getkey()
{
  char ch,sch;

  do {
    ch = getch();
    if(ch == 0) {
      sch = getch();
      if(sch == 68)
        chat();
      if(sch == 65)
        --info.mins;
      if(sch == 66)
        ++info.mins;
      if(sch == 63)
	exit(0);
      if(sch == 59)
	top("F1=Menu, F5=Boot, F7= -1 M, F8= +1 M, F10=Chat");
    }
  } while (ch == 0);
    return(ch);
}

int yes_no(int yn)
{
  char ok[4],ch;

  strcpy(ok,"YN");
  ok[2] = 13;
  ok[3] = '\0';
  ch = onek(ok);
  if(ch == 'Y')
    return(1);
  if(ch == 'N')
    return(0);
  return(yn);
}

int yn()
{
  yes_no(0);
}

int ny()
{
  yes_no(1);
}

void chat()
{
  char ch;

  nl();
  nl();
  pl("< Chat Mode >");
  nl();
  top(CHAT);
  do {
    ch = getkey();
    switch(ch) {
      case 13:
	nl();
	break;
      default:
        printf("%c",ch);
	break;
    }
  } while(ch != 27);
  nl();
  nl();
  pl("< End Chat Mode >");
}

void pla(char *s, int *abort)
{
  int i,next;

  i=0;
  while ((s[i]) && (!(*abort))) {
    printf("%c",s[i++]);
    if(kbhit() != 0)
      if(getch() == 32)
        *abort = 1;
  }
  if (!(*abort))
    nl();
}

void outchr(char ch)
{
  printf("%c",ch);
}