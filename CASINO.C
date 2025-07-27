#include "skel.c"
#include "cas_fcns.h"

struct {
  char alias[30];
  unsigned long gold;
  long guts_cap, gold_bonus;
} player;

struct {
  char user_name[25];
  unsigned long time_used;
  char time_begin[15];
} log;
struct {
  char registration[20];
  char bbs_name[30];
  char cas_dir[30];
  int cheat_on,monitor,mins;
  float betadjust;
} info;
char temps[121],timebegin[15];
int tempi,suit[5][15],used,number,type,done,dealer,menu,winner,
    player_number[5],dealer_number[5],player_type[5],dealer_type[5],
    player_cards=0,dealer_cards=0,player_total,dealer_total,stay,
    player_ace=0,dealer_ace=0,reg;
unsigned long bet,begin_time,prev_used;
#define VERSION "1.08"
FILE *fptr;

#include "cas_util.c"

void main(int argc, char *argv[])
{

  char s[81];
  time_t bintime;

  if (argc<2)
    strcpy(s,"chain.txt");
  else
    strcpy(s,argv[1]);

  if (read_in_data(s)==-1) {
    printf("\nUnable to find CHAIN.TXT\n\n");
    exit(0);
  }

  if((fptr=fopen("CASINO.CFG","rb"))==NULL) {
    printf("\n\nCan't open file \"CASINO.CFG\".  Run SETUP.EXE!\n\n");
    exit(1);
  }
  fread(&info,sizeof(info),1,fptr);

  sprintf(s,"%s\\CASINO.LOG",info.cas_dir);
  if(access(s,00)!=0)
    write_new_day();
  else {
    if(compare_date()) {
      fptr=fopen(s,"rb");
      while(fread(&log,sizeof(log),1,fptr)==1) {
        if(strcmp(name,log.user_name)==0)
          prev_used += log.time_used;
      }
    }
  }

  begin_time = (timer() - prev_used);
  time(&bintime);
  strcpy(timebegin,ctime(&bintime));
  timebegin[19] = '\0';
  strrev(timebegin);
  timebegin[9] = '\0';
  strrev(timebegin);



  reg = check_registration();
  outchr(12);
  if (okansi)
    sprintf(s,"%s\\CASINO.ANS",info.cas_dir);
  else
    sprintf(s,"%s\\CASINO.MSG",info.cas_dir);
  printfile(s);
  if ((!reg) && (info.cheat_on))
    info.cheat_on = 0;
  if (!reg)
    pl("0This Copy Is 6UN7-0REGISTERED7!0");
  nl();
  done=0;
  randomize();
  do {
    nl();
    tempi = check_time();
    sprintf(temps,"7[0TL: %d7]0 Select Game 7[3? 7-0 Menu7] 3>0 ",tempi);
    outstr(temps);
    menu = onek("BCDFGHIQRSTUV?*");
    switch (menu) {
      case 'B':
        shuffle();
        do {
          blackjack();
        } while (playagain());
        done=0;
        break;
      case 'C':
        do {
	  craps();
	} while (playagain());
	done=0;
	break;
      case 'D':
        do {
	  dice_black();
	} while (playagain());
	done=0;
	break;
      case 'F':
        do {
          flip_coin();
        } while (bet > 0);
        done=0;
	break;
      case 'G':
        do {
          guts();
        } while (playagain());
        done=0;
        break;
      case 'H':
        shuffle();
        do {
	  hilo();
	} while (playagain());
	done = 0;
	break;
      case 'I':
	outchr(12);
        sprintf(s,"%s\\CASINO.DOC",info.cas_dir);
	printfile(s);
	break;
      case 'Q':
        done = 1;
        end_session();
        break;
      case 'R':
        do {
          roulette();
        } while (playagain());
        done=0;
        break;
      case 'S':
	do {
	  slot_machine();
	} while (playagain());
	done=0;
	break;
      case 'T':
        shuffle();
        do {
	  baccarat();
	} while (playagain());
	done=0;
	break;
      case 'U':
        russian_roulette();
	done=0;
	break;
      case 'V':
	nl();
	sprintf(temps,"TAK's Casino v%s by The Archaic Knight",VERSION);
	pl(temps);
        nl();
	pl("Special thanks to7:0");
	pl(" Excalibur 7>0 Opening ANSI and Beta-Testing");
	pl(" Dragon    7>0 Beta-Testing");
        nl();
	pl("All may be reached at The Knights Of Olde:");
	pl("(215)/453-0376.  TAK may be reached at WWIV-");
        pl("Link address 1@12551.");
	nl();
	break;
      case '?':
        outchr(12);
        sprintf(s,"%s\\CASINO.MNU",info.cas_dir);
	printfile(s);
        done=0;
        break;
      case '*':
        if (cs)
          sysop_menu();
	break;
    }
  } while (!done);
}

void blackjack()
{
  bet_amount(3000);
  if (bet == 0)
    return;
  nl();
  tempi=1;
  player_ace=0;
  dealer_ace=0;
  do {
    get_card();
    player_number[tempi]=number;
    player_type[tempi]=type;
    if (number == 14)
      ++player_ace;
    get_card();
    dealer_number[tempi]=number;
    dealer_type[tempi]=type;
    if (number == 14)
      ++dealer_ace;
    ++tempi;
  } while (tempi <= 2);
  player_cards=2;
  dealer_cards=2;
  done = 0;
  stay = 0;
  winner = 0;

  do {
    show_hands();
    if (dealer_total == 21) {
      pl("3Dealer has Blackjack0...");
      done=1;
      winner=1;
    }
    if (dealer_total > 21) {
      pl("4Dealer has Busted0...");
      done=1;
      winner=2;
    }
    if ((dealer_total < 22) && (dealer_cards > 4)) {
      pl("3Dealer has 5 cards0...3automatic win0...");
      done=1;
      winner=1;
    }
    if (player_total == 21) {
      pl("4Player has Blackjack0...");
      done=1;
      bet=bet*1.5;
      if (dealer_total != 21)
        winner=2;
    }
    if (player_total > 21) {
      pl("3Player has Busted0...");
      done=1;
      winner=1;
    }
    if ((player_total < 22) && (player_cards > 4)) {
      pl("4Player has 5 cards0...4automatic win0...");
      done=1;
      winner=2;
    }
    if ((stay) && (!done))
      dealer_turn();
    if ((!done) && (!stay)) {
      outstr("3H7]0it 3S7]0tay ");
      if ((player_total == 10) || (player_total == 11))
	outstr("3D7]0ouble ");
      outstr("7>0 ");
      if ((player_total == 10) || (player_total == 11))
        menu = onek("HSD");
      else
        menu = onek("HS");
      switch(menu)  {
        case 'H':
          ++player_cards;
          get_card();
          player_number[player_cards] = number;
          player_type[player_cards] = type;
          if (number == 14)
            ++player_ace;
          player_total += find_value(player_number[player_cards]);
          break;
        case 'D':
          bet = bet * 2;
	  ++player_cards;
	  get_card();
	  player_number[player_cards] = number;
	  player_type[player_cards] = type;
	  if (number == 14)
	    ++player_ace;
	  player_total += find_value(player_number[player_cards]);
          stay = 1;
          dealer_turn();
	  break;
        case 'S':
          stay = 1;
          dealer_turn();
          break;
      }
    }
  } while (!done);

  if (!winner) {
    if (player_total <= dealer_total) {
      done=1;
      winner=1;
    }
    else {
      done=1;
      winner=2;
    }
  }

  nl();
  if (winner == 1) {
    pl("3Sorry0, 3dealer takes the pot0...");
    gold=gold-bet;
  }
  else {
    pl("4Congratulations0,4 you win0!");
    gold=gold+bet;
  }
}

void dealer_turn()
{
  nl();
  if (dealer_total < 17) {
    pl("7Dealer Hits0...");
    ++dealer_cards;
    get_card();
    dealer_number[dealer_cards] = number;
    dealer_type[dealer_cards] = type;
    if (number == 14)
      ++dealer_ace;
    dealer_total += find_value(dealer_number[dealer_cards]);
  }
  else
    if (dealer_total < 22) {
      if (dealer_cards == 2)
        show_hands();
      pl("5Dealer Stays0...");
      if (stay)
        done = 1;
    }
}



int find_value(int card_number)
{
  int i;

  if (card_number < 11);
    i = card_number;
  if ((card_number > 10) && (card_number < 14))
    i = 10;
  if (card_number == 14)
    i = 11;
  return(i);
}

void shuffle()
{
  int count;

  nl();
  outstr("2Shuffling0...");
  tempi=1;
  used = 0;
  do {
    count = 2;
    do {
      suit[tempi][count]=1;
      ++count;
    } while (count < 15);
    ++tempi;
    outstr(".");
  } while (tempi < 5);
  nl();
}


void get_card()
{
  if (used > 36)
    shuffle();
  do {
    type = (random(4)+1);
    number = (random(13)+2);
  } while (suit[type][number] != 1);
  suit[type][number] = 0;
  ++used;
}


void find_card_name(int card_number,int card_type)
{
  static char card_numbers[13][6] =
                {  "Two",
                   "Three",
                   "Four",
                   "Five",
                   "Six",
                   "Seven",
                   "Eight",
                   "Nine",
                   "Ten",
                   "Jack",
                   "Queen",
                   "King",
                   "Ace"    },
         card_types[4][13] =
                {  " of Diamonds",
                   " of Hearts",
                   " of Spades",
                   " of Clubs"     };

  strcpy(temps," 7>0 ");
  strcat(temps,card_numbers[card_number-2]);
  strcat(temps,card_types[card_type-1]);
  outstr(temps);
}


void show_hands()
{
  nl();
  pl("3Dealer's Hand0:");
  tempi=1;
  dealer_total=0;
  do {
    if ((!stay) && (tempi == 1))
      outstr(" 7>0 3[0FACE7-0DOWN3]0");
    else
      find_card_name(dealer_number[tempi],dealer_type[tempi]);
    nl();
    dealer_total=dealer_total+find_value(dealer_number[tempi]);
    ++tempi;
  } while (tempi <= dealer_cards);
  nl();
  if ((dealer_total > 21) && (dealer_ace)) {
    tempi=dealer_ace;
    do {
      if (dealer_total > 21)
        dealer_total=dealer_total - 10;
      --dealer_ace;
    } while (dealer_ace);
    dealer_ace = tempi;
  }

  if (!stay)
    sprintf(temps,"0Total7:0 ?");
  else
    sprintf(temps,"0Total7:0 %d",dealer_total);
  pl(temps);
  nl();
  pl("4Player's Hand0:");
  tempi=1;
  player_total=0;
  do {
    find_card_name(player_number[tempi],player_type[tempi]);
    nl();
    player_total=player_total+find_value(player_number[tempi]);
    ++tempi;
  } while (tempi <= player_cards);
  nl();
  if ((player_total > 21) && (player_ace)) {
    tempi=player_ace;
    do {
      if (player_total > 21)
        player_total = player_total - 10;
      --player_ace;
    } while (player_ace);
    player_ace = tempi;
  }
  sprintf(temps,"0Total7:0 %d",player_total);
  pl(temps);
  nl();
}


void guts()
{
  int player_tries,computer_tries,total,mark,guts,smarts;
  long calc;

  randomize();
  nl();
  if ((gold * .10) > 5000)
    bet_amount(5000);
  else
    bet_amount(gold*.10);
  if (bet == 0)
    return;
  nl();
  pl("7[0Computer's Turn7]0");
  outstr("4 Mark ---> ");
  mark = dice();
  if ((mark == 2) || (mark == 12))
    guts = 57;
  if ((mark == 3) || (mark == 11))
    guts = 34;
  if ((mark == 4) || (mark == 10))
    guts = 23;
  if ((mark == 5) || (mark == 9))
    guts = 16;
  if ((mark == 6) || (mark == 8))
    guts = 12;
  if (mark == 7)
    guts = 8;
  tempi = guts;
  if (bet >= 1000)
    tempi = (guts * .96);
  if (bet >= 3000)
    tempi = (guts * .92);
  if (bet >= 5000)
    tempi = (guts * .88);
  if (bet >= 7000)
    tempi = (guts * .85);
  if (bet >= 9000)
    tempi = (guts * .82);
  if (bet == 10000)
    tempi = (guts * .79);
  guts = tempi;
  if (bet > 4000)
  pl("0");
  nl();
  computer_tries = 0;

  do {
    sprintf(temps,"Try #%2d -> ",(computer_tries+1));
    outstr(temps);
    total = dice();
    nl();
    smarts = (random(guts/2)+guts/2);
    ++computer_tries;
  } while ((total != mark) && (computer_tries < smarts));

  nl();
  if (total == mark) {
    computer_tries = 0;
    outstr("7[3-0Computer has busted");
  }
  else
    outstr("7[3-0Computer Stops");
  sprintf(temps,"3-7]0: %d Turns",computer_tries);
  pl(temps);

  nl();
  pl("7[0Player's Turn7]0");
  outstr("4 Mark ---> ");
  mark = dice();
  pl("0");
  nl();
  player_tries = 1;

  done = 0;
  do {
    sprintf(temps,"Try #%2d -> ",player_tries);
    outstr(temps);
    total = dice();
    nl();
    if (total != mark) {
      outstr("Again? ");
      do {
        top(NONE);
        menu = getkey();
      } while ((menu != 'Y') && (menu != 'y') && (menu != 'N')
	    && (menu != 'n') && (menu != 13));
      backspace(8);
      switch (menu) {
        case 13:
        case 'y':
        case 'Y':
          ++player_tries;
          break;
        case 'n':
        case 'N':
          done = 1;
          break;
      }
    }
  }  while ((total != mark) && (!done));

  nl();
  if (total == mark) {
    player_tries = 0;
    outstr("7[3-0Player has busted");
  }
  else
    outstr("7[3-0Player Stops");
  sprintf(temps,"3-7]0 %d Turns",player_tries);
  pl(temps);
  nl();

  if (computer_tries == player_tries)
    pl("7<3---0 Tie 3---7>0");
  if (computer_tries > player_tries) {
    calc = (bet * (computer_tries - player_tries));
    tempi = computer_tries - player_tries;
    sprintf(temps,"The Computer beat you by %d turns...",tempi);
    pl(temps);
    sprintf(temps,"So, you lose %.0ld gold!",calc);
    pl(temps);
    gold = gold - calc;
  }
  if (computer_tries < player_tries) {
    calc = (bet * (player_tries - computer_tries));
    tempi = player_tries - computer_tries;
    sprintf(temps,"You beat the Computer by %d turns...",tempi);
    pl(temps);
    sprintf(temps,"So, you win %.0ld gold!",calc);
    pl(temps);
    gold = gold + calc;
  }
}

int dice()
{
  int die1,die2,total;

  die1 = (random(6)+1);
  die2 = (random(6)+1);
  total = die1 + die2;
  sprintf(temps,"3%2d 2+3 %2d2 = 7%2d0",die1,die2,total);
  outstr(temps);
  return(total);
}

void russian_roulette()
{
  long templ;

  done = 0;
  nl();
  pl("You have a 310 in 360 chance of dying7...0");
  pl("If you don7'0t get shot7,0 you will get 250 gold7...0");
  pl("Resurrection costs 37/04 your gold7...0");
  nl();
  do {
    outstr("Pull the trigger 7[0y3/0N7]3?0 ");
    randomize();
    winner = (random(6)+1);
    if(winner == 1)
      top("BANNNNG!");
    else
      top("CLICK.");
    if (yn()) {
      nl();
      outstr("4Spinning the chambers0...");
      period(3);
      if (winner == 1) {
        pl("6BBAAANNNGGGG7!!!0");
        nl();
        templ = (gold * .75);
        sprintf(temps,"Sorry7,0 you lose %ld gold7...0",templ);
        pl(temps);
        gold = gold - templ;
      }
      else {
        pl("4CLICK7!0");
        nl();
        pl("Pheeeeww7!0  You win 250 gold7!0");
        gold = gold + 250;
      }
    }
    else {
      nl();
      pl("6Chicken7!0");
      done = 1;
    }
  } while (done != 1);
}

void roulette()
{
  int menu2,target,odds;
  char cheat[20];

  randomize();
  nl();
  bet_amount(8000);
  if (bet == 0)
    return;
  randomize();
  target=random(37);
  sprintf(cheat,"%d (",target);
  if (target & 1)
    strcat(cheat,"Odd)");
  else
    strcat(cheat,"Even)");

  nl();
  pl("4Place money on:          Pays:0");
  nl();
  pl("317]0  Odd 7/0 Even            17:01");
  pl("327]0  1st Half 7/0 2nd Half   17:01");
  pl("337]0  Pair of numbers      187:01");
  pl("347]0  Number               367:01");
  pl("3Q7]0  Quit");
  nl();
  outstr("Select 7>0 ");
  top(cheat);
  menu = onek("1234Q");
  winner = 0;
  odds = 1;
  nl();

  switch (menu) {
    case '1':
      outstr("Bet on which 7[3O7]0dd 7[3E7]0ven7?0 ");
      menu2 = onek("OE");
      switch (menu2) {
        case 'O':
          if (target & 1)
            winner = 1;
        break;
        case 'E':
          if (!(target & 1))
            winner = 1;
        break;
      }
      break;
    case '2':
      outstr("Bet on which 7[317]0st 7[327]0nd Half7?0 ");
      menu2 = onek("12");
      switch (menu2) {
	case '1':
	  if (target < 19)
	    winner = 1;
	break;
	case '2':
	  if (target > 18)
	    winner = 1;
	break;
      }
      break;
    case '3':
      odds = 18;
      outstr("Enter first number  7[013-0367]3:0 ");
      input1(temps,2,2);
      if (target == atoi(temps))
	winner = 1;
      outstr("Enter second number 7[013-0367]3:0 ");
      input1(temps,2,2);
      if (target == atoi(temps))
        winner = 1;
      break;
    case '4':
      odds = 36;
      outstr("Enter number 7[013-0367]3:0 ");
      input1(temps,2,2);
      if (target == atoi(temps))
	winner = 1;
      break;
    case 'Q':
      return;
  }

  nl();
  outstr("4Round and round she goes0...");
  period(2);
  nl();
  outstr("4Where she stops0...");
  period(2);
  nl();
  outstr("4You're about to find out0...");
  period(2);
  nl();
  nl();
  sprintf(temps,"0The ball lands on 6%d7...0",target);
  pl(temps);
  nl();
  if (target == 0) {
    winner = 0;
    pl("Ball landed on 07...0automatic loss7...0");
    nl();
  }
  if (winner == 1) {
    sprintf(temps,"Congratulations7!0  You bet %ld gold at %d7:01 odds7,0",bet,odds);
    pl(temps);
    sprintf(temps,"So you win %ld gold7!0",(bet * odds));
    pl(temps);
    gold = gold + (bet * odds);
  }
  else {
    pl("Sorry7...0better luck next time7...0");
    sprintf(temps,"You lose %ld gold7...0",bet);
    pl(temps);
    gold = gold - bet;
  }
}

void flip_coin()
{
  nl();
  bet_amount(3000);
  if (bet == 0)
    return;
  nl();
  number=(random(10)+1);
  if(number < 6)
    top("Heads!");
  else
    top("Tails!");

  sprintf(temps,"7[0%.0f7] [3H7]0eads7 [3T7]0ails 7[3Q7]0uit 7>0 ",gold);
  outstr(temps);
  winner = 0;
  menu = onek("HTQ");
  nl();
  outstr("Coin is");
  period(5);
  if (number < 6)
    outstr("6Heads7!");
  else
    outstr("6Tails7!");

  switch (menu) {
    case 'H':
      if (number < 6)
	winner = 1;
      break;
    case 'T':
      if (number > 5)
	winner = 1;
      break;
    case 'Q':
      return;
  }

  if (winner == 1) {
    nl();
    sprintf(temps,"0You win %ld gold7!0",bet);
    pl(temps);
    gold = gold + bet;
  }
  else {
    nl();
    sprintf(temps,"0You lose %ld gold7...0",bet);
    pl(temps);
    gold = gold - bet;
  }
}

void craps()
{
  int mark;

  randomize();
  bet_amount(5000);
  if (bet == 0)
    return;
  winner = 0;
  nl();
  outstr("2Rolling0");
  period(5);
  mark = dice();
  if ((mark == 7) || (mark == 11)) {
    pl(" 7...4 Automatic win7!0");
    winner = 1;
  }
  if (mark == 2) {
    pl(" 7...4 Snake-Eyes7!0");
    winner = 2;
  }
  if (mark == 6)
    winner = 2;
  if (!winner) {
    pl(" 7[0 Your Mark 7]0");
    nl();
    do {
      outstr("Hit a key 7>0 ");
      top(NONE);
      getkey();
      backspace(13);
      outstr("2Rolling0");
      period(5);
      tempi = dice();
      nl();
      if (tempi == mark)
	winner = 1;
      if (tempi == 7)
	winner = 2;
    } while (!winner);
  }
  nl();
  if (winner == 1) {
    sprintf(temps,"0Congratulations7!0  You win %ld gold7!0",bet);
    pl(temps);
    gold += bet;
  }
  else {
    sprintf(temps,"0Too bad 7...0 You lose %ld gold7...0",bet);
    pl(temps);
    gold -= bet;
  }
}

void slot_machine()
{
  unsigned int machine,slot_num[4],slot_values[]= { 100,250,500,1000,2500 };

  randomize();
  nl();
  pl("4Pick slot machine:0");
  nl();
  for(winner=0; winner < 5; winner++) {
    slot_values[winner] = slot_values[winner] * info.betadjust;
    sprintf(temps,"7[3%d7]0 %4d Gold",winner+1,slot_values[winner]);
    pl(temps);
  }
  nl();
  outstr("Choose 7[013-053,0 Q3)0uit7]3 >0 ");
  menu = onek("12345Q");
  if(menu == 'Q')
    return;
  menu -= 49;
    machine = slot_values[menu];
  nl();
  done = 0;
  do {
    if(gold < machine) {
      nl();
      pl("You don't have enough gold!");
      nl();
      done = 1;
    }
    else {
      sprintf(temps,"7[0%d Gold Machine7]0 Pull Arm 7[0y3/0N7]3?0 ",machine);
      outstr(temps);
      if (yn()) {
        nl();
        slot_num[1] = pull_slot();
        slot_num[2] = pull_slot();
        slot_num[3] = pull_slot();
        if ((slot_num[1] == slot_num[2]) && (slot_num[2] == slot_num[3])) {
          switch(slot_num[1]) {
            case 0:
              winner = 8;
	      break;
            case 1:
              winner = 15;
              break;
            case 2:
	      winner = 20;
	      break;
	    case 3:
	      winner = 50;
              break;
          }
          bet = winner * machine;
          nl();
          nl();
          sprintf(temps,"4%d x %u0 7=0 You win %lu gold7!0",winner,machine,bet);
          pl(temps);
          nl();
          gold += bet;
        }
        else {
          sprintf(temps,"You lose %d gold7...0",machine);
          pl(temps);
          gold -= machine;
        }
      }
      else
        done = 1;
    }
  } while (done != 1);
}

int pull_slot()
{
  int count=1;
  static char slot_name[5][10] =
	  {  "Cherry",
	     "Lemon",
	     "Orange",
             "Bar"     };

  outstr("[");
  do {
    tempi = random(10);
    if ((tempi == 4) || (tempi == 5) || (tempi == 6))
      tempi = 0;
    if ((tempi == 7) || (tempi == 8))
      tempi = 1;
    if (tempi == 9)
      tempi = 2;
    outstr(slot_name[tempi]);
    ++count;
    if (count < 6)
      backspace(strlen(slot_name[tempi])+1);
  } while (count < 6);
  outstr("] ");
  return(tempi);
}

void dice_black()
{
  bet_amount(5000);
  if(bet == 0)
    return;
  nl();
  tempi = 0;
  done = 0;
  winner = 0;
  pl("4Player's Turn:0");
  do {
    tempi += dice();
    sprintf(temps," 7>0 Total7:3 %2d0",tempi);
    outstr(temps);
    if (tempi < 22) {
      outstr("  0H7]0it  S7]0tay 7>0 ");
      do {
        top(NONE);
        menu = getkey();
      } while ((menu != 'H') && (menu != 'h') && (menu != 'S')
        && (menu != 's'));
      backspace(16);
      nl();
      switch (menu) {
        case 'h':
        case 'H':
          done = 0;
          break;
        case 's':
        case 'S':
          done = 1;
          break;
      }
    }
  } while ((!done) && (tempi < 22));

  if (tempi > 21) {
   nl();
   nl();
    pl("Player busts...");
    winner = 2;
  }

  number = tempi;
  tempi = 0;
  if (!winner) {
    nl();
    pl("4Computer's Turn:0");
    do {
      tempi += dice();
      sprintf(temps," 7>0 Total7: 3%2d0",tempi);
      pl(temps);
    } while (tempi < 15);
  }

  if (tempi > 21) {
    nl();
    pl("Dealer busts...");
    winner = 1;
  }

  if (!winner) {
    if (number > tempi)
      winner = 1;
    else
      winner = 2;
  }
  nl();
  if (winner == 1) {
    sprintf(temps,"You win %lu gold7!0",bet);
    pl(temps);
    gold += bet;
  }
  else {
    sprintf(temps,"You lose %lu gold7...0",bet);
    pl(temps);
    gold -=bet;
  }
}


void hilo()
{
  char cheat[25];
  int first_card,count,gutsy=0;

  bet_amount(4000);
  if(bet == 0)
    return;
  player_number[0] = 0;
  count = 1;
  do {
    nl();
    get_card();
    if((count == 2) && (player_number[0])) {
      number = player_number[0];
      type = player_type[0];
    }
    first_card = number;
    outstr("4First Card7  :  0");
    find_card_name(number,type);
    nl();
    outstr("4Next Card is7:  0");
    get_card();
    player_number[0] = number;
    player_type[0] = type;
    outstr("3H7>0igher 3L7>0ower 7>0 ");
    sprintf(cheat,"First> %d  Next> %d",first_card,number);
    top(cheat);
    do {
      menu = getkey();
    } while ((menu != 'h') && (menu != 'H') && (menu != 'l')
          && (menu != 'L'));
    backspace(18);
    switch(menu) {
      case 'h':
      case 'H':
        winner = 1;
        break;
      case 'l':
      case 'L':
        winner = 0;
        break;
    }
    find_card_name(number,type);
    stay = 0;
    if(first_card < number) {
      pl("       (Higher)");
      if (winner)
        stay = 1;
    }
    if(first_card > number) {
      pl("       (Lower)");
      if(!winner)
        stay = 1;
    }
    if(first_card == number) {
      pl("       (Push6!0)");
      nl();
      pl("You lose twice your bet!");
      gold -= (bet * 2);
      return;
    }
    nl();
    if((count == 1) && (stay) && (number == 8)) {
      pl("Forced continue on the Eight...");
      nl();
      pl("Second round...");
      gutsy = 1;
    }
    if((count == 1) && (stay) && (number != 8)) {
      bet = bet / 2;
      sprintf(temps,"You've won %lu gold.  Continue? ",bet);
      outstr(temps);
      if(yn()) {
        bet = bet * 2;
        gutsy = 1;
        nl();
        pl("Second round...");
      }
    }
    ++count;
  } while((count < 3) && (gutsy));

  if(stay) {
    sprintf(temps,"You win %lu gold!",bet);
    gold += bet;
  }
  else {
    sprintf(temps,"You lose %lu gold...",bet);
    gold -= bet;
  }
  pl(temps);
}

void baccarat()
{
  bet_amount(5000);
  if(bet == 0)
    return;
  player_total = 0;

  nl();
  pl("7[0Your Hand7]3:0");
  for (done=0; done < 2; done++) {
    get_card();
    find_card_name(number,type);
    nl();
    tempi = find_value(number);
    if (tempi == 10)
      tempi = 0;
    if (tempi == 11)
      tempi = 1;
    player_total += tempi;
  }
  nl();
  if (player_total > 9)
    player_total -= 10;
  sprintf(temps,"7[0Total: %d7]0 Another card? ",player_total);
  outstr(temps);
  if (yn()) {
    get_card();
    nl();
    find_card_name(number,type);
    nl();
    tempi = find_value(number);
    if (tempi == 10)
      tempi = 0;
    if (tempi == 11)
      tempi = 1;
    player_total += tempi;
  }
  if (player_total > 9)
    player_total -= 10;
  nl();
  sprintf(temps,"Player has %d.",player_total);
  pl(temps);
  nl();
  dealer_total = 0;
  pl("7[0Dealer's Hand7]3:0");
  for (done=0; done < 2; done++) {
    get_card();
    find_card_name(number,type);
    nl();
    tempi = find_value(number);
    if (tempi == 10)
      tempi = 0;
    if (tempi == 11)
      tempi = 1;
    dealer_total += tempi;
  }
  if (dealer_total > 9)
    dealer_total -= 10;
  nl();
  if (dealer_total < 5) {
    pl("Dealer takes another card...");
    nl();
    get_card();
    find_card_name(number,type);
    tempi = find_value(number);
    if (tempi == 10)
      tempi = 0;
    if (tempi == 11)
      tempi = 1;
    dealer_total += tempi;
  }
  if(dealer_total > 9)
    dealer_total -= 10;
  nl();
  nl();
  sprintf(temps,"Dealer has %d.",dealer_total);
  pl(temps);

  nl();
  if(player_total > dealer_total) {
    sprintf(temps,"You win %lu gold!",bet);
    pl(temps);
    gold += bet;
  }
  else {
    sprintf(temps,"You lose %lu gold...",bet);
    pl(temps);
    gold -= bet;
  }
}

int playagain()
{
  if (gold < 0)
    gold = 0;
  nl();
  write_points();
  tempi = check_time();
  sprintf(temps,"7[0Gold: %.0f7] 0Play again 7[0y3/0N7]3?0 ",gold);
  outstr(temps);
  top(NONE);
  if (yn())
    return (1);
  else
    return (0);
}


void bet_amount(long high)
{
  char bets[10];

  high = high * info.betadjust;
  if (gold < 0)
    gold = 0;
  tempi = check_time();
  if ((high == 0) || (high > gold))
    high = gold;
  do {
    nl();
    ltoa(high,bets,10);
    sprintf(temps,"0Enter amount to bet 7[Max: 0%s7]0 3> ",bets);
    outstr(temps);
    input1(bets,9,2);
    bet = atol(bets);
    if (bet == 0)
      return;
  } while ((bet > high) || (bet < 0));
}

int check_registration()
{

  char right_code[20];
  int i;

  if (strlen(info.registration) < 9)
    return(0);

  i = info.bbs_name[4];
  i += info.bbs_name[3];

  strcpy(right_code,"K86");
  sprintf(temps,"%d",i);
  strcat(right_code,temps);
  strcat(right_code,"2KJ");

  if(strcmp(right_code,info.registration) == 0)
    return(1);
  else
    return(0);
}


void sysop_menu()
{
  done = 1;
  do {
    nl();
    outstr("7[0Sysop Menu7]0 Choose 3>0 ");
    menu = onek("LQ?");
    switch (menu) {
      case 'L':
        nl();
        sprintf(temps,"%s\\CASINO.LOG",info.cas_dir);
        fptr=fopen(temps,"rb");
        outchr(12);
        nl();
        nl();
        pl("TAK's Casino Log for Today:");
        nl();
        fread(&log,sizeof(log),1,fptr);
        pl("Alias                    Logged On At:  Secs On:");
        pl("------------------------------------------------");
        while(fread(&log,sizeof(log),1,fptr)==1) {
          sprintf(temps,"%-23s %8s %10d",log.user_name,log.time_begin,log.time_used);
	  pl(temps);
        }
        nl();
        fclose(fptr);
        break;
    case 'Q':
      done = 0;
      break;
    case '?':
      nl();
      nl();
      pl("TAK's Casino Sysop Menu7:");
      nl();
      pl("3L 7>0 Log of Casino Players");
      pl("3Q 7>0 Quit to Casino");
      pl("3? 7>0 This Menu");
      nl();
      break;
    }
  } while(done);
}


int check_time()
{
  long cur_time;
  int tleft_min;

  cur_time = timer();
  tleft_min = info.mins - ((cur_time - begin_time) / 60);
   if (tleft_min <= 0) {
    nl();
    nl();
    pl("Sorry!  Your Casino time is now up!");
    nl();
    pl("Thanks for playing TAK's Casino!");
    nl();
    end_session();
    exit(0);
  }
  return(tleft_min);
}

void write_new_day()
{
  struct date date;

  getdate(&date);
  sprintf(log.user_name,"%d%d%d",date.da_day,date.da_mon,date.da_year);
  log.time_used = 69;

  sprintf(temps,"%s\\CASINO.LOG",info.cas_dir);
  fptr=fopen(temps,"wb");
  fwrite(&log, sizeof(log), 1, fptr);
  fclose(fptr);
}

int compare_date()
{
  char comp_date[15];
  struct date date;

  getdate(&date);
  sprintf(comp_date,"%d%d%d",date.da_day,date.da_mon,date.da_year);
  sprintf(temps,"%s\\CASINO.LOG",info.cas_dir);
  fptr=fopen(temps,"rb");
  fread(&log,sizeof(log),1,fptr);
  fclose(fptr);
  if(strcmp(comp_date,log.user_name)==0)
    return(1);
  write_new_day();
  return(0);
}

void end_session()
{
  nl();
  nl();
  nl();
  sprintf(temps,"Returning to %s...",info.bbs_name);
  outstr(temps);
  write_points();
  strcpy(log.time_begin,timebegin);
  log.time_used = timer() - (begin_time + prev_used);
  strcpy(log.user_name, name);
  sprintf(temps,"%s\\CASINO.LOG",info.cas_dir);
  fptr=fopen(temps,"ab");
  fwrite(&log, sizeof(log), 1, fptr);
  fclose(fptr);
  nl();
}

