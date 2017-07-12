/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Mancala class declaration
Date: 04/20/2010
*/

#ifndef MANCALA_H
#define MANCALA_H

#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QIODevice>
#include "inputhi.h"
#include "hiscore1.h"
#include "mreceive.h"
#include "mconnect.h"

namespace Ui {
    class mancala;
}



class mancala : public QMainWindow {
    Q_OBJECT
public:
    mancala(QWidget *parent = 0);
    ~mancala();
     void update_display();

private slots: // linked to each of the 13 NUDGE buttons of the interface
    // Player 2 buttons
    void on_actionConnect_to_a_Server_triggered();
    void on_actionTop_Scores_triggered();
    void on_actionServer_triggered();
    void on_actionAbout_LCD_Mancala_triggered();
    void on_actionRules_and_Instructions_triggered();
    void button1pressed(); //cup 1
    void button2pressed(); // cup 2
    void button3pressed(); // cup 3
    void button4pressed(); // cup 4
    void button5pressed(); // cup 5
    void button6pressed(); // cup 6
    // Player 1 buttons
    void button7pressed(); // cup 6
    void button8pressed(); // cup 5
    void button9pressed(); // cup 4
    void button10pressed(); // cup 3
    void button11pressed(); // cup 2
    void button12pressed(); // cup 1
    void resetbutton();  // the reset button


protected:
    void changeEvent(QEvent *e);

private:
    Ui::mancala *ui;


    void reset(); // reset function, invoked when reset button is pressed
    void check_game_over(); // check game over condition after every turn
    // invoked when one player's cup is empty

    void bonus(); // check if a player is eligible for bonus
    /* triggered when the last stone from a cup gets placed into
     one of the player's own cups that is empty and the opponent's cup
     directly across from that empty cup is not empty.
     the player then captures all of the stones in opponent's cup plus
     the one stone placed in the player's own cup.  */

    // display message on the status message box in the middle
    void player1turn(); //player 1 turn
    void player2turn(); // player 2 turn
    void player1free(); // player 1 free turn
    void player2free(); // player 2 free turn
    void player1bonus(); // player 1 BONUS
    void player2bonus(); // player 2 BONUS
    void player1wins(); // player 1 victory
    void player2wins(); // player 2 victory
    void draw(); // draw

    void score_entry(QString, int); // leaderboard entry;

    // variables that store number of stones in a certain cup or mancala
    int mancala1;
    int mancala2;
    int cup11;    // cup 11 = player 1 cup 1, cup 23 = player 2 cup 3 etc.
    int cup12;
    int cup13;
    int cup14;
    int cup15;
    int cup16;
    int cup21;
    int cup22;
    int cup23;
    int cup24;
    int cup25;
    int cup26;

    int last_cup; // track where the last stone was put, for awarding bonus

    bool player_flag; // true = player 1 turn, false = player 2 turn
    bool extra_turn; // true = extra turn awarded

    bool game_active; // if the game is over, this will be false and user will be required
    // to reset the game

    QString current_user_name;
    int current_high_score;

    int high1;
    int high2;
    int high3;
    int high4;
    int high5;
    QString name1;
    QString name2;
    QString name3;
    QString name4;
    QString name5;

    QString readme_text;

    inputhi hi_score_entry;
    hiscore1 hi_score_window;
    MReceive rec;
    MConnect con;


};

#endif // MANCALA_H
