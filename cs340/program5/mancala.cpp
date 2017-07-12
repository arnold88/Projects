/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Mancala class implementation
Date: 04/29/2010
*/

#include "mancala.h"
#include "ui_mancala.h"
#include "inputhi.h"




mancala::mancala(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mancala)
{
    // startup routine
    ui->setupUi(this);
    reset();
    name1="User";
    name2="User";
    name3="User";
    name4="User";
    name5="User";
    high1=0;
    high2=0;
    high3=0;
    high4=0;
    high5=0;

}

mancala::~mancala()
{
    delete ui;
}

void mancala::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// player 2 buttons

void mancala::button1pressed() // if button at cup 21 is nudged
{

    // check for 3 condtions:
    // Is this player 2's turn?
    // Is the cup not empty?
    // Is the game still active, i.e. not over yet?
 if ( (!player_flag) && (cup21 > 0) && (game_active))
    {

     // while the cup not empty, take one stone from this cup
     // and place on to the next one
  while (cup21 > 0)
  {


      // is the next slot player 2's mancala?
      // If yes, put one stone in, if not, skip.
  if (!player_flag)
      {
   cup21--;
   mancala2++;
   if (cup21==0)
   {
       extra_turn = true;
       break;
   }
      }

  // put the stone to cup 15
   cup21--;
   cup16++;
   last_cup = 0; // track the last cup for bonus purposes, 0 means this is opponent's cup
   if (cup21==0) break; // no more stone to put? break the loop.

   cup21--;
   cup15++;\
   last_cup = 0;\
   if (cup21==0) break;

   cup21--;
   cup14++;
   last_cup = 0;\
   if (cup21==0) break;

   cup21--;
   cup13++;\
          last_cup = 0;
   if (cup21==0) break;

   cup21--;
   cup12++;\
           last_cup = 0;\
   if (cup21==0) break;

   cup21--;
   cup11++;\
           last_cup = 0;\
   if (cup21==0) break;

   if (player_flag)
       {
    cup21--;
    mancala1++;
    if (cup21==0) break;
       }

   cup21--;
   cup26++;\
           last_cup = 26;\
   if (cup21==0) break;

   cup21--;
   cup25++;\
            last_cup = 25;\
   if (cup21==0) break;

   cup21--;
   cup24++;\
           last_cup = 24;\
   if (cup21==0) break;

   cup21--;
   cup23++;\
           last_cup = 23;\
   if (cup21==0) break;

   cup21--;
   cup22++;\
           last_cup = 22;\
   if (cup21==0) break;

   last_cup=21;

  }

  bonus(); // now determine if the bonus has triggered
  update_display(); // update display for all the cups and mancalas
  player_flag = !player_flag; // invert the player flag to indicate it is opponent's turn

}

 if (extra_turn) // extra turn awarded when last stone drop into own's mancala
 {
      player_flag = !player_flag; // invert the player flag again to award one more turn
      extra_turn = false; // turn off the extra turn glaf
      player2free(); // display message in status box

 }

 check_game_over(); // check for game over

}



void mancala::button2pressed()
{

    if(!player_flag  && (cup22 > 0) && (game_active))
       {
    while (cup22 > 0)
    {
        cup22--;
        cup21++;\
                last_cup = 21;\
        if (cup22==0) break;

    if (!player_flag)
        {
     cup22--;
     mancala2++;
     if (cup22==0)
     {
         extra_turn = true;
         break;
     }
        }

     cup22--;
     cup16++;\
             last_cup = 0;
     if (cup22==0) break;

     cup22--;
     cup15++;\
             last_cup = 0;
     if (cup22==0) break;

     cup22--;
     cup14++;\
             last_cup = 0;
     if (cup22==0) break;

     cup22--;
     cup13++;\
             last_cup = 0;
     if (cup22==0) break;

     cup22--;
     cup12++;\
             last_cup = 0;
     if (cup22==0) break;

     cup22--;
     cup11++;\
             last_cup = 0;
     if (cup22==0) break;

     if (player_flag)
         {
      cup22--;
      mancala1++;
      if (cup22==0) break;
         }

     cup22--;
     cup26++;\
             last_cup = 26;\
     if (cup22==0) break;

     cup22--;
     cup25++;\
             last_cup = 25;\
     if (cup22==0) break;

     cup22--;
     cup24++;\
             last_cup = 24;\
     if (cup22==0) break;

     cup22--;
     cup23++;\
             last_cup = 23;\
     if (cup22==0) break;

    last_cup = 22;

    }

    bonus();
    update_display();
    player_flag = !player_flag;

    }

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player2free();

    }


    check_game_over();
}

void mancala::button3pressed()
{

    if(!player_flag  && (cup23 > 0) && (game_active))
       {
    while (cup23 > 0)
    {
        cup23--;
        cup22++;\
                last_cup = 22;\
        if (cup23==0) break;

        cup23--;
        cup21++;\
                last_cup = 21;\
        if (cup23==0) break;

    if (!player_flag)
        {
     cup23--;
     mancala2++;
     if (cup23==0) {
         extra_turn = true;
         break;
     }
        }

     cup23--;
     cup16++;\
             last_cup = 0;
     if (cup23==0) break;

     cup23--;
     cup15++;\
             last_cup = 0;
     if (cup23==0) break;

     cup23--;
     cup14++;\
             last_cup = 0;
     if (cup23==0) break;

     cup23--;
     cup13++;\
             last_cup = 0;
     if (cup23==0) break;

     cup23--;
     cup12++;\
             last_cup = 0;
     if (cup23==0) break;

     cup23--;
     cup11++;\
             last_cup = 0;
     if (cup23==0) break;

     if (player_flag)
         {
      cup23--;
      mancala1++;
      if (cup23==0) break;
         }

     cup23--;
     cup26++;\
             last_cup = 26;\
     if (cup23==0) break;

     cup23--;
     cup25++;\
             last_cup = 25;\
     if (cup23==0) break;

     cup23--;
     cup24++;\
             last_cup = 24;\
     if (cup23==0) break;

     last_cup = 23;
    }

    bonus();
    update_display();
    player_flag = !player_flag;

    }

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player2free();

    }

    check_game_over();
}

void mancala::button4pressed()
{
    if(!player_flag  && (cup24 > 0) && (game_active))
       {
    while (cup24 > 0)
    {
        cup24--;
        cup23++;\
                last_cup = 23;\
        if (cup24==0) break;

        cup24--;
        cup22++;\
                last_cup = 22;\
        if (cup24==0) break;

        cup24--;
        cup21++;\
                last_cup = 21;\
        if (cup24==0) break;

    if (!player_flag)
        {
     cup24--;
     mancala2++;
     if (cup24==0) {
         extra_turn = true;
         break;
        }
 }

     cup24--;
     cup16++;\
             last_cup = 0;
     if (cup24==0) break;

     cup24--;
     cup15++;\
             last_cup = 0;
     if (cup24==0) break;

     cup24--;
     cup14++;\
             last_cup = 0;
     if (cup24==0) break;

     cup24--;
     cup13++;\
             last_cup = 0;
     if (cup24==0) break;

     cup24--;
     cup12++;\
             last_cup = 0;
     if (cup24==0) break;

     cup24--;
     cup11++;\
             last_cup = 0;
     if (cup24==0) break;

     if (player_flag)
         {
      cup24--;
      mancala1++;
      if (cup24==0) break;
         }

     cup24--;
     cup26++;\
             last_cup = 26;\
     if (cup24==0) break;

     cup24--;
     cup25++;
     last_cup = 25;\
     if (cup24==0) break;

     last_cup = 24;
    }

    bonus();
    update_display();
    player_flag = !player_flag;

    }

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player2free();

    }


    check_game_over();
}

void mancala::button5pressed()
{
    if(!player_flag && (cup25 > 0) && (game_active))
       {
    while (cup25 > 0)
    {
        cup25--;
        cup24++;\
                last_cup = 24;
        if (cup25==0) break;

        cup25--;
        cup23++;
        last_cup = 23;
        if (cup25==0) break;

        cup25--;
        cup22++;
        last_cup = 22;
        if (cup25==0) break;

        cup25--;
        cup21++;\
                last_cup = 21;
        if (cup25==0) break;

    if (!player_flag)
        {
     cup25--;
     mancala2++;
     if (cup25==0) {
         extra_turn = true;
         break;
        }
 }

     cup25--;
     cup16++;\
             last_cup = 0;
     if (cup25==0) break;

     cup25--;
     cup15++;\
             last_cup = 0;
     if (cup25==0) break;

     cup25--;
     cup14++;\
             last_cup = 0;
     if (cup25==0) break;

     cup25--;
     cup13++;\
             last_cup = 0;
     if (cup25==0) break;

     cup25--;
     cup12++;\
             last_cup = 0;
     if (cup25==0) break;

     cup25--;
     cup11++;\
             last_cup = 0;
     if (cup25==0) break;

     if (player_flag)
         {
      cup25--;
      mancala1++;
      if (cup25==0) break;
         }

     cup25--;
     cup26++;\
             last_cup = 26;
     if (cup25==0) break;

             last_cup = 25;

    }

    bonus();
    update_display();
    player_flag = !player_flag;

   }

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player2free();

    }


    check_game_over();
}

void mancala::button6pressed()
{
    if(!player_flag  && (cup26 > 0) && (game_active))
       {
    while (cup26 > 0)
    {
        cup26--;
        cup25++;\
                last_cup = 25;\
        if (cup26==0) break;

        cup26--;
        cup24++;\
                last_cup = 24;\
        if (cup26==0) break;

        cup26--;
        cup23++;
        last_cup = 23;\
        if (cup26==0) break;

        cup26--;
        cup22++;
        last_cup = 22;\
        if (cup26==0) break;

        cup26--;
        cup21++;\
                last_cup = 21;\
        if (cup26==0) break;

    if (!player_flag)
        {
     cup26--;
     mancala2++;
     if (cup26==0) {
         extra_turn = true;
         break;
        }
 }

     cup26--;
     cup16++;\
             last_cup = 0;
     if (cup26==0) break;

     cup26--;
     cup15++;\
             last_cup = 0;
     if (cup26==0) break;

     cup26--;
     cup14++;\
             last_cup = 0;
     if (cup26==0) break;

     cup26--;
     cup13++;\
             last_cup = 0;
     if (cup26==0) break;

     cup26--;
     cup12++;\
             last_cup = 0;
     if (cup26==0) break;

     cup26--;
     cup11++;\
             last_cup = 0;
     if (cup26==0) break;

     last_cup = 26;

     if (player_flag)
         {
      cup26--;
      mancala1++;
      if (cup26==0) break;
         }


 }

    bonus();
 update_display();
 player_flag = !player_flag;

}
    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player2free();

    }


    check_game_over();

}

// Player 1 buttons

void mancala::button7pressed()
{
    if(player_flag  && (cup16 > 0) && (game_active))
       {
    while (cup16 > 0)
    {

     cup16--;
     cup15++;\
             last_cup = 15;
     if (cup16==0) break;

     cup16--;
     cup14++;\
             last_cup = 14;
     if (cup16==0) break;

     cup16--;
     cup13++;\
             last_cup = 13;
     if (cup16==0) break;

     cup16--;
     cup12++;\
             last_cup = 12;
     if (cup16==0) break;

     cup16--;
     cup11++;\
             last_cup = 11;
     if (cup16==0) break;

     if (player_flag)
         {
      cup16--;
      mancala1++;
      if (cup16==0) {
          extra_turn = true;
          break;
         }
  }

     cup16--;
     cup26++;\
             last_cup = 0;
     if (cup16==0) break;

     cup16--;
     cup25++;\
             last_cup = 0;
     if (cup16==0) break;

     cup16--;
     cup24++;\
             last_cup = 0;
     if (cup16==0) break;

     cup16--;
     cup23++;
     last_cup = 0;
     if (cup16==0) break;

     cup16--;
     cup22++;
     last_cup = 0;
     if (cup16==0) break;

     cup16--;
     cup21++;\
             last_cup = 0;
     if (cup16==0) break;

     last_cup = 16;

 if (!player_flag)
     {
  cup16--;
  mancala2++;
  if (cup16==0) break;
     }

 }

    bonus();
 update_display();
 player_flag = !player_flag;

 // at here, check free turn/capture/gameover condition
}

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player1free();

    }


    check_game_over();

}

void mancala::button8pressed()
{

    if(player_flag  && (cup15 > 0) && (game_active))
       {
    while (cup15 > 0)
    {
     cup15--;
     cup14++;\
             last_cup = 14;
     if (cup15==0) break;

     cup15--;
     cup13++;\
             last_cup = 13;
     if (cup15==0) break;

     cup15--;
     cup12++;\
             last_cup = 12;
     if (cup15==0) break;

     cup15--;
     cup11++;\
             last_cup = 11;
     if (cup15==0) break;

     if (player_flag)
         {
      cup15--;
      mancala1++;
      if (cup15==0) {
          extra_turn = true;
          break;
         }
  }

     cup15--;
     cup26++;\
             last_cup = 0;
     if (cup15==0) break;

     cup15--;
     cup25++;\
             last_cup = 0;
     if (cup15==0) break;

     cup15--;
     cup24++;\
             last_cup = 0;
     if (cup15==0) break;

     cup15--;
     cup23++;
     last_cup = 0;
     if (cup15==0) break;

     cup15--;
     cup22++;
     last_cup = 0;
     if (cup15==0) break;

     cup15--;
     cup21++;\
             last_cup = 0;
     if (cup15==0) break;



 if (!player_flag)
     {
  cup15--;
  mancala2++;
  if (cup15==0) break;
     }

 cup15--;
 cup16++;
 last_cup = 16;\
 if (cup15==0) break;

 last_cup = 15;

 }

    bonus();
 update_display();
 player_flag = !player_flag;


}

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player1free();

    }


    check_game_over();
}

void mancala::button9pressed()
{
    if(player_flag &&  (cup14 > 0) && (game_active))
       {
    while (cup14 > 0)
    {


     cup14--;
     cup13++;\
             last_cup = 13;
     if (cup14==0) break;

     cup14--;
     cup12++;\
             last_cup = 12;
     if (cup14==0) break;

     cup14--;
     cup11++;\
             last_cup = 11;
     if (cup14==0) break;

     if (player_flag)
         {
      cup14--;
      mancala1++;
      if (cup14==0) {
          extra_turn = true;
          break;
         }
  }

     cup14--;
     cup26++;\
             last_cup = 0;
     if (cup14==0) break;

     cup14--;
     cup25++;\
             last_cup = 0;
     if (cup14==0) break;

     cup14--;
     cup24++;\
             last_cup = 0;
     if (cup14==0) break;

     cup14--;
     cup23++;
     last_cup = 0;
     if (cup14==0) break;

     cup14--;
     cup22++;
     last_cup = 0;
     if (cup14==0) break;

     cup14--;
     cup21++;\
             last_cup = 0;
     if (cup14==0) break;

 if (!player_flag)
     {
  cup14--;
  mancala2++;
  if (cup14==0) break;
     }

 cup14--;
 cup16++;\
         last_cup = 16;
 if (cup14==0) break;

 cup14--;
 cup15++;\
         last_cup = 15;
 if (cup14==0) break;

 last_cup = 14;

 }

    bonus();
 update_display();
 player_flag = !player_flag;


}

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player1free();

    }

    check_game_over();
}

void mancala::button10pressed()
{

    if(player_flag  && (cup13 > 0) && (game_active))
       {
    while (cup13 > 0)
    {
     cup13--;
     cup12++;\
             last_cup = 12;
     if (cup13==0) break;

     cup13--;
     cup11++;\
             last_cup = 11;
     if (cup13==0) break;

     if (player_flag)
         {
      cup13--;
      mancala1++;
      if (cup13==0) {
          extra_turn = true;
          break;
         }
  }

     cup13--;
     cup26++;\
             last_cup = 0;
     if (cup13==0) break;

     cup13--;
     cup25++;\
             last_cup = 0;
     if (cup13==0) break;

     cup13--;
     cup24++;\
             last_cup = 0;
     if (cup13==0) break;

     cup13--;
     cup23++;
     last_cup = 0;
     if (cup13==0) break;

     cup13--;
     cup22++;
     last_cup = 0;
     if (cup13==0) break;

     cup13--;
     cup21++;\
             last_cup = 0;
     if (cup13==0) break;

 if (!player_flag)
     {
  cup13--;
  mancala2++;
  if (cup13==0) break;
     }

 cup13--;
 cup16++;\
         last_cup = 16;
 if (cup13==0) break;

 cup13--;
 cup15++;\
         last_cup = 15;
 if (cup13==0) break;

 cup13--;
 cup14++;\
         last_cup = 14;
 if (cup13==0) break;

 last_cup = 13;

 }

    bonus();
 update_display();
 player_flag = !player_flag;

}\

if (extra_turn)
{
     player_flag = !player_flag;
     extra_turn = false;
     player1free();

}

check_game_over();

}

void mancala::button11pressed()
{
    if(player_flag  && (cup12 > 0) && (game_active))
       {
    while (cup12 > 0)
    {

     cup12--;
     cup11++;\
             last_cup = 11;
     if (cup12==0) break;

     if (player_flag)
         {
      cup12--;
      mancala1++;
      if (cup12==0) {
          extra_turn = true;
          break;
         }
  }

     cup12--;
     cup26++;\
             last_cup = 0;
     if (cup12==0) break;

     cup12--;
     cup25++;\
             last_cup = 0;
     if (cup12==0) break;

     cup12--;
     cup24++;\
             last_cup = 0;
     if (cup12==0) break;

     cup12--;
     cup23++;
     last_cup = 0;
     if (cup12==0) break;

     cup12--;
     cup22++;
     last_cup = 0;
     if (cup12==0) break;

     cup12--;
     cup21++;\
             last_cup = 0;
     if (cup12==0) break;

 if (!player_flag)
     {
  cup12--;
  mancala2++;
  if (cup12==0) break;
     }

 cup12--;
 cup16++;\
         last_cup = 16;
 if (cup12==0) break;

 cup12--;
 cup15++;\
         last_cup = 15;
 if (cup12==0) break;

 cup12--;
 cup14++;\
         last_cup = 14;
 if (cup12==0) break;

 cup12--;
 cup13++;\
         last_cup = 13;
 if (cup12==0) break;

 last_cup = 12;

 }

    bonus();
 update_display();
 player_flag = !player_flag;

}

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player1free();

    }

    check_game_over();
}

void mancala::button12pressed()
{
    if(player_flag  && (cup11 > 0) && (game_active))
       {
    while (cup11 > 0)
    {

     if (player_flag)
         {
      cup11--;
      mancala1++;
      if (cup11==0) {
          extra_turn = true;
          break;
         }
  }

     cup11--;
     cup26++;\
             last_cup = 0;
     if (cup11==0) break;

     cup11--;
     cup25++;\
             last_cup = 0;
     if (cup11==0) break;

     cup11--;
     cup24++;\
             last_cup = 0;
     if (cup11==0) break;

     cup11--;
     cup23++;
     last_cup = 0;
     if (cup11==0) break;

     cup11--;
     cup22++;
     last_cup = 0;
     if (cup11==0) break;

     cup11--;
     cup21++;\
             last_cup = 0;
     if (cup11==0) break;

 if (!player_flag)
     {
  cup11--;
  mancala2++;
  if (cup11==0) break;
     }

 cup11--;
 cup16++;\
         last_cup = 16;
 if (cup11==0) break;

 cup11--;
 cup15++;\
         last_cup = 15;
 if (cup11==0) break;

 cup11--;
 cup14++;\
         last_cup = 14;
 if (cup11==0) break;

 cup11--;
 cup13++;\
         last_cup = 13;
 if (cup11==0) break;

 cup11--;
 cup12++;
 last_cup = 12;\
 if (cup11==0) break;

 last_cup = 11;
 }

 bonus();
 update_display();
 player_flag = !player_flag;

}

    if (extra_turn)
    {
         player_flag = !player_flag;
         extra_turn = false;
         player1free();

    }


    check_game_over();
}

void mancala::resetbutton()
{
    reset();
}


// triggered when the reset button is pressed
void mancala::reset()
{
    extra_turn = false;
    last_cup = 0;


    // set LCD display dimensions
    ui->lcdNumber11->setDigitCount(2);
     ui->lcdNumber12->setDigitCount(2);
      ui->lcdNumber13->setDigitCount(2);
       ui->lcdNumber14->setDigitCount(2);
        ui->lcdNumber15->setDigitCount(2);
         ui->lcdNumber16->setDigitCount(2);
          ui->lcdNumber21->setDigitCount(2);
           ui->lcdNumber22->setDigitCount(2);
            ui->lcdNumber23->setDigitCount(2);
             ui->lcdNumber24->setDigitCount(2);
              ui->lcdNumber25->setDigitCount(2);
               ui->lcdNumber26->setDigitCount(2);
                ui->lcdNumberM1->setDigitCount(2);
                 ui->lcdNumberM2->setDigitCount(2);

     mancala1 = 0;
     mancala2 = 0;
     cup11    = 4;
     cup12    = 4;
     cup13    = 4;
     cup14    = 4;
     cup15    = 4;
     cup16    = 4;
     cup21    = 4;
     cup22    = 4;
     cup23    = 4;
     cup24    = 4;
     cup25    = 4;
     cup26    = 4;

\
   // change this value to set who is going to go first at the start
   // true = player 1, false = player 2
   player_flag = true;

   game_active = true;
   update_display();

   if (player_flag)
   {
   player1turn();
   }
   else
   {
       player2turn();
   }

}

// update the display on the number of stones
void mancala::update_display()
{
    ui->lcdNumberM1->display(mancala1);
     ui->lcdNumber26->display(cup26);
      ui->lcdNumber25->display(cup25);
       ui->lcdNumber24->display(cup24);
        ui->lcdNumber23->display(cup23);
         ui->lcdNumber22->display(cup22);
          ui->lcdNumber21->display(cup21);
           ui->lcdNumberM2->display(mancala2);
            ui->lcdNumber16->display(cup16);
             ui->lcdNumber15->display(cup15);
              ui->lcdNumber14->display(cup14);
               ui->lcdNumber13->display(cup13);
                ui->lcdNumber12->display(cup12);
                 ui->lcdNumber11->display(cup11);

}


// status message box displays
void mancala::player1turn()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignBottom );
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 1 Turn");
}

void mancala::player2turn()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 2 Turn");
}

void mancala::player1free()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 1 awarded FREE TURN");
}

void mancala::player2free()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 2 awarded FREE TURN");
}

void mancala::player1bonus()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 2 Turn -- Player 1 collected BONUS");
    ui->statusbar->setWordWrap(true);
}

void mancala::player2bonus()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("Player 1 Turn -- Player 2 collected BONUS");
    ui->statusbar->setWordWrap(true);
}

void mancala::player1wins()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("GAME OVER! Player 1 WINS!");
}

void mancala::player2wins()
{
    ui->statusbar->setAlignment(Qt::AlignHCenter |  Qt::AlignTop);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("GAME OVER! Player 2 WINS!");
}

void mancala::draw()
{
    ui->statusbar->setAlignment(Qt::AlignCenter);
    ui->statusbar->setTextFormat(Qt::RichText);
    ui->statusbar->setScaledContents(true);
    ui->statusbar->setText("GAME OVER! This game is a draw.");
}


// check game over condition
void mancala::check_game_over()
{

    int player1sum = cup11+cup12+cup13+cup14+cup15+cup16;
    int player2sum = cup21+cup22+cup23+cup24+cup25+cup26;

    if ((player1sum == 0) || (player2sum == 0))
    {
       mancala1 = player1sum + mancala1; // add stones in own cup to mancala
       mancala2 = player2sum + mancala2;

       cup11    = 0;  // clean the cup
       cup12    = 0;
       cup13    = 0;
       cup14    = 0;
       cup15    = 0;
       cup16    = 0;
       cup21    = 0;
       cup22    = 0;
       cup23    = 0;
       cup24    = 0;
       cup25    = 0;
       cup26    = 0;

       update_display();

       if (mancala1 > mancala2) // declare victory
       {
           player1wins();

           // enter high score ONLY if higher than any of the existing five

           if (mancala1 > high1)
           {
               hi_score_entry.exec();
               name1=hi_score_entry.name;
               high1=mancala1;
           }
           else if (mancala1 > high2)
           {
               hi_score_entry.exec();
               name2=hi_score_entry.name;
               high2=mancala1;
           }
           else if (mancala1 > high3)
           {
               hi_score_entry.exec();
               name3=hi_score_entry.name;
               high3=mancala1;
           }
           else if (mancala1 > high4)
           {
               hi_score_entry.exec();
               name4=hi_score_entry.name;
               high4=mancala1;
           }
           else if (mancala1 > high5)
           {
               hi_score_entry.exec();
               name5=hi_score_entry.name;
               high5=mancala1;
           }

       }
       else if (mancala1 < mancala2)
       {
           player2wins();

           // enter high score ONLY if higher than any of the existing five

           if (mancala2 > high1)
           {
               hi_score_entry.exec();
               name1=hi_score_entry.name;
               high1=mancala2;
           }
           else if (mancala2 > high2)
           {
               hi_score_entry.exec();
               name2=hi_score_entry.name;
               high2=mancala2;
           }
           else if (mancala2 > high3)
           {
               hi_score_entry.exec();
               name3=hi_score_entry.name;
               high3=mancala2;
           }
           else if (mancala2 > high4)
           {
               hi_score_entry.exec();
               name4=hi_score_entry.name;
               high4=mancala2;
           }
           else if (mancala2 > high5)
           {
               hi_score_entry.exec();
               name5=hi_score_entry.name;
               high5=mancala2;
           }
       }
       else // mancala1 = mancala2
       {
           draw();

           // enter high score ONLY if higher than any of the existing five
           // since this is a draw, it doesn't matter which mancala we use
           // whoever enter the name will be on the score list

           if (mancala2 > high1)
           {
               hi_score_entry.exec();\
               name1=hi_score_entry.name;
               high1=mancala2;
           }
           else if (mancala2 > high2)
           {
               hi_score_entry.exec();
               name2=hi_score_entry.name;
               high2=mancala2;
           }
           else if (mancala2 > high3)
           {
               hi_score_entry.exec();
               name3=hi_score_entry.name;
               high3=mancala2;
           }
           else if (mancala2 > high4)
           {
               hi_score_entry.exec();
               name4=hi_score_entry.name;
               high4=mancala2;
           }
           else if (mancala2 > high5)
           {
               hi_score_entry.exec();
               name5=hi_score_entry.name;
               high5=mancala2;
           }
       }

       game_active = false; // requires user to reset for a new game
    }



}

// bonus checking mechanism
void mancala::bonus()
{
    if (player_flag) // player 1 bonus check
    {
        switch (last_cup) // which cup did the last stone ends?
        {
        case 11: // Player 1 cup 1 , or cup 11
            if (cup11 == 1) // if the cup 11 was previously empty
            {
               if (cup26 > 0) // if the cup across (cup 26) is not empty
                {
                   player1bonus(); // bonus message shown
               mancala1 = mancala1 + cup11 + cup26;  // add everything into own mancala
               cup11 = 0; // clear both cups
               cup26 = 0;
           }
               else // cup 26 is empty --> no bonus
               {
                   player2turn();
               }

            }
            else // last stone did not land on empty cup
            {
                player2turn();
            }
            break;

        // Everything else below use the same logic as above for each cup

        case 12:
            if (cup12 == 1)
            {
               if (cup25 > 0)
                {
                   player1bonus();
               mancala1 = mancala1 + cup12 + cup25;
               cup12 = 0;
               cup25 = 0;
               }
               else
               {
                   player2turn();
               }

            }
            else
            {
                player2turn();
            }
            break;
        case 13:
            if (cup13 == 1)
            {
               if (cup24 > 0)
                {
                   player1bonus();
               mancala1 = mancala1 + cup13 + cup24;
               cup13 = 0;
               cup24 = 0;
           }
               else
               {
                   player2turn();
               }

            }
            else
            {
                player2turn();
            }
            break;
        case 14:
            if (cup14 == 1)
            {

                    if (cup23 > 0) {
                        player1bonus();
               mancala1 = mancala1 + cup14 + cup23;
               cup14 = 0;
               cup23 = 0;
           }
                else
                    {
                    player2turn();
                }

            }
            else
            {
                player2turn();
            }
            break;
        case 15:
            if (cup15 == 1)
            {
               if (cup22 > 0)
                {
                   player1bonus();
               mancala1 = mancala1 + cup15 + cup22;
               cup15 = 0;
               cup22 = 0;
                }
               else
               {
                   player2turn();
               }


            }
            else
            {
                player2turn();
            }
            break;
        case 16:
            if (cup16 == 1)
            {
               if (cup21 > 0)
                {
                   player1bonus();
               mancala1 = mancala1 + cup16 + cup21;
               cup16 = 0;
               cup21 = 0;
                 }
               else
               {
                   player2turn();
               }

            }
            else
            {
                player2turn();
            }
            break;
         case 0:
            player2turn();
        } // end switch
    } // end player 1 bonus check
    else // player 2 bonus check
    {

        switch (last_cup)
        {
    case 21:
        if (cup21 == 1)
        {
           if (cup16 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup21 + cup16;
           cup21 = 0;
           cup16 = 0;
       }
           else
           {
               player1turn();
           }
        }
        else
        {
            player1turn();
        }
        break;
    case 22:
        if (cup22 == 1)
        {
           if (cup15 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup22 + cup15;
           cup22 = 0;
           cup15 = 0;
       }
           else
           player1turn();
        }
        else
        {
            player1turn();
        }
        break;
    case 23:
        if (cup23 == 1)
        {
           if (cup14 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup23 + cup14;
           cup23 = 0;
           cup14 = 0;
       }
           else
               player1turn();
        }
        else
        {
            player1turn();
        }
        break;
    case 24:
        if (cup24 == 1)
        {
           if (cup13 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup24 + cup13;
           cup24 = 0;
           cup13 = 0;
       }\
           else
               player1turn();
        }
        else
        {
            player1turn();
        }
        break;
    case 25:
        if (cup25 == 1)
        {
           if (cup12 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup25 + cup12;
           cup25 = 0;
           cup12 = 0;
       }
           else
               player1turn();
        }
        else
        {
            player1turn();
        }
        break;
    case 26:
        if (cup26 == 1)
        {
           if (cup11 > 0)
            {player2bonus();
           mancala2 = mancala2 + cup26 + cup11;
           cup26 = 0;
           cup11 = 0;
       }
           else
               player1turn();
        }
        else
        {
            player1turn();
        }
        break;
       case 0:
        player1turn();
    } // end switch

    }// end player 2 bonus check
}// end entire bonus check

void mancala::on_actionRules_and_Instructions_triggered()
{
  /*
   QFile readme("readme.txt");

    if (!readme.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&readme);

        while (!in.atEnd())
        {
        readme_text += in.readLine();
    }*/


       QMessageBox::about(this,tr("Instructions on using LCD Mancala"),
       tr(
               "Game mode: \n\n"
               "Choose 'single screen' to have two players using the same screen and keyboard. Choose 'Network Play' to connect to network player or to be a server. \n"
               "Note that if you going to be a server, makr sure to give your IP address and port number to your opponent to connect to. \n"
               "Also ensure that those ports are opened on your firewall, if one exist in your system. \n\n"



         "    Game rules: \n\n"

         " The goal of the game is to get more stones into your own mancala than the other player can get into his/her mancala by the end of the game. It is possible to end the game in a tie. This is when both players have 24 stones in their mancalas a the end of the game. \n\n "

          "The game will always start with Player 1's turn. Player 1's cups -- represented by a LCD display -- are located in the bottom half while Player 2's cup are the upper half. Player 1's mancala is located on the right of the board, while Player 2's on the left. \n\n "

          "The middle space is the status message box, it displays message such as whose turn it is now (player 1's turn or player 2's turn), the game is over, or if special evens occured (FREE TURN or BONUS, explained below). \n\n "

          "On a player's turn, the player selects one of his cups by hitting the 'NUDGE' button that has one or more stones in it. All of the stones in that cup are removed and they are placed one-by-one going counter-clockwise around the board into the cups or the players own mancala. A player never places a stone into the other player's mancala.\n\n "

          "Assume that a player has 12 stones in cup #3. If the player were to select that cup on his/her turn, the player would then: \n\n "

             "1. place one stone in his/her cup #2 \n"
             "2. place one stone in his/her cup #1 \n"
             "3. place one stone in his/her own mancala \n"
             "4. place one stone in the oppenent's cup #6 \n"
             "5. place one stone in the oppenent's cup #5 \n"
             "6. place one stone in the oppenent's cup #4 \n"
             "7. place one stone in the oppenent's cup #3 \n"
             "8. place one stone in the oppenent's cup #2 \n"
            " 9. place one stone in the oppenent's cup #1 \n"
            "10. place one stone in his/her cup #6 \n"
            "11. place one stone in his/her cup #5 \n\n"

         " There are two special cases that occur when the last stone from a cup is placed. \n\n"

            " 1. If the last stone from a cup gets placed into the player's own mancala, the player gets another turn. The status message box in the middle will say 'Player 1 (or player 2) FREE TURN'. \n"

             "2. If the last stone from a cup gets placed into one of the player's own cups that is empty and the opponent's cup directly across from that empty cup is not empty, the player then captures all of the stones in opponent's cup plus the one stone placed in the player's own cup. All of the captured stones are then placed directly into the player's own mancala. When this occurs, The status message box will say 'Player 1 (or player 2) collected BONUS'. \n\n"

          "The game is over when all of the cups of one of the two players have no stones in them at the end of the player's turn. Any stones left in the other player's cups are immediately moved to that player's mancala. The status message box will display 'GAME OVER' and will declare a winner or 'DRAW'' if a tie occurs. \n\n"

          "At any point in the game or after the game is over, press the 'RESET' button in the bottom to start over again."

           ));

}

void mancala::on_actionAbout_LCD_Mancala_triggered()
{

    QMessageBox::about(this, tr("About LCD Mancala V2.0"),
                       tr("LCD Mancala V2.0\nCopyright 2010 Arnold Lee. All rights reserved."));


}

void mancala::on_actionServer_triggered()
{
   rec.exec();
}

void mancala::on_actionTop_Scores_triggered()
{
    hi_score_window.name_score_entry(name1,high1,1);
    hi_score_window.name_score_entry(name2,high2,2);
    hi_score_window.name_score_entry(name3,high3,3);
    hi_score_window.name_score_entry(name4,high4,4);
    hi_score_window.name_score_entry(name5,high5,5);
    hi_score_window.exec();



}

void mancala::on_actionConnect_to_a_Server_triggered()
{
    con.exec();
}
