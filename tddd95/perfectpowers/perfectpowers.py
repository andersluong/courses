import math

def negative_largest_power(x):
    b = -2
    while (abs(b) < math.sqrt(abs(x))):
        for p in range(3, 33, 2):
            value = b ** p
            if value < x:
                break
            if value == x:
                return p
        b -= 1
    return 1

def positive_largest_power(x):
    for b in range(2, int(math.sqrt(x)) + 1):
        for p in range(2, 33):
            value = b ** p
            if value > x:
                break
            if value == x:
                return p
    return 1

def main():
    while True:
        x = int(input())
        if x == 0:
            break
        if x > 0:
            print(positive_largest_power(x))
        else:
            print(negative_largest_power(x))

if __name__ == "__main__":
    main()
