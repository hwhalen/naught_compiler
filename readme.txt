12/03 9:39PM Jordan
  Started working on splitting up long expressions. Going really well. Couldn't figure out how to get a static int going so all temp variables
are not very unique. But other than that expressions are splitting up correctly.

12/02 20:20 hunter
  added in a "run_all_tests" bash file to run "comp" on all files in the test directory

12/02 18:32 hunter
  removed all dependencies on StrUtil, you can delete it if you want. This requires updating the makefile though, so I've added it to the repo. Also removed some of my older, no longer relevant comments in this readme.

12/02 17:57 hunter
  I think all necessary nodes are made, and naught.bison is entirely filled in! I know that all the evaluates aren't working yet though. And I'm sure many changes are gonna be required. But the skeleton is there!

12/01 2:25PM Jordan
  Fixed the segfault with params. Need to do something about vardecl vs. terms. Maybe can't do anything before we traverse tree, but if we do the following initialization int x = 10; and then late x = x + y; the second statement will be wrong, since ID nodes and vardecl nodes have to way of sharing info at the moment. Will be on later to work more.

12/01 12:41AM hunter
  the problem you were having with the wrong evaluate function being called was because you were getting some object slicing since you were redefining a 'value' field in some of the subclasses of expr_node. this caused bad behavior.

11/30 3:18PM Jordan
  Worked on funcdef_node. Made another test file for this. Now all types (expr, term, etc.) are no longer StrUtil. Still segfault on param list for some reason.

11/30 2:30PM Jordan
  Added functionality to some arglist and a test naught file. Added a test file for param list, but something is causing a segfault. Didn't end up changing vardecl node, not sure if we need to or not.

11/30 1:50PM Jordan
  Added a bunch of expression nodes. Should work great once evaluate is working properly. Added an ID node and am going to switch change vardecl node to use ID nodes instead.

files not staged on git:
  yy.cc/.h  - just defines some error handling for us, maybe not added to?
