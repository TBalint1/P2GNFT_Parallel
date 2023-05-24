import numpy as np
import random
import time


n = int(input("A pontok számának megadása: "))
start = time.time()

x = np.zeros(n)
y = np.zeros(n)


print("Adatok")
for i in range(n):
    x[i] = random.randint(1, 9)
    print(x[i])
    y[i] = random.randint(1, 9)
    print(y[i])

sumX, sumX2, sumY, sumXY = 0, 0, 0, 0
for i in range(n):
    sumX = sumX + x[i]
    sumX2 = sumX2 + x[i]*x[i]
    sumY = sumY + y[i]
    sumXY = sumXY + x[i]*y[i]


b = (n*sumXY-sumX*sumY)/(n*sumX2-sumX*sumX)
a = (sumY - b*sumX)/n


print("\nAz együtthatók:")
print("a: ", a)
print("b: ", b)
print("Az egyenlet: y = %0.4f + %0.4f x" % (a, b))
end = time.time()
print("\nA szamitas ideje: %0.4f" % (end-start))
