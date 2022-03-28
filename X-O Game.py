# Welcome to X-O Game, written by Ahmad Reda Bayoumy Mohammed
# The first player to play will be PlayerX and will play with symbol X,The second one to play will be PlayerO
# Once you press RUN, the board will appear and you will choose number from 1 to 9, if you enter something else the game will re-asking you for a valid number.
# This game INSPIRED BY Dr.Mohammed El-Ramly's PSEUDOCODE.

board = ['1', '2' , '3' , '4', '5', '6', '7', '8', '9']
def display_board(symbol, move):
    if (move != "null"):
        board[move-1] = symbol
    
    print (f"-------------")
    print (f"| {board[0]} | {board[1]} | {board[2]} |") 
    print (f"| {board[3]} | {board[4]} | {board[5]} |")        
    print (f"| {board[6]} | {board[7]} | {board[8]} |")         
    print (f"-------------")

def iswinner():
    # Checking the rows
    for i in range(0, 9, 3):
        if((board[i] == board[i+1]) and (board[i+1] == board[i+2])):
            return True
    # Checking for colums
    for j in range(0, 3, 1):
        if((board[j] == board[j+3]) and (board[j+3] == board[j+6])):
            return True
    # Checking for / \ winning status
    if((board[0] == board[4]) and (board[4] == board[8])):
        return True
    elif((board[2] == board[4]) and (board[4] == board[6])):
        return True

    return False

def play_game():
    nactions = 0
    display_board("", "null")
    while(nactions != 9):
        movex = input("PlayerX, Please choose a number from 1-9 to play the game: ")
        while(True):
            if(movex.isdigit() and int(movex) <= 9 and int(movex) >= 1):
                if board[int(movex)-1] != 'X' and board[int(movex)-1] != 'O':
                   break 
                else:
                    movex = input("Please, choose an unchosen number between 1-9: ")   
            else:
                movex = input("Please, choose an unchosen number between 1-9: ")   
 
        movex = int(movex)           
        display_board("X", movex)

        if(iswinner()):
            print("PlayerX is the winner!!")
            return 0

        nactions += 1

        if(nactions == 9):
            print("Draw.")
            return 1

        moveo = input("PlayerO, Please choose a number from 1-9 to play the game: ")
        while(True):
            if(moveo.isdigit() and int(moveo) <= 9 and int(moveo) >= 1):
                if board[int(moveo)-1] != 'O' and board[int(moveo)-1] != 'X':
                    break               
                else:
                    moveo = input("Please, choose an unchosen number between 1-9: ")
            else:
                moveo = input("Please, choose an unchosen number between 1-9: ")

        moveo = int(moveo) 
        display_board("O", moveo)

        if(iswinner()):
            print("PlayerO is the winner!!")
            return 0
        nactions += 1

      
play_game()
