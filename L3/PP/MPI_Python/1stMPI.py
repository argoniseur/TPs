#passRandomDraw.py
#mpirun -n 2 python3 1stMPI.py
import random
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = random.randint(1,10)

if rank == 1:
        print ("Process", rank, "drew the number", randNum)
        comm.send(randNum, dest=0)

if rank == 0:
        print ("Process", rank, "before receiving has the number", randNum)
        randNum = comm.recv(source=1)
        print ("Process", rank, "received the number", randNum)
