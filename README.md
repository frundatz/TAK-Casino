# TAK-Casino
A game that I wrote in C when I was a teenager for the WWIV BBS system in 1991. Has several casino-style games including Blackjack, Craps, Dice, Coin Flip, High-Low, Roulette, Slot Machine and Baccarat

**Original Documentation from 1991**


                               T   A   K   '   s

                                 C a s i n o !

                  (C) 1991 Frank Rundatz, All Rights Reserved.

                           Installation Documentation

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    Unzip file TAKCAS.ZIP in your main BBS directory.  Run the tcinst.bat
file.  This will create a CASINO directory off of your main BBS directory,
and copy all necessary files there.

    TCINST.BAT will then run a program called Setup.Exe, which will ask you
a series of questions which can be changed at any time later by running
Setup.Exe again.  The questions it will ask you are:

1)  Registration Number:
      If you have registered your copy of TAK's Casino and have a valid
      registration number, place it here.  You will then be able to change
      some other options.
2)  BBS Name:
      This is asking the name of your BBS.  If you have your copy of TAK's
      Casino registered, type it in exactly as you sent it to me, or you
      registration code will not work.
3)  Cheating Option:
      In the registered (ONLY) version of TAK's Casino, there is an option
      whereby the local terminal displays a one-line window at the top of the
      screen when a user is playing a game.  This will enable the sysop to
      certain advantageous things, and amaze users with their amazing "luck".
4)  Monitor:
      Because of two windows that TAK's Casino creates at the top of the
      screen, it is necessary to know your monitor type (either monochrome
      or color) so that the writes can be done as quickly as possible.
5)  Minutes Per Day:
      This allows you to set the maximum minutes per DAY that a user can use
      TAK's Casino.  Once their time is up, they will not be allowed in till
      the following day.
6)  Betting Adjustment:
      I'm sure there are BBS's out there with a different gold standard than
      I have (for instance, getting 1,000 gold on my system is not a big deal
      to say the least, but on others, getting 5 gold is a tremendously big
      deal.)  To compensate for this, enter a number in the betting adjustment
      slot.  This will cause all maximum bets to be multiplied by this number.
      So, putting a .01 will cause all maximum bets to be only 1% of their
      "real" values.  Experiment around with this till you find the BA that's
      right for you.


(Note:  Starting in version 1.08, you may not run the Setup.Exe program
        remotely, unless you use the /R switch.  This is so that things are
        printed out much quicker when running the program locally.  You may
        use the /R switch either when running TCINST.BAT or when using
        SETUP.  [Such as: "SETUP /R" or "TCINST /R"])


                          S y s o p   M e n u

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

     While in TAK's Casion, entering the "*" command will give you access to
a sysop menu (only those with 100 SL or greater are allowed access.)  There
are only two options here.  One is view the setup, allowing you to view the
values that were made with the setup program.  The other is the Casino Log.
This will tell you who logged on to the casino, and at what time, and how many
seconds they stayed in the casino.  The log is automatically reset every day,
so there is NO maintenance required whatsoever on the sysop's part.  TAK's
Casino is FULLY automatic.


                                  Special Keys

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

     While a user is online, there are certain keys that you may press to
control different things.  Here is a list of these keys:

 F1 - Show Menu (List of Special Keys)
 F5 - Boot user out of the game
 F7 - Take one minute away from user
 F8 - Give user one more minute
F10 - Enter Chat Mode

  (Note:  With the exception of F1, these keys serve the same functions as they
          do with WWIV.)

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

  That's about it.  If you have any suggestions/comments/complains, either
  send mail to WWIV-Link 1@12551 or give The Knights of Olde BBS a call at
  (215)/453-0376.

                                     The Archaic Knight
                                     WWIV-Link 1@12551

  Please Note:  Currently, with TAK's Casino v1.00, it is necessary to install
                a mod into the source code of WWIV, so that gold earned in the
                casino is transferred back to the person's account on your BBS.
                If this is a problem, please contact me and let me know, and
                I'll consider writing the next version to have it as an op-
                tional step.


Revisions:
---------

  1.00    ->      April  5th, 1991.  First release.
  1.05    ->      April  9th, 1991.  Added "special" keys functions.
  1.06    ->      April 12th, 1991.  CASINO.EXE 4k smaller w/ more functions.
  1.07    ->        May 20th, 1991.  Added configurable Casino directory.
  1.08    ->        May 24th, 1991.  Re-Wrote Setup program.
