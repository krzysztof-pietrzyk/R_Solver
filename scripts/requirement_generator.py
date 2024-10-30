import sys

REQ_NAME = sys.argv[0]
COMPONENT = REQ_NAME.split(" ")[0].capitalize()

anchor = "req-" + REQ_NAME.replace(" ", "-").lower()
result = \
f'''\page Requirements_{COMPONENT} Requirements: {COMPONENT}

\\anchor {anchor}
|\\ref {anchor} {REQ_NAME}|
|:-|
|Example introduction.|
|\\anchor {anchor}-a \\ref {anchor}-a "a." Example point.|
|\\anchor {anchor}-b \\ref {anchor}-b "b." Example point.|
|\\anchor {anchor}-c \\ref {anchor}-c "c." Example point.|
|\\anchor {anchor}-d \\ref {anchor}-d "d." Example point.|
|\\anchor {anchor}-e \\ref {anchor}-e "e." Example point.|
|\\anchor {anchor}-f \\ref {anchor}-f "f." Example point.|
|\\anchor {anchor}-g \\ref {anchor}-g "g." Example point.|
|\\anchor {anchor}-h \\ref {anchor}-h "h." Example point.|
|\\anchor {anchor}-i \\ref {anchor}-i "i." Example point.|
|\\anchor {anchor}-j \\ref {anchor}-j "j." Example point.|
'''

print(result)
