# Written by Ahmad Reda Bayoumy Mohamed

# This function returning true if the parameter was a signed real number, Returning false otherwise
def is_Real_Number(num):
    num = str(num)
    # Check if the number is acually a number or not by replacing every '.' to 0 then checking if it is a digit or not 
    # But we must check if its contain more than one dot or the num is just a dot and the same for the negative sign.
    if num.replace(".", "0").replace("-", '0').isdecimal() and num.count('.') < 2 and num.strip() != '.' and num.count('-') < 2 and num.strip() != '-' and "-." not in num: 
        # Checking if it contains only one '-' or not, if it contains then check if the negative sign is the first character or not
        if '-' in num:
            if num.strip()[0]  ==  '-':
                return True
            else: 
                return False
        else:
            return True         
    else:
        return False 