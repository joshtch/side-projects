:- use_module(library(csv)).

csv_read_file('poker.txt', 1000, [separator(' '), arity(10)]),
rows_to_lists(Rows, Lists).

