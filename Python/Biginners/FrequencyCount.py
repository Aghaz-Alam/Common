#frequency count
#{}      # dictionary
def main():
    arr = [1, 2, 2, 3, 1, 4, 2]

    freq = {}

    for x in arr:
        if x in freq:
            freq[x] += 1
        else:
            freq[x] = 1
    print(freq)


if __name__ == "__main__":
    main()

""" 
Output:
{1: 2, 2: 3, 3: 1, 4: 1}
"""





#[]      # list
def main():
    matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ]

    for row in matrix:
        for val in row:
            print(val, end=" ")
        print()     
if __name__ == "__main__":
    main()  

'''
🖥 Output   
1 2 3
4 5 6
7 8 9
'''



#()      # tuple
def main():
    point = (3, 4)

    x, y = point

    print("X:", x)
    print("Y:", y)  
if __name__ == "__main__":
    main()  

''' 
🖥 Output   
X: 3
Y: 4
''' 

