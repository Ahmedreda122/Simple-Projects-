#                                                                    Kayles Game
#  How to play?
#  This game begins with an arbitrary number of tokens in a single row. Two players alternate turns.
#  During a turn a player may remove either one or two adjacent tokens.
#  Note that if tokens are removed from the middle of the row, then their removal creates a gap that divides the row to two parts. 
#  The player who removes the last token wins.

# The board
board = ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20']
 
# Display board function that takes zero or one or two parameters that presented the chosen tokens 
def display_board(token1 = " ", token2 = " "):
    global board
    # If there is no parameters then just display the board
    if token1 == ' ' and token2 == ' ':
        print(f'\n{board}')
    # Else if there is one chosen token then replace this token with '-' that representd that this token will be taken then display the updated board
    elif token2 == ' ':
        board[(int(token1) - 1)] = '-'
        print(f'\n{board}')
    # Else if there are two chosen tokens then replace them with '-' that representd that these tokens will be taken then display the updated board    
    else:
        board[(int(token1) - 1)] = '-'
        board[(int(token2) - 1)] = '-'
        print(f'\n{board}')
        
# This function returns true only if all tokens have been chosen or taken and tells you who play the last turn when you check it after every turn
def iswinner():
    if board == ( ["-"] * 20 ):
        return True

# Gets a valid input(s) or choice(s) then give it to the diplay_board function to replace them with '-' and update the board
def get_valid_input(turn,board, player_num):
    
    # Take the first player's choice(s) (token) and remove white spaces from it then if there is a comma(s) replace it with a space then put the two numbers that saparated with space(s) into a list and call it turn or if there is just one number put it into the list
    turn = input(f"Player{player_num}, please pick one or two adjacent numbers from 1 to 20 and saperate them with a comma or spaces: ").strip().replace(",", " ", 1)     
    
    # A loop that checks that the input list is valid
    while(True):
        
        # If the input were nothing or just a comma or spaces call the function again in order to get a valid input(s)  
        if turn == ' ' or turn == '':
            turn = input(f"Player{player_num}, please pick one or two adjacent numbers from 1 to 20 and saperate them with a comma or spaces: ").strip().replace(",", " ", 1)
        else:
            turn = turn.split()
        # if there is two inputs or choices
        if len(turn) == 2:
            # Check if the inputs are unchosen adjacent numbers between 1-20
            if (turn[0].isdigit() and turn[1].isdigit()) and (int(turn[0]) >= 1 and int(turn[0]) <= 20) and  (int(turn[1]) >= 1 and int(turn[1]) <= 20):
                if (board[int(turn[0]) - 1] != '-'  and board[int(turn[1]) - 1] != '-') and abs(int(turn[1])- int(turn[0])) == 1:
                    # if the inputs are valid send them to display board to update it (replace chosen tokens with "-") then display it 
                    display_board(turn[0], turn[1])
                    return True
            # else if there is a wrong input, request for a valid input(s) from the player again    
                else:
                    turn = input(f"Player{player_num}, please pick one or two ADJACENT numbers from UNCHOSEN numbers and saperate them with a comma or spaces: ").strip().replace(",", " ", 1) 
            else:
                turn = input(f"Player{player_num}, please pick one or two adjacent numbers from 1 to 20 and saperate them with a comma or spaces: ").strip().replace(",", " ", 1) 
                
        # else if there is a number of inputs except two              
        else:
            # Check if the input(s) is just one unchosen number between 1-20
            if turn[0].isdigit() and (int(turn[0]) >= 1 and int(turn[0]) <= 20) and len(turn) == 1:
                if board[int(turn[0]) - 1] != '-':
                    display_board(turn[0])
                    return True
            # If there is something wrong with the input or were multiple inputs request for a valid input(s) from the user again    
                else:
                    turn = input(f"Player{player_num}, please pick one or two ADJACENT numbers from UNCHOSEN numbers and saperate them with a comma or spaces: ").strip().replace(",", " ", 1)
            else:
                turn = input(f"Player{player_num}, please pick one or two adjacent numbers from 1 to 20 and saperate them with a comma or spaces: ").strip().replace(",", " ", 1)


# This function runs the play process and take valid choice(s) from the players        
def play_game():
    # First display board
    display_board()
    # loop that make players take turns until one of them wins
    while(True):
        # *PLAYER ONE*
        turn1 = ''
        # Gets a valid input(s) then pass it to display_board function
        get_valid_input(turn1, board, 1)
        
        # Checks if the last play make the board empty(does not contain numbers or unchosen tokens)             
        if iswinner():
            # If the first player play the last turn in the game then (s)he is the winnnneerrrr
            print ("Congratulation, Player 1 is the Winner!!")
            return 0
        
        # *PLAYER TWO*
        # Redoing the process above again but for the second player
        turn2 = ''
        get_valid_input(turn2, board, 2)
        
        if iswinner():
            print ("Congratulation, Player 2 is the Winner!!")
            return 0    
            
                  
play_game()