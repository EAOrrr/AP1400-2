def adjacentElementsProduct(inputArray):
    return max([inputArray[i]*inputArray[i+1] for i in range(len(inputArray)-1)])  # with help of newbing
    return inputArray[0] * inputArray[1] if len(inputArray)==2 else max(inputArray[0]*inputArray[1], adjacentElementsProduct(inputArray[1:]))

def allLongestStrings(inputArray):
    return [i for i in inputArray if len(i) == len(max(inputArray, key=len))] # save a lot of
    return [] if len(inputArray) == 0 else [s for s in [inputArray[0]] + allLongestStrings(inputArray[1:]) if len(s) == len(max([inputArray[0]] + allLongestStrings(inputArray[1:]), key=lambda s: len(s)))]

def checkPalindrome(inputString):
    return inputString == inputString[::-1]  # oh i forgot python's slice hahaha
    return True if len(inputString) <= 1 else False if inputString[0] != inputString[-1] else checkPalindrome(inputString[1:-1])

def palindromeRearranging(inputString):
    return sum([inputString.count(i)%2 for i in set(inputString)]) <= 1
    return len(list(filter(lambda x: x % 2 == 1, list(map(lambda ch: inputString.count(ch), inputString))))) <= 1

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [i if i != elemToReplace else substitutionElem for i in inputArray]
    return list(map(lambda elem: substitutionElem if elem==elemToReplace else elem, inputArray))
    # return ([inputArray[0]] if inputArray[0]!=elemToReplace else [substitutionElem]) + arrayReplace(inputArray[1:], elemToReplace, substitutionElem) if inputArray else []

def evenDigitsOnly(n):
    return all([int(i)%2==0 for i in str(n)])
    return True if n==0 else False if n % 10 % 2 else evenDigitsOnly(n//10)

def commonCharacterCount(s1, s2):
    return sum([(lambda x: min(s1.count(x), s2.count(x)))(i) for i in (set(s1).intersection(set(s2)))])  # this one seems to be faster
    # return sum([(lambda x: min(s1.count(x), s2.count(x)))(i) for i in set(s1)])

def areSimilar(A, B):
    return sorted(A) == sorted(B) and (sum([a != b for a, b in zip(A, B)]) == 0 or sum([a != b for a, b in zip(A, B)]) == 2)

def alphabeticShift(inputString):
    # return chr(ord(inputString[0])+1 if ord(inputString[0]) < ord('z') else 97) + alphabeticShift(inputString[1:]) if len(inputString) > 0 else ''
    return ''.join(list(map(lambda ch: chr(ord(ch)+1) if ch<'z'else 'a', inputString)))

def firstDigit(inputString):
    return next((int(i) for i in inputString if i.isdigit()), None)  # new bing
    # return int(next(filter(lambda x: x.isdigit(), inputString))[0])
    # return int(inputString[0]) if inputString[0].isdigit() else firstDigit(inputString[1:])


