### manifest: where i log general progress and direction

21 jul: further migration to vector ranges. certain behavior is wonk. need to investigate further.

17 jul: migrating eval functions to use vector ranges rather than algebraic for looping. this lets me concatenate functions for different types of ranges (columns, rows, squares, etc) which i needed to do because the eval functions file was nearing 1000 lines and there was a lot of repetition. more to do in this regard.

16 jul: picking this back up somewhat. changed my formatting for legibility. continued working on n-layer stuff.

22 jun: fixed some bugs w.r.t. initialization. n-layer functions not functional at this time. remains w.i.p.

21 jun 2025: beginning functions to evaluate candidates at n-layer.

19 jun 2025: more merges. combined candidates + solutions to a single array to cut down on memory usage. can probably optimize further.

16 jun x2: fixed broken search elements; merged some similar functions. there is more to merge. there is also more to solve.

16 jun 2025: does a better job evaluating sets. there is a lot of room to streamline things. there is also room to "make it work" because it "does not work" right now (it still can only solve easier boards, need to improve its search).

15 jun 2025: can evaluate squares. have devised strategy to evaluate XOR over a set of inputs I where |I| ("n") > 2, which complies with the parity requirements i'm looking for (it's relevant for sudokus). This almost works too well, in that i'm not yet equipped to deal with some of the things it's capable of evaluating, but now I know where to start.

14 jun 2025: can now do basic evaluation on sets of rows and columns. CLI has been expanded for better unit testing.

11 jun 2025: capable of solving simple sudoku puzzles. Cannot yet evaluate more difficult puzzles i.e. candidate striking. program has taken shape; cmake has been adopted as a way to manage file counts > ~3 (it's not a hard limit, it's a preference thing). there is more to be done, but this is definitely "something".

9 Jun. 2025: correctly computes valid options "candidates"; first stage of the program is generally taking shape. Can it do anything meaningful right now? No. Does it represent an approach that I am happy with? Sort of. Ideally state evaluations should compute without branches, and right now they *almost* do, save some nagging issues.

*can one be out of their element if one does not have an element of their own?