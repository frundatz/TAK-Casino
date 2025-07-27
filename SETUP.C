#include <conio.h>
#include <stdio.h>
#include <math.h>
void regnum();
void bbsname();
void cheat();
void monitor();
void minsperday();
void betadjust();
void casino_dir();
void save();
char onek(char *s);
void print(char *s);
void jump(int x, int y);
void cleareol();
void finish_installing();

struct {
  char registration[20],bbs_name[30],cas_dir[30];
  int cheat_on,monitor,mins;
  float betadjust;
} info;
char temps[81],temps2[81],tempc,spaces[] = "                       ";
int tempi,mode = 0;
float tempf;
FILE *fptr;


main(int argc, char *argv[])
{
  if(argc > 1) {
    strupr(argv[1]);
    if(strcmp(argv[1], "/R") == 0)
      mode = 1;
  }
  if(mode)
    printf("\x1B[2J");
  else
    clrscr();
  jump(28,3);
  textcolor(LIGHTBLUE);
  print("TAK's Casino v1.08 Setup\n\n");
  textcolor(LIGHTGRAY);
  print("Please Enter The Following Information:");

  if((fptr=fopen("CASINO.CFG","rb"))==NULL) {
    print("\n\n");
    regnum();
    bbsname();
    cheat();
    monitor();
    minsperday();
    betadjust();
    casino_dir();
    print("\n\n");
    save();
    finish_installing();
    cprintf("\n\n\n\n\n\nTAK's Casino is now installed and ready to go!\n\n");
    exit(0);
  }
  fread(&info, sizeof(info),1,fptr);
  do {
    for(tempi = 18; tempi < 25; tempi++) {
      jump(1,tempi);
      cleareol();
    }
    jump(1,5);
    sprintf(temps2,"\n\n1> Registration Number    : %s%s",info.registration,spaces);
    print(temps2);
    sprintf(temps2,"\n2> BBS Name               : %s%s",info.bbs_name,spaces);
    print(temps2);
    strcpy(temps,"Off.");
    if(info.cheat_on)
      strcpy(temps,"On.");
    sprintf(temps2,"\n3> Cheating Option        : %s%s",temps,spaces);
    print(temps2);
    if(info.monitor == 1)
      strcpy(temps,"Monochrome.");
    if(info.monitor == 2)
      strcpy(temps,"CGA/EGA/VGA");
    sprintf(temps2,"\n4> Monitor                : %s%s",temps,spaces);
    print(temps2);
    sprintf(temps,"\n5> Minutes per day        : %d%s",info.mins,spaces);
    print(temps);
    sprintf(temps,"\n6> Betting Adjustment     : %.2f%s",info.betadjust,spaces);
    print(temps);
    sprintf(temps,"\n7> Casino Directory       : %s%s",info.cas_dir,spaces);
    print(temps);
    print("\nQ> Quit & Save");
    cleareol();
    printf("\n");
    cleareol();
    print("\nChange which >  \b");
    tempi = 0;
    tempc = onek("1234567Q");
    print("\n");
    switch(tempc) {
      case '1':
        regnum();
        break;
      case '2':
        bbsname();
        break;
      case '3':
        cheat();
        break;
      case '4':
        monitor();
        break;
      case '5':
        minsperday();
        break;
      case '6':
        betadjust();
        break;
      case '7':
        casino_dir();
        break;
      case 'q':
      case 'Q':
        save();
        exit(0);
    }
  } while (tempi != 5052);
}

void regnum()
{
  print("Registration Number    : ");
  gets(temps);
  strupr(temps);
  if(strlen(temps) > 1)
    strcpy(info.registration,temps);
  strupr(info.registration);
}

void bbsname()
{
  print("BBS Name               : ");
  gets(temps);
  if(strlen(temps) > 1)
    strcpy(info.bbs_name,temps);
}

void cheat()
{
  print("\nUse \"cheating\" option [Y/n]? ");
  tempc = getche();
  switch(tempc) {
    case 'n':
    case 'N':
      info.cheat_on = 0;
      break;
    default:
      info.cheat_on = 1;
  }
}

void monitor()
{
  print("\nWhich graphics adaptor do you have:");
  print("\n1> Monochrome");
  print("\n2> CGA/EGA/VGA");
  tempi = 0;
  print("\nChoose > ");
  do {
    tempc = onek("12");
    switch(tempc) {
      case '1':
        info.monitor = 1;
        tempi = 1;
        break;
      case '2':
	info.monitor = 2;
	tempi = 1;
	break;
    }
  } while (!tempi);

}

void minsperday()
{
  print("\n\nAllow how many minutes per day [5-30, Def=10]? ");
  gets(temps);
  tempi = atoi(temps);
  if((tempi < 5) || (tempi > 30))
    tempi = 10;
  info.mins = tempi;
}

void betadjust()
{
  print("\n\nEnter betting adjustment (normal is 1.00): ");
  gets(temps);
  tempf = atof(temps);
  if((tempf < .01) || (tempf > 3))
    tempf = 1;
  info.betadjust = tempf;
}

void casino_dir()
{
  print("\n\nEnter casino directory (default is CASINO): ");
  gets(temps);
  if(strlen(temps) > 1)
    strcpy(info.cas_dir, temps);
  else
    strcpy(info.cas_dir,"casino");
  strupr(info.cas_dir);
}

void save()
{
  fptr = fopen("casino.cfg","wb");
  print("Saving Information...");
  fwrite(&info, sizeof(info),1,fptr);
  fclose(fptr);
  print("Done.\n");
}


char onek(char *s)
{
  char ch;

  do {
    ch = getch();
    if((ch > 96) && (ch < 123))
      ch -= 32;
  } while(strchr(s,ch)==0);
  sprintf(temps,"%c\n",ch);
  print(temps);
  return(ch);
}

void print(char *s)
{
  if(mode)
    printf("%s",s);
  else
    cprintf("%s",s);
}

void jump(int x, int y)
{
  if(mode)
    printf("\x1B[%d;%dH",y,x);
  else
    gotoxy(x,y);
}

void cleareol()
{
  if(mode)
    printf("\x1B[K");
  else
    clreol();
}

void finish_installing()
{
  sprintf(temps,"%s",info.cas_dir);
  mkdir(temps);

  sprintf(temps,"Pkunzip CAS_DIR.Zip %s",info.cas_dir);
  printf("%s",temps);
  system(temps);
}