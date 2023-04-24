# get cents
def get_cents():
    # loop to get cent
    while True:
        # try catch
        try:
            cents = float(input("Change owed: "))
            if (cents > 0):
                break
        except ValueError:
            print("Error. try again \n")
    return cents
# calculate quarters


def calculate_quarters(cents):
    # return quarters
    return cents // 0.25

# calculate dimes


def calculate_dimes(cents):
    # return quarters
    return cents // 0.10

# calculate nickels


def calculate_nickels(cents):
    # return nickels
    return cents // 0.05

# calculate pennies


def calculate_pennies(cents):
    # return pennies
    return cents // 0.01


# Ask how many cents the customer is owed
cents = get_cents()
# Calculate the number of quarters to give the customer
quarters = calculate_quarters(cents)
cents = round(cents - quarters * 0.25, 2)

# Calculate the number of dimes to give the customer
dimes = calculate_dimes(cents)
cents = round(cents - dimes * 0.10, 2)

# Calculate the number of nickels to give the customer
nickels = calculate_nickels(cents)
cents = round(cents - nickels * 0.05, 2)

# Calculate the number of pennies to give the customer
pennies = calculate_pennies(cents)
cents = round(cents - pennies * 0.01, 2)

# Sum coins
coins = round(quarters + dimes + nickels + pennies)

# Print total number of coins to give the customer
print(coins)