#                                                                  Connect 4 Game
# How to play?
# Players choose a symbol, either X(RED) or O(YELLOW).
# In their turn, they drop the symbol from top of the board (number 6) until it settles in the bottom empty cell. 
# See video: https://www.youtube.com/watch?v=ylZBRUJi3UQ 
# The first player to connect 4 symbols horizontally, vertically or diagonally wins.
# Done by Ahmad Reda Bayoumy
# Requirments:
# Installing python and pygame library:
#   pip install pygame

import pygame
from pygame.locals import *
import pygame.locals
from pygame import gfxdraw
import sys
import time


board = []
intial = []
starting_point = True 

# To use pygame's functionality.
pygame.init()
# colors
red = (232, 19, 19)
blue = (27, 36, 166)
black = (25, 25 ,25)
yellow = (255, 233, 0)
white = (245, 245, 245)
# create the background of window
surface = pygame.display.set_mode((780,778))


def display_popup(player_symbol):
    #Time to see last turn on the screen
    time.sleep(0.4)
    # Creating the popup window
    popup_window = pygame.display.set_mode((280,100))
    # Set its background color to a nice white
    popup_window.fill(white)
    # Add a title of the popup
    pygame.display.set_caption('Congratulation!!')
    # Setting the text font and its color and its mode
    font2 = pygame.font.SysFont("calibri", 16)
    # If parameter was RED or YELLOW Say congratulation to the parameter value
    if player_symbol == 'RED' or player_symbol == 'YELLOW':
        text2 = font2.render(f"Congratulation, Player{player_symbol} you won!!", True, (12,7,5))
    # Else if the parameter was DRAW, Say Draw to the players    
    else:
        # Add a title of the popup
        pygame.display.set_caption('Draw!.')
        text2 = font2.render(f"{player_symbol}", True, (12,7,5))   
        
    # Creating a rectangle to copy the text into it
    text2Rect = text2.get_rect()
    text2Rect.center = (140, 50)
    # Printing the Text in the window
    popup_window.blit(text2, text2Rect)
    # Updating the window
    pygame.display.update()
    # If the exit button pressed close the program
    while True:
        for event in pygame.event.get():
            if event.type == pygame.locals.QUIT:
                pygame.quit()
                sys.exit(0)

def ui_board():
    # colorize the background
    surface.fill((27, 36, 166))
    # To draw circles horizontally, the primary value of y-coordinate(From the left) of the circle
    basew = 75
    # To draw circles vertically,  the primary value of X-coordinate(From the top) of the circle
    baseh = 75
    # If you want how to placing circles onto a spacific position, please visit https://www.petercollingridge.co.uk/tutorials/pygame-physics-simulation/drawing-circles/ 
    for j in range(6):
        for i in range(7):
            pygame.event.get()
            # to draw a smooth circle
            gfxdraw.filled_circle(surface, basew, baseh, 40, black)    
            gfxdraw.aacircle(surface, basew, baseh, 40, black) 
            
            basew = basew + 105
        basew = 75
        baseh = baseh + 95
        
    # Set the pygame window name
    pygame.display.set_caption('Connect 4 Game')
    # Create a font object, 1st parameter is the font file, which is present in pygame, 2nd parameter is size of the font
    font = pygame.font.Font('freesansbold.ttf', 32)
    # Create a text surface object, on which text is drawn on it.
    text = font.render('                 1          2          3          4          5          6          7             ', True, white)
    
    # Copying the text surface object to the display surface object at the center coordinate.
    textRect = text.get_rect()
    textRect.center = (375, 650)
    # Printing text on the text rectangle which on the surface
    surface.blit(text, textRect)
    # Updating the board (Appling changes)
    pygame.display.update()

def display_board(display):
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
    # printing board(or updated board)
    if display:  
        print("")  
        for i in range(6):
            print(board[i])
        
        print("  1    2    3    4    5    6    7")  


def iswinner(symbol):
    
    # check a 4 connect horizentely
    for i in range(6):
        for j in range(4):
            if board[i][j] == board[i][j+1] == board[i][j+2] == board[i][j+3] == symbol:
                return True
        
    # check a 4 connect vertically
    for i in range(6):
        for j in range(3):
            if board[j][i] == board[j+1][i] == board[j+2][i] == board[j+3][i] == symbol:
                return True      

    # check a 4 connect for / or \ line
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

# Updating board
def update(symbol,col, counter = 0):
    global board
    board[6-counter][col-1] = symbol
    # Handles pygame events
    pygame.event.pump()
    
    if symbol == 'X':
        gfxdraw.filled_circle(surface, (75 + ((col-1) * 105)), (75 + ((6-counter) * 95)), 40, red) 
        gfxdraw.aacircle(surface, (75 + ((col-1) * 105)), (75 + ((6-counter) * 95)), 40, red)   
        pygame.display.update()
    elif symbol == 'O':
        gfxdraw.filled_circle(surface, (75 + ((col-1) * 105)), (75 + ((6-counter) * 95)), 40, yellow)
        gfxdraw.aacircle(surface, (75 + ((col-1) * 105)), (75 + ((6-counter) * 95)), 40, yellow)       
        pygame.display.update()
        
        
def play():
    # Setting text info
    font1 = pygame.font.Font('freesansbold.ttf', 18)
    text1 = font1.render(None, True, blue)
    text1Rect = text1.get_rect()
    text1Rect.center = (25, 720)
    #creating board
    display_board(False)
    #displaying GUI board
    ui_board()
    
    while True:
        #Hiding the previous text then updating it with the new one (second text)
        text1 = font1.render("PlayerYELLOW, Please press a number from 1-7 in unfilled column: ", True, blue, blue)
        surface.blit(text1, text1Rect)
        
        text1 = font1.render("PlayerRED, Please press a number from 1-7 in unfilled column: ", True, white)
        surface.blit(text1, text1Rect)
        pygame.display.update()
        
        # Takes the input(the column position) from the player
        running = True
        while running: 
            for event in pygame.event.get():
                # If you press a key from the keyboard, listening to the numbers from top row and keypad in the keyboard this store his chosen column in playerx if the column is not filled
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1 or event.key == pygame.K_KP1: 
                        playerx = '1'
                        # Checks whether the column you choose is filled or not
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_2 or event.key == pygame.K_KP2:
                        playerx = '2'
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_3 or event.key == pygame.K_KP3:
                        playerx = '3'
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_4 or event.key == pygame.K_KP4:
                        playerx = '4'
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_5 or event.key == pygame.K_KP5:
                        playerx = '5'
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_6 or event.key == pygame.K_KP6:
                        playerx = '6'
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_7 or event.key == pygame.K_KP7:
                        playerx = '7'  
                        if isfilled(int(playerx)):
                            continue  
                        else:
                            running = False   
                                      
                if event.type == pygame.locals.QUIT:
                    pygame.quit()
                    sys.exit(1)
                  
            
        #  update
        update('X',int(playerx),availability[int(playerx)-1])
        #  iswinner
        if iswinner('X'):
            display_board(True)
            print("Congratulation, PlayerX(Red) you won!!")
            display_popup('RED')
        # Checks if availability counters is full (equal 6) this means that all positions in the board are played and the result is DRAW      
        elif availability == [6] * 7:
            display_board(True)
            print("Draw!.")
            display_popup('Draw!.')

        # Hiding the previous text then updating it with the new one (second text)
        text1 = font1.render("PlayerRED, Please press a number from 1-7 in unfilled column: ", True, blue, blue)
        surface.blit(text1, text1Rect)
        
        text1 = font1.render("PlayerYELLOW, Please press a number from 1-7 in unfilled column:", True, white)
        surface.blit(text1, text1Rect)
        pygame.display.update()
        
        # Takes the input(the column position) from the player
        running = True
        while running : 
            for event in pygame.event.get():
                # If you press a key from the keyboard, listening to the numbers from top row and keypad in the keyboard this store his chosen column in player2 if the column is not filled
                if event.type == pygame.KEYDOWN:   
                    if event.key == pygame.K_1 or event.key == pygame.K_KP1: 
                        player2 = '1'
                        # Checks whether the column you choose is filled or not
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_2 or event.key == pygame.K_KP2:
                        player2 = '2'
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                                    
                    elif event.key == pygame.K_3 or event.key == pygame.K_KP3:
                        player2 = '3'
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_4 or event.key == pygame.K_KP4:
                        player2 = '4'
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_5 or event.key == pygame.K_KP5:
                        player2 = '5'
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_6 or event.key == pygame.K_KP6:
                        player2 = '6'
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False
                            
                    elif event.key == pygame.K_7 or event.key == pygame.K_KP7:
                        player2 = '7'  
                        if isfilled(int(player2)):
                            continue  
                        else:
                            running = False   
                                      
                if event.type == pygame.locals.QUIT:
                    pygame.quit()
                    sys.exit(1)
                    
        #  update
        update('O',int(player2),availability[int(player2)-1])
        #  iswinner
        if iswinner('O'):
            display_board(True)
            print("Congratulation, PlayerO(Yellow) you won!!")
            display_popup('YELLOW')
        # Checks if availability counters is full (equal 6) this means that all positions in the board are played and the result is DRAW      
        elif availability == [6] * 7:
            display_board(True)
            print("Draw!.")
            display_popup('Draw!.')
              
   
play()
