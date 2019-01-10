int btinit()
BTA *btcrt(char *fid, int nkeys, int shared)
/*create a new b tree, fid is the name of file to create
nkeys defines maximum number of keys store in b tree,
for operating system, it's set to 0 for dynamic file growth,
shared: 0 for not shared to other b tree, non 0 for shared */

BTA *btopn(char *fid, int mode, int shared)
/* open existing b tree file, mode is determines b tree can be updated 
or not. 0 are updatable, non-0 for can not. shared: 0 - not shared */

int btcls(BTA *btact)
/* close file associate to btact context poiter,
non-0 return an error */

int btdups(BTA* btact, int dups);

/*The btdups controls support for duplicate keys in the current root of the index file associated with the btact context pointer. Setting the value of the dups to non-zero (TRUE) will enable support for duplicate keys in the current root. A value of zero (FALSE) will disable duplicate key support for the current root. Enabling duplicate key support on the superroot is not permitted.

Disabling duplicate key support on a root that previously permitted them merely prevents further duplicate keys from being inserted into the root BTree index. Existing duplicates will remain and must be managed by the application.

A non-zero return code indicates an error occurred.*/

int btthresh(BTA *btact, int threshold)
/* Set the wrtie threshold to the index file associate to btact context
pointer. threshold defines the number of updates on a block that will 
cause it to be wrtiten to disk. Default is 0 means that block is not 
written until the memory it hold is required new block

btthresh is to reduce the chance of losing data*/

int binsky(BTA *btact, char *key, BTint value)
/*binsky insert a new key and associated integer value
into the current root. binsky return 0 for successfully insert
keys longer than maximum key length (ZKYLEN) will automatically
truncated to the maximum len.*/

int bfndky(BTA *btact, char *key, BTint *value)
/* bfndky() search for  a key in the current root,
if the key is found, the integer value will be return */

int bnxtky(BTA* btact, char* key, BTint* value);

/*The bnxtky function returns the next key from the current root in the file associated with the btact context pointer. The key, a character string, is returned via the pointer in key. The value associated with the key will be returned in the integer location identified by value. value is declared as a BTint, which is normally a typedef for int, but with Large File Support will be a typedef for long long.

bnxtky returns zero to indicate the next key has been located. If no next key exists, bnxtky returns the error code QNOKEY.

To initialise the B Tree position, a call to bfndky or btpos must be made before the first call to bnxtky. Thereafter, repeated calls to bnxtky may be made. Calls to bprvky may be freely intermingled with calls to bnxtky.

A non-zero return from bnxtky indicates an error occurred during the key location process.*/

int bprvky(BTA *btact, char *key, BTint *value)
/* return the previous key */

int btpos(BTA *btact, int pos)
/* set the position int the current root.
The desired position is indicated by pos,
value of 1 will positions before the first key in the index,
value of 2 will positions after the last key in the index.
They correspond to ZSTART and ZEND. */

int bdelky(BTA *btact, char *key)
/* if pass NULL as key, the current key will be delete */

int bupdky(BTA *btact, char *key, BTint value)
/* if key not exist -> error code returned,
if pass NULL as key, the update will act on the current key */

int btrcrtr(BTA *btact, char *root)
/* creating a root within the file context,
the root name is pass, return 0 as successs, the new root is make as current. */

int btchgr(BTA *btact, char *root)
/* chage the curent root of the context file. */

int btdelr(BTA *btact, char *root)
/* delete a root from the context file, all block owned 
by the target root will be delete */

int btlock(BTA *btact)
/* enable process to gain exclusive access to b tree file */

int btunlock(BTA *btact)
/* enable process to relinquish exclusive access to file */

int btins(BTA *btact, char *key, char *data, int dsize)
/* inserting a key and data into a file associated with btact,
both key and data are char pointer, dsize is the length of data
to avoid '\0' character */

int btupd(BTA *btact, char *key, char *data, int dsize)
/* update the data for an existing key, 
if NULL is pass as key, an update act on the current key
selected by btsel, btseln or btselp */

int btsel(BTA *btact, char *key, char *data, int dsize, int *rsize)
/* locating data for an existing key: return the data of an existing key
dsize is the max number of bytes to return, the actual number of byte is
rsize */

int btdel(BTA *btact, char *key)
/* delete a key and associated data, if Null is pass as key,
the current key is deleted */

int btseln(BTA *btact, char *key, char *data, int dsize, int *rsize)
/* locate and return the next key and data in the context file,
before using btseln, a call to btsel or btpos must be made */

int btselp(BTA *btact, char *key, char *data, int dsize, int rsize)
/* locate and return the previous key and data */

int btrecs(BTA *btact, char *key, char *rsize)
/* return the number of bytes occupied by the data of a key in the context file,
the number of byte is return in rsize, 
if NULL is passed as key, record for the current key */

int bdbug(BTA *btact, char *opt, BTint blk)
/*
The bdbug function provides a debug capability for the B Tree package. The following options can be passed via the opt parameter:

Table 3.1. Debug Options

control	-	displays the in-memory block information, together with the last key found details
super	-	displays superroot information i.e. block usage, free list etc.
stack	-	displays the tree stack (i.e. key context)
space	-	displays occupancy statistics
stats	-	displays B Tree operating statistics
block	-	displays the contents of the block identified by blk. blk is declared as a BTint, which is normally a typedef for int, but with Large File Support will be a typedef for long long.
structure	-	Performs a structure check of the currently active BTree file. If blk is set to ZNULL, information on the index structure, and problems (if any), are displayed. Otherwise, a simple statement of structure condition is displayed.
*/