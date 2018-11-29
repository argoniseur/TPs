#mpirun -n 4 python3 reduce.py 
from mpi4py import MPI
comm = MPI.COMM_WORLD

rank = comm.Get_rank()
somme = 0

somme = comm.reduce(rank, op=MPI.SUM, root=1)
print ("Reduced on 1 : rank=", rank, "somme=", somme)

maxi = comm.allreduce(rank, op=MPI.MAX)
print ("Allreduce on ", rank, "maximum=", maxi)



