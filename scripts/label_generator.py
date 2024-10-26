import random

LABEL_MIN = 1
LABEL_MAX = (2 ** 32) - 1
LABEL_LEN = 8
PREFIX = "$~"

while(True):
    random_number = random.randrange(LABEL_MIN, LABEL_MAX)
    random_number_hex = str(hex(random_number)[2:]).zfill(LABEL_LEN).lower()
    print(f'<a id="{PREFIX}{random_number_hex}"></a>')
    user_input = input()
    if user_input.lower() == "exit":
        break
