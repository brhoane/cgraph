# Default target.  If you change this, you must make sure that
# 'make strbuf-d' and 'make strbuf' compile as expected before
# you hand in your files.
default:
	$(MAKE) cgraph

# The *.dSYM directories will not exist on Linux, but rm -rf
# should tolerate that.
#clean:
#	-rm -rf strbuf-d strbuf-d.dSYM strbuf strbuf.dSYM

cgraph : cgraph.c util.c cgraph-test.c cgraph.h
	$(CC) -g -Wall -Wextra -Werror -std=gnu99 -pedantic \
	-I/usr/include/SDL -lSDL \
	  -o cgraph util.c cgraph.c cgraph-test.c

cgraph-d : cgraph.c cgraph-test.c
	$(CC) -DDEBUG -g -Wall -Wextra -Werror -std=c99 -pedantic \
	  -o cgraph util.c cgraph.c cgraph-test.c

# You may add further targets below.  Recommended simple format:
# <target>: <dependencies>
#	<command-to-execute>
# where <target> is the name of the binary to create
# <dependencies> are the files that, if changed, require regeneration of target
# <command-to-execute> is the shell command that will create the target
