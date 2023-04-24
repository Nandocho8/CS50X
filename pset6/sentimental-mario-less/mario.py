# loop get number between 1 - 8
while True:
    # try catch exception
    try:
        n = int(input("Height: "))
        if (n > 0 and n < 9):
            break
    except ValueError:
        print("error")

# loop print
for i in range(1, n+1):
    print(" "*(n-i)+"#"*(i))