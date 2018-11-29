#mpirun -n 4 python3 dotProductParallel.py 20
from mpi4py import MPI
import sys
import random

# computes the dot product of x.y
def dotproduct(x,y):
	d = 0
	for xi in range(len(x)):
		d = d + x[xi]*y[xi]
	return d

# split a vector "x" in "size" part, each of them having "n" elements
def split(x, n, size):
	return [x[n*i:n*(i+1)] for i in range(size)]
	
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

#read from command line
n = int(sys.argv[1])    #length of vectors

#arbitrary example vectors, generated to be evenly divided by the number of
#processes for convenience
local_n = 0 
x = []
y = []
xsplitted=[]
ysplitted=[]


if rank == 0:
	for i in range(1,n+1):
		x.append(random.randint(1,100))
		y.append(random.randint(1,100))
	print ("X=", x)
	print ("Y=", y)
	if(n % size != 0):
		print ("the number of processors must evenly divide n.")
		comm.Abort()
	local_n = int(n/size)
	#divide up vectors
	#xsplitted = [x[local_n*i:local_n*(i+1)] for i in range(size)]
	xsplitted = split(x, local_n, size)
	ysplitted = split(y, local_n, size)

# scatter the vector to the other nodes 
local_x = comm.scatter(xsplitted, root=0)
local_y = comm.scatter(ysplitted, root=0)
print("Processus ", rank, "has vector X=", local_x, "and Y=", local_y)

#local computation of dot product
local_dot = dotproduct(local_x, local_y)

#sum the results of each
dot = comm.reduce(local_dot, op = MPI.SUM, root=0)

if (rank == 0):
                print ("The dot product is", dot, "computed in parallel")
