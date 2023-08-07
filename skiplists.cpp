#include "skiplists.h"

int new_nodesize(int max) {
	int size = 0;
	while (max > size) {
		if ((rand() % 2) == 0) break; //dont forget to initialize program with 1 call of srand() 
		else ++size;
	}
	return size;
}

snode* init_topleft(skiplists* s) {
	snode* temp = s->header;
	while (temp->upper) temp = temp->upper;
	return temp;
}

snode* init_top(snode* sn) {
	snode* temp = sn;
	while (temp->upper) {
		temp = temp->upper;
	}
	return temp;
}

void print_row(snode* sn) {
	snode* arbiter = sn;
	while (arbiter->lower) {
		cout << arbiter->key << ", Size: " << arbiter->size << endl;
		arbiter = arbiter->lower;
	}
	cout << arbiter->key << ", Size: " << arbiter->size << endl;
}

void skiplists::print_all() {

	snode* supertemp = header;
	while (supertemp->forward) {
		snode* temp2 = init_top(supertemp);
		print_row(temp2);
		supertemp = supertemp->forward;
	}
	snode* temp2 = init_top(supertemp);
	print_row(temp2);
}

skiplists* skiplists::add(const int& key) {
	snode* arbiter = init_topleft(this);
	vector<snode*> ref;

	//pt2 looking
	while (true) {
		if (arbiter->forward->key < key) {
			arbiter = arbiter->forward;
		}
		else if (arbiter->forward->key > key) {
			if (arbiter->lower) {
				ref.push_back(arbiter);
				arbiter = arbiter->lower;
			}
			else {
				ref.push_back(arbiter);
				break;
			}
		}
		else {
			cout << "(Item already element)\n";
			return this;
		}

	}
	//pt3 mking new node, adding
	int maxlvl = this->size;
	int nodelvls = new_nodesize(maxlvl);
	snode* newbuild = new snode(key, nodelvls);
	cout << "(new build: " << nodelvls << " nodelevels; value: " << key <<")" << endl;
	
	for (int i = 0; i <= nodelvls; ++i) {
		snode* left = ref[ref.size() - 1 - i];
		newbuild->prev = left;
		newbuild->forward = left->forward;
		left->forward = newbuild;
		newbuild = newbuild->upper;
	}
	
	return this;
}

snode* skiplists::find(const int& s_key) {
	snode* arbiter = init_topleft(this);
	while (true) {
		if (arbiter->forward->key < s_key) {
			arbiter = arbiter->forward;
		}
		else if (arbiter->forward->key > s_key) {
			if (arbiter->lower) {
				arbiter = arbiter->lower;
			}
			else {
				cout << "(Item not found)\n";
				break;
			}
		}
		else {
			cout << "(Item found)\n";
			return arbiter->forward;
		}
	}
	return nullptr;
}


skiplists* skiplists::remove(const int& s_key) {
	snode* arbiter = find(s_key);
	if (!arbiter) return this;

	arbiter = init_top(arbiter);
	while (arbiter->lower) {		
		arbiter->prev->forward = arbiter->forward;
		arbiter->forward->prev = arbiter->prev;
		arbiter = arbiter->lower;
	}
	arbiter->prev->forward = arbiter->forward;
	arbiter->forward->prev = arbiter->prev;
	return this;
}








