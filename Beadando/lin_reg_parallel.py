import numpy as np
import concurrent.futures
import random
import time


n = int(input("A pontok számának megadása: "))
start = time.time()


x = np.zeros(n)
y = np.zeros(n)


print("Adatok:")
for i in range(n):
    x[i] = random.randint(1, 9)
    print(x[i])
    y[i] = random.randint(1, 9)
    print(y[i])


def calculate_sums(start, end):
    sumX, sumX2, sumY, sumXY = 0, 0, 0, 0
    for i in range(start, end):
        sumX += x[i]
        sumX2 += x[i] * x[i]
        sumY += y[i]
        sumXY += x[i] * y[i]
    return sumX, sumX2, sumY, sumXY


num_threads = 4
chunk_size = n // num_threads
thread_results = []

with concurrent.futures.ThreadPoolExecutor() as executor:

    for i in range(num_threads):
        start = i * chunk_size
        end = start + chunk_size if i < num_threads - 1 else n
        thread_results.append(executor.submit(calculate_sums, start, end))


sumX, sumX2, sumY, sumXY = 0, 0, 0, 0
for result in thread_results:
    partial_sumX, partial_sumX2, partial_sumY, partial_sumXY = result.result()
    sumX += partial_sumX
    sumX2 += partial_sumX2
    sumY += partial_sumY
    sumXY += partial_sumXY


b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX)
a = (sumY - b * sumX) / n


print("\nAz együtthatók:")
print("a: ", a)
print("b: ", b)
print("Az egyenlet: y = %0.4f + %0.4f x" % (a, b))
end = time.time()
print("\nA szamitas ideje: %0.4f" % (end-start))
