#mpirun -n 9 python3 bcast.py 
from mpi4py import MPI
comm = MPI.COMM_WORLD

rank = comm.Get_rank()

if rank == 0:
	A = [1.,2.,3., 4.,5.,6., 7.,8.,9.]
else:
	A = None
	
local_A = comm.bcast(A, root=0)
print ("Local_A on ", rank, "=", local_A)


