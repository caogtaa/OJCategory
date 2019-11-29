limit = 4000000
fibo = [1,1]
while fibo[-1] <= limit:
	fibo.append(fibo[-2]+fibo[-1])
sum([f for f in fibo if f % 2 == 0])