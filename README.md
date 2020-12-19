# inference_engine

An implementation of the [A\*](https://en.wikipedia.org/wiki/A*_search_algorithm) algorithm (with its [greedy](https://en.wikipedia.org/wiki/Greedy_algorithm) and [uniform-cost](https://en.wikipedia.org/?title=Uniform-cost_search&redirect=no) variants) solving [N-puzzles](https://en.wikipedia.org/wiki/15_puzzle) of various sizes, as optimally as possible.

![Recordit GIF](https://i.ibb.co/s2CQNfz/ezgif-com-crop-1.gif)

## Input

```
# This puzzle is solvable
3
4 8 1
2 0 5
6 3 7
```

```
# This puzzle is unsolvable
4
 3 13  6  2
 8 12  4  1
 7  0 14 11
10  5  9 15
```

## Usage

first argument **(heurisics)**:

- 0 : Manhattan Distance _(best)_
- 1 : Hamming Distance
- 2 : Linear conflict and manhattan distance

second argument **(algorithms)**:

- a : A\*
- g : Greedy
- u : Uniform cost

third argument : Input file

```
make

./n_puzzle -0 -a puzzles/solvable/size_3x3/s33_1
```
