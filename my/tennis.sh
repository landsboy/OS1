#!/bin/bash
#Netanel Landesman 315873588

# This method prints the board of the game:
board_printing () {
    # print the score of both players:
    echo " Player 1: $1         Player 2: $2 "
    # print the board:
    echo " --------------------------------- "
    echo " |       |       #       |       | "
    echo " |       |       #       |       | "
    # print the current position of the ball according to the state of the game:
    case $3 in
        3)
        echo " |       |       #       |       |O"
        ;;
        2)
        echo " |       |       #       |   O   | "
        ;;
        1)
        echo " |       |       #   O   |       | "
        ;;
        0)
        echo " |       |       O       |       | "
        ;;
        -1)
        echo " |       |   O   #       |       | "
        ;;
        -2)
        echo " |   O   |       #       |       | "
        ;;
        -3)
        echo "O|       |       #       |       | "
        ;;
    esac
    echo " |       |       #       |       | "
    echo " |       |       #       |       | "
    echo " --------------------------------- "
    # print the guess of the player (after the first turn)
    if $flag; then
        echo -e "       Player 1 played: ${num1}\n       Player 2 played: ${num2}\n\n" 
    fi
}

# This method checks if the game is over:
check_game_end () {
# First option - the ball is out:
    if [ $3 == 3 ]; then
        echo "PLAYER 1 WINS !"
        exit
    elif [ $3 == -3 ]; then
        echo "PLAYER 2 WINS !"
        exit
    fi
    
# Second option - one of the players with 0 points:
    if [ $2 == 0 ] && [ $1 -gt 0 ]; then
        echo "PLAYER 1 WINS !"
        exit
    elif [ $1 == 0 ] && [ $2 -gt 0 ]; then
        echo "PLAYER 2 WINS !"
        exit
    fi

# Third option - the 2 players with 0 points:
    if [ $1 == 0 ] && [ $2 == 0 ]; then
        if [ $3 -gt 0 ]; then
            echo "PLAYER 1 WINS !"
            exit
        elif [ $3 -lt 0 ]; then
            echo "PLAYER 2 WINS !"
            exit
        elif [ $3 == 0 ]; then
            echo "IT'S A DRAW !"
            exit
        fi
    fi
}

# This method receives input from the users and checks their validness, and updates the game state accordingly:
get_users_inputs () {
    while true; do
        echo "PLAYER 1 PICK A NUMBER: "
        read -s num1
        if [[ ! $num1 =~ ^[0-9]+$ || $num1 -lt 0 || $num1 -gt $1 ]]; then
            echo "NOT A VALID MOVE !"
        else
            break
        fi
    done
    while true; do
        echo "PLAYER 2 PICK A NUMBER: "
        read -s num2
        if [[ ! $num2 =~ ^[0-9]+$ || $num2 -lt 0 || $num2 -gt $1 ]]; then
            echo "NOT A VALID MOVE !"
        else
            break
        fi
    done
    if [ $num1 -gt $num2 ]; then
        if [ $3 -gt 0 ]; then
            state=$[$3+1]
        else
            state=1
        fi
    elif [ $num2 -gt $num1 ]; then
        if [ $3 -lt 0 ]; then
            state=$[$3-1]
        else
            state=-1
        fi
    fi
}

flag=false
state=0
p1_score=50
p2_score=50
board_printing $p1_score $p2_score $state
flag=true
# continue game until stop
while true; do
    check_game_end $p1_score $p2_score $state
    get_users_inputs $p1_score $p2_score $state
    p1_score=$[$p1_score-$num1]
    p2_score=$[$p2_score-$num2]
    board_printing $p1_score $p2_score $state
done

