#mpirun -n 4 python3 reduce-Numpy.py 
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD

rank = comm.Get_rank()
rankF = numpy.array(float(rank))
total = numpy.zeros(1)
comm.Reduce(rankF,total, op=MPI.SUM, root=1)
print ("Reduced on 1 : rankF=", rankF, "total=", total)

comm.Allreduce(rankF, total, op=MPI.MAX)
print ("Allreduce on ", rankF, "total=", total)



