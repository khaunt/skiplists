#pragma once
#include "std_lib_facilities.h"
#include <chrono>
#include <ctime>

const int minimal = 0;
const int maximal = numeric_limits<int>::max();


struct snode {
	int key;
	int size;
	snode* prev = 0; // for deletion important
	snode* upper;
	snode* lower;
	snode* forward = 0;
	snode(int k, int sz)
		:key(k), size(sz), lower(0) {
		if (sz == 0) {
			upper = 0;
		}
		else {
			upper = new snode(k, (sz - 1), this);
		}		
	}
	snode(int k, int sz, snode* prev): key(k), size(sz), lower(prev) {
		if (sz < 1) {
			upper = 0;
		}
		else {
			upper = new snode(k, (sz - 1), this);
		}
	}
	~snode() { delete upper; };
};

struct skiplists
{
	skiplists(int sz)
		:size(sz), elements(0)
	{
		header = new snode(minimal, size);
		NIL = new snode(maximal, size);
		snode* first = this->header;
		snode* last = this->NIL;
		while (true) {
			first->forward = last;
			if (first->upper) {
				first = first->upper;
				last = last->upper;
			}
			else break;
		}
	}
	~skiplists() { delete header; delete NIL; }

	void print_all();
	skiplists* add(const int& key);
	snode* find(const int& s_key);
	skiplists* remove(const int& s_key);

	int size;
	int elements;
	snode* header;
	snode* NIL;


};
