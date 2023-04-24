# TODO
# func count letter

def count_letters(text):
    # letter counter
    letters = 0
    # loop between frist and last letter
    for i in range(len(text)):
        # if is alpha add counter
        if text[i].isalpha():
            letters += 1
    return letters

# func count words


def count_words(text):
    # words counter
    words = 1
    # loop between frist and last letter
    for i in range(len(text)):
        # if is space add counter
        if (text[i] == " "):
            words += 1
    return words

# func count sentences


def count_sentences(text):
    sentences = 0
    # loop between frist and last letter
    for i in range(len(text)):
        # if is space add counter
        if (text[i] in ".!?"):
            sentences += 1
    return sentences


# get text
text = str(input("Text: "))

# use function
l = count_letters(text)
w = count_words(text)
s = count_sentences(text)

# factor quantity will make the text simulate have 100 words
factor = 100 / w
# simulate value
l *= factor
# simulate value
s *= factor
# the Coleman-Liau index
grade = round(0.0588 * l - 0.296 * s - 15.8)

# if grate between 1 and 16 print grade
if (grade > 0 and grade < 17):

    print(f"Grade %i\n", grade)

# less than 1 print before grade 1
elif (grade < 1):
    print("Before Grade 1\n")

# greater 16+
else:
    print("Grade 16+\n")
