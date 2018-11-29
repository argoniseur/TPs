#mpirun -n 9 python3 gather.py 
from mpi4py import MPI
comm = MPI.COMM_WORLD

rank = comm.Get_rank()

local_A = rank
print ("Local_A on ", rank, "=", local_A)

comm.barrier()

global_A = comm.gather(local_A, root=0)
print ("Global_A After Gather on ", rank, "=", global_A)

comm.barrier()

global_A = comm.allgather(local_A)
print ("Global_A After AllGather on ", rank, "=", global_A)
