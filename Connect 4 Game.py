#                                                                  Connect 4 Game
# How to play?
# Players choose a symbol, either X(RED) or O(YELLOW).
# In their turn, they drop the symbol from top of the board (number 6) until it settles in the bottom empty cell. 
# See video: https://www.youtube.com/watch?v=ylZBRUJi3UQ 
# The first player to connect 4 symbols horizontally, vertically or diagonally wins.
# Done by Ahmad Reda Bayoumy

import sys

board = []
intial = []
starting_point = True

def display_board():
    global board
    global intial
    global starting_point
    # Creating board at the first time to call the function only
    while starting_point:
        for i in range(6):
            intial = []
            for j in range(7):  
                intial.append(' ')
                
            board.append(intial)
                
        starting_point = False
           
    print("")     
    for i in range(6):
        print(board[i])
    
      
    print("  1    2    3    4    5    6    7")  


def iswinner(symbol):
    
    # Check a 4 connect horizentely
    for i in range(6):
        for j in range(4):
            if board[i][j] == board[i][j+1] == board[i][j+2] == board[i][j+3] == symbol:
                return True
        
    # Check a 4 connect vertically
    for i in range(6):
        for j in range(3):
            if board[j][i] == board[j+1][i] == board[j+2][i] == board[j+3][i] == symbol:
                return True      

    # Check a 4 connect for / or \ shape
    for i in range(3):
        for j in range(6):
            # Checks a 4 connect in obligue line like that \
            if j <= 3:
                if board[i][j] == board[i+1][j+1] == board[i+2][j+2] == board[i+3][j+3] == symbol:
                    return True
            # Checks a 4 connect in obligue line like that /    
            if j >= 3:
                if board[i][j] == board[i+1][j-1] == board[i+2][j-2] == board[i+3][j-3] == symbol:
                    return True
                
    return False


# A list of counters tells you whether the column you choose is filled or not
availability = [0] * 7
def isfilled(col):
    global availability
    # If the column counter equal 6 that means it is filled    
    if availability[col-1] >= 6:
        return True
    
    # Every Time you call this function increase the counter of the column you choose by one until it become 6
    availability[col-1] += 1
    return False

# Checking if the input is valid or not
def isvalid(player, symbol):
    while True:
        if player.isdigit():
            if int(player) <= 0 or int(player) > 7:
                player = input(f"player{symbol}, Please enter a number from 1-7 in unfilled column: ")
            else:
                if isfilled(int(player)): 
                    player = input(f"player{symbol}, Please enter a number from 1-7 in unfilled column: ")
                else:
                    return player
                  
        else:
            player = input(f"player{symbol}, Please enter a number from 1-7 in unfilled column: ")
            

# Updating board
def update(symbol,col, counter = 0):
    global board
    board[6-counter][col-1] = symbol 
       

def play():
    while True:
        # Display board
        display_board()
        # input
        playerx = input("playerX, Please enter a number from 1-7 in unfilled column: ")
                 
        # isvalid
        playerx = isvalid(playerx, 'X')
        
        # update
        update('X',int(playerx),availability[int(playerx)-1])
        # iswinner
        if iswinner('X'):
            display_board()
            print("Congratulation, PlayerX you won!!")
            return 0
        elif availability == [6] * 7:
            display_board(True)
            print("Draw!.")
            return 0
    
    
        display_board()
        
        player2 = input("playerO, Please enter a number from 1-7 in unfilled column: ")
        # isfilled
        player2 = isvalid(player2, 'O')
        

        # Update the board
        update('O',int(player2),availability[int(player2)-1])
        # iswinner
        if iswinner('O'):
            display_board()
            print("Congratulation, PlayerO you won!!")
            return 0
        
        elif availability == [6] * 7:
            display_board(True)
            print("Draw!.")
            return 0
        
play()