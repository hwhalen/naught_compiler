12/02 17:57 hunter
  I think all necessary nodes are made, and naught.bison is entirely filled in! I know that all the evaluates aren't working yet though. And I'm sure many changes are gonna be required. But the skeleton is there!

12/01 2:25PM Jordan
  Fixed the segfault with params. Need to do something about vardecl vs. terms. Maybe can't do anything before we traverse tree, but if we do the following initialization int x = 10; and then late x = x + y; the second statement will be wrong, since ID nodes and vardecl nodes have to way of sharing info at the moment. Will be on later to work more.

12/01 12:41AM hunter
  the problem you were having with the wrong evaluate function being called was because you were getting some object slicing since you were redefining a 'value' field in some of the subclasses of expr_node. this caused bad behavior. also, I wasn't sure why you were returning a reference int rather than just the int, so i changed that. if you had a good reason just let me know. also also, as i mentioned in the commit comment I switched the names of test1 and test2, since the old test2 was more basic than the old test1. just so ya know.

11/30 3:18PM Jordan
  Worked on funcdef_node. Made another test file for this. Now all types (expr, term, etc.) are no longer StrUtil. Still segfault on param list for some reason.

11/30 2:30PM Jordan
  Added functionality to some arglist and a test naught file. Added a test file for param list, but something is causing a segfault. Didn't end up changing vardecl node, not sure if we need to or not.

11/30 1:50PM Jordan
  Added a bunch of expression nodes. Should work great once evaluate is working properly. Added an ID node and am going to switch change vardecl node to use ID nodes instead.

11/30 2:48 hunter
  - maybe this logging date and time will help keep us organized. I didn't figured out why the wrong evaluate is being called, but I did a lot of work to continue the actual improvement of test2 compilation; the returned AST should be about right now. along with that I improved the printing methods for a lot of nodes. let me know if you have questions. also, try to use spaces instead of tabs if you can. 

files not staged on git:
  StrUtil.h - not relevant to our assignment, will be deleted eventually
  makefile  - hopefully no changes will be required, so not needed in repo
  yy.cc/.h  - just defines some error handling for us, maybe not added to?
