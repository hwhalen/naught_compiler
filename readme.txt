got the test2.n working better.
started work on test1.n and made expr_add_node.
If you get on before me could you try to figure out why
the wrong evaluate is getting called. Its calling evaluate
from expr_node instead of int_literal_node and I can't figure out why.
Other than that making good progress on test1.n

11/30 2:48 hunter
  - maybe this logging date and time will help keep us organized. I didn't figured out why the wrong evaluate is being called, but I did a lot of work to continue the actual improvement of test2 compilation; the returned AST should be about right now. along with that I improved the printing methods for a lot of nodes. let me know if you have questions. also, try to use spaces instead of tabs if you can. 

files not staged on git:
  StrUtil.h - not relevant to our assignment, will be deleted eventually
  makefile  - hopefully no changes will be required, so not needed in repo
  yy.cc/.h  - just defines some error handling for us, maybe not added to?
