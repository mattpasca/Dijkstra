import numpy as np
import ctypes as ct
import igraph as ig
import matplotlib.pyplot as plt

shared_library = ct.CDLL('./dijkstra.so')
shared_library.dijkstra.argtypes = [
    ct.POINTER(ct.c_int),
    ct.c_int,
    ct.c_int,
    ct.c_int
    ]
shared_library.dijkstra.restype = ct.POINTER(ct.c_int)
shared_library.free_pointer.argtype = ct.POINTER(ct.c_int)
shared_library.free_pointer.restype = None

n_vertices = 4
edges = [(0, 1), (1, 2), (2, 3)]
graph = ig.Graph(n_vertices, edges)

matrix = np.array(graph.get_adjacency(), dtype=np.int32)
matrix_ptr = matrix.ctypes.data_as(ct.POINTER(ct.c_int))

path_ptr = shared_library.dijkstra(matrix_ptr, n_vertices, 0, 3)
path = np.ctypeslib.as_array(path_ptr, shape=(n_vertices,))
print(path)

fig, ax = plt.subplots()
ig.plot(
    graph,
    target=ax,
    vertex_size=7,
    edge_width=0.7
)
plt.show()

shared_library.free_pointer(path_ptr)
