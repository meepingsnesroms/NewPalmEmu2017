#include "palmwrapper.h"//for app list

#include "memmap.h"
#include "minifunc.h"

//new list
#include "m68k.h"
#include "palmmalloc.h"
#include "resourcelocator.h"

#include <vector>

//memory tracking types
typedef struct{
	bool ishandle = false;
	int lockcount = 0;
	bool released = false;
	CPTR start;
	size_t_68k size;
}mallocchunk;

typedef struct{
	CPTR start;
	size_t_68k size;
}memfragment;


//Mini functions
static inline memfragment mergefrags(memfragment& frag1,memfragment& frag2){
	memfragment spliced;
	spliced.start = smallest(frag1.start,frag2.start);
	spliced.size = frag1.size + frag2.size;
	return spliced;
}

static inline bool fragstouching(memfragment& frag1,memfragment& frag2){
	if(smallest(frag1.start + frag1.size,frag2.start + frag2.size) + 1
	   == largest(frag1.start,frag2.start))return true;
	return false;
}


//memory stats
CPTR freesavedataptr;
size_t_68k avsavedata;

CPTR freeheapptr;
size_t_68k avheapdata;

std::vector<memfragment> freememfragments;
std::vector<mallocchunk> malloclist;


void resetmallocstate(){
	freememfragments.clear();
	malloclist.clear();
	freesavedataptr = SAVEDATA;
	avsavedata = SAVEDATASIZE;
	freeheapptr = HEAP;
	avheapdata = HEAPSIZE;
}

size_t_68k avheapmem(){
	//add up all small chunks and remander of heap stack
	size_t_68k totaldata = 0;
	unsigned int totalfrags = freememfragments.size();
	unsigned int count;
	inc_for(count,totalfrags){
		totaldata += freememfragments[count].size;
	}
	totaldata += avheapdata;
	return totaldata;
}

size_t_68k avlinearheapmem(){
	return avheapdata;
}

//checking starts at the back because the newest malloc is the one most
//likely to be freed,and for each 2 merged theres 1 less that needs to be checked against all the others
static bool condensefrags(){
	//condense fragments DONE
	//values must be signed for >= 0 to be valid
	int lastvectorelement = freememfragments.size() - 1;
	for(int segments = lastvectorelement;segments >= 0;segments--){
		for(int comp = segments - 1/*dont recheck what is done*/;comp >= 0;comp--){
			if(fragstouching(freememfragments[comp],freememfragments[segments])){
				freememfragments[segments] = mergefrags(freememfragments[comp],freememfragments[segments]);
				freememfragments.erase(freememfragments.begin() + comp);
				return true;//merged a fragment(if true call this function again)
			}
		}
	}
	return false;//all done
}

static CPTR getfromfrags(size_t_68k bytes){
	if(bytes & 1)bytes += 1;
	clensememory();
	uint numfrags = freememfragments.size();
	for(uint count = 0;count < numfrags;count++){
		if(freememfragments[count].size >= bytes){
			mallocchunk taken;
			taken.start = freememfragments[count].start;
			taken.size = bytes;
			malloclist.push_back(taken);

			//take data out of fragment(or destroy if equal in size)
			if(freememfragments[count].size == bytes){
				//destroy the fragment,not shrink it
				freememfragments.erase(freememfragments.begin() + count);
			}
			else{
				//shrink fragment
				freememfragments[count].size -= bytes;
				freememfragments[count].start += bytes;
			}

			return taken.start;
		}
	}
	return nullptr_68k;
}


//HACK just use normal ram as storage
CPTR getfreestorageram(size_t_68k bytes){
	if(bytes > avsavedata){
		palmabrt();//hack
		return nullptr_68k;
	}
	if(bytes & 1)bytes += 1;

	CPTR old = freesavedataptr;
	freesavedataptr += bytes;
	avsavedata -= bytes;

	//log allocation
	mallocchunk thissegment;
	thissegment.start = old;
	thissegment.size = bytes;
	malloclist.push_back(thissegment);

	return old;
}

CPTR getfreeheap(size_t_68k bytes){
	CPTR fromsmall = getfromfrags(bytes);//try to use small chunks first
	if(fromsmall)return fromsmall;

	if(bytes > avheapdata){
		palmabrt();//hack
		return nullptr_68k;
	}
	if(bytes & 1)bytes += 1;

	CPTR old = freeheapptr;
	freeheapptr += bytes;
	avheapdata -= bytes;

	//log allocation
	mallocchunk thissegment;
	thissegment.start = old;
	thissegment.size = bytes;
	malloclist.push_back(thissegment);

	return old;
}

CPTR getfreeheaphandle(size_t_68k bytes){
	CPTR block = getfreeheap(bytes);
	if(block == nullptr_68k)return nullptr_68k;
	malloclist.back().ishandle = true;
	return block;
}

CPTR getfreestorageramhandle(size_t_68k bytes){
	CPTR block = getfreestorageram(bytes);
	if(block == nullptr_68k)return nullptr_68k;
	malloclist.back().ishandle = true;
	return block;
}

bool ishandle(int index){
	return malloclist[index].ishandle;
}

bool islocked(int index){
	return (malloclist[index].lockcount > 0);
}

void lockmem(int index){
	malloclist[index].lockcount++;
}

bool unlockmem(int index){
	if(malloclist[index].lockcount > 0){
		malloclist[index].lockcount--;
		return true;
	}
	return false;
}

void lockappdata(int index,UWORD resid){
	apps[index].parts[resid].lockcount++;
}

bool unlockappdata(int index,UWORD resid){
	if(apps[index].parts[resid].lockcount > 0){
		apps[index].parts[resid].lockcount--;
		return true;
	}
	return false;
}

void clensememory(){
	//here checking starts at back so when an element is deleted and everything shifts
	//it dosent effect the checking position

	//values must be signed for >= 0 to be valid

	//free unused memory DONE
	for(int segments = malloclist.size() - 1;segments >= 0;segments--){
		if(malloclist[segments].released){
			memfragment newfrag;
			newfrag.start = malloclist[segments].start;
			newfrag.size = malloclist[segments].size;
			freememfragments.push_back(newfrag);
			malloclist.erase(malloclist.begin() + segments);
		}
	}

	//remove fragments that are touching DONE
	bool compact = true;
	while(compact)compact = condensefrags();

	//merge fragments with malloc stack DONE
	for(int segments = freememfragments.size() - 1;segments >= 0;segments--){
		if(freememfragments[segments].start + freememfragments[segments].size == freeheapptr){
			freeheapptr = freememfragments[segments].start;
			avheapdata += freememfragments[segments].size;
			freememfragments.erase(freememfragments.begin() + segments);
		}
	}
}

int memisalloc(CPTR address){
	if(address <= HEAP || address >= SAVEDATAEND)return -1;

	unsigned int count;
	size_t_68k size = malloclist.size();
	inc_for(count,size){
		//dbgprintf("Address:%08x,Cmp:%08x\n",address,malloclist[count].start);
		if(malloclist[count].start == address && !malloclist[count].released)return count;
	}
	return -1;
}

//if the last item on the malloc stack is freed just delete it instead of logging it
void quickclean(){
	if(malloclist.back().start + malloclist.back().size == freeheapptr && malloclist.back().released){
		freeheapptr -= malloclist.back().size;
		avheapdata += malloclist.back().size;
		malloclist.pop_back();
	}
}

bool lockmemaddr(CPTR addr,bool handle){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		//if(ishandle(index) != handle)return false;

		lockappdata(app,id);
		return true;
	}

	int index = memisalloc(addr);

	if(index == -1){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}
	if(ishandle(index) != handle){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}

	lockmem(index);
	return true;
}

bool unlockmemaddr(CPTR addr,bool handle){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		//if(ishandle(index) != handle)return false;

		return unlockappdata(app,id);
	}

	int index = memisalloc(addr);

	if(index == -1){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}
	if(ishandle(index) != handle){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}

	return unlockmem(index);
}

bool freememaddr(CPTR addr,bool handle){
	int index = memisalloc(addr);

	if(index == -1){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}
	if(ishandle(index) != handle){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}

	//may need to check lock count

	malloclist[index].released = true;
	quickclean();
	return true;
}

ULONG getsizememaddr(CPTR addr,bool handle){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		//hack (check if app and id are valid)
		//if(ishandle(index) != handle)return false;

		return apps[app].parts[id].size;
	}

	int index = memisalloc(addr);

	if(index == -1){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return 0;
	}
	if(ishandle(index) != handle){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}

	return malloclist[index].size;
}



bool abstractlock(CPTR addr){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		lockappdata(app,id);
		return true;
	}

	int index = memisalloc(addr);

	if(index == -1){
		palmabrt();
		return false;
	}

	lockmem(index);
	return true;
}

bool abstractunlock(CPTR addr){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		return unlockappdata(app,id);
	}

	int index = memisalloc(addr);

	if(index == -1){
		palmabrt();
		return false;
	}
	return unlockmem(index);
}

bool abstractfree(CPTR addr){
	if(addr <= HEAP || addr >= SAVEDATAEND)return false;//cant free storage ram

	int index = memisalloc(addr);
	if(index == -1){
		dbgprintf("Index:%d,IsHandle:%d\n",index,ishandle(index));
		palmabrt();
		return false;
	}
	malloclist[index].released = true;
	quickclean();
	return true;
}

ULONG abstractgetsize(CPTR addr){
	if(addr <= HEAP || addr >= SAVEDATAEND){
		int app;
		UWORD id;
		getnumfromptr(addr,&app,&id);

		//hack (check if app and id are valid)

		return apps[app].parts[id].size;
	}

	int index = memisalloc(addr);
	if(index == -1)return 0;
	return malloclist[index].size;
}
