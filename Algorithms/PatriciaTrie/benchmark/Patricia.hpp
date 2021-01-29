#ifndef PATRICIA_HPP
#define PATRICIA_HPP

#include <iostream>
#include <fstream>
//max size 257
typedef char TKey;
typedef unsigned long long TData;
//работает только с латинскими маленькими так бит 0 у них всегда первый

class TNode {
private:
    TKey* key;
    TData data;
    int unbit;
    int id;
    TNode* branches[2];
    friend class TPatricia;
public:
    TNode(TKey*& ikey, TData& idata, int iunbit) : key(ikey), data(idata), unbit(iunbit), id(0)
    {
        branches[0] = this;
        branches[1] = this;
    }


    ~TNode() {
        if(key != nullptr) {
           delete [] key;
           key = nullptr;
        }
    }


    TData GetData() {
        return data;
    } 
};


class TPatricia {
private:
    int size;
    TNode* head;
public:
    TPatricia() : size(0), head(nullptr)
    {}


    TNode* Find(TKey* ckey) {
        if(head == nullptr) {
            return nullptr;
        }
        TNode* prevnode = head;
        TNode* currnode = head->branches[0];
        while(prevnode->unbit < currnode->unbit) {
            prevnode = currnode;
            currnode = prevnode->branches[DesiredBit(ckey,prevnode->unbit)];
        }
        if(KeyCompare(currnode->key,ckey)) {
            return currnode;
        }
        return nullptr;
    }


    bool Insert(TKey*& nkey, TData& ndata) {
        if(head == nullptr) {
            TNode* nnode = new TNode(nkey,ndata,-1);
            head = nnode;
            head->branches[1] = nullptr;
            size++;
            return true;
        }
        TNode* prevnode = head;
        TNode* currnode = head->branches[0];
        //search
        while(prevnode->unbit < currnode->unbit) {
            prevnode = currnode;
            currnode = prevnode->branches[DesiredBit(nkey,prevnode->unbit)];
        }
        // check
        if(KeyCompare(currnode->key,nkey)) {
            return false;
        }
        // get number of Different bit
        int nunbit = DifferentBit(currnode->key,nkey);
        prevnode = head;
        currnode = head->branches[0];
        // find place to insert
        while((prevnode->unbit < currnode->unbit) && (currnode->unbit < nunbit)) {
            prevnode = currnode;
            currnode = prevnode->branches[DesiredBit(nkey,prevnode->unbit)];
        }
        TNode* nnode = new TNode(nkey,ndata,nunbit);
        // get prevnode next element
        TNode* breakbranch = currnode;
        prevnode->branches[DesiredBit(nkey,prevnode->unbit)] = nnode;
        //insert with rules
        if(DesiredBit(nkey,nunbit) == 1) {
            nnode->branches[1] = nnode;
            nnode->branches[0] = breakbranch;
        } else if(DesiredBit(nkey,nunbit) == 0) {
            nnode->branches[0] = nnode;
            nnode->branches[1] = breakbranch;
        }
        size++;
        return true;
    }

    bool Save(const char* filename) {
        std::ofstream file;
        file.open(filename,std::ios::binary | std::ios::out);
        if(!file) {
            throw std::logic_error("ERROR: File do not open!");
            return false;
        }
        if(size == 0) {
            file.close();
            return true;
        }
        file.write((char*)&size, sizeof(int));
        int id = 0;
        TNode** nodes = new TNode*[size];
        GetNodes(nodes,id,head);
        head->branches[1] = head;
        for(int i = 0; i < size;i++) {
            file.write((char*) &(nodes[i]->data), sizeof(TData));
            file.write((char*) &(nodes[i]->unbit), sizeof(int));
            int len = LengthOfByte(nodes[i]->key);
            file.write((char*) &(len), sizeof(int));
            file.write(nodes[i]->key, len);
            file.write((char*) &(nodes[i]->branches[0]->id), sizeof(int));
            file.write((char*) &(nodes[i]->branches[1]->id), sizeof(int));
        }
        head->branches[1] = nullptr;
        delete [] nodes;
        file.close();
        return true;
    }


    bool Load(const char* filename) {
        std::ifstream file;
        file.open(filename, std::ios::in|std::ios::binary);
        if(!file) {
            throw std::logic_error("ERROR: File do not open!");
            return false;
        }
        if (file.peek() == EOF) {
           DeleteTrie(head);
           head = nullptr;
           size = 0;
           return true;
        }
        file.read((char*) &size, sizeof(int));
        if (!size) {
            throw std::logic_error("ERROR: Other form!");
            return false;
        }
        this->size = size;
        TNode** nodes = new TNode*[size];
        TData data;
        int unbit;
        int len;
        int lbranch;
        int rbranch;
        int* ourid = new int[size * 2];
        int count = 0;
        for (int i = 0; i < size; ++i) {
            file.read((char*) &(data), sizeof(TData));
            file.read((char*) &(unbit), sizeof(int));
            file.read((char*) &(len), sizeof(int));
            char* key = new char[len + 1];
		    key[len] = 0;
		    file.read(key, len);
            file.read((char*) &(lbranch), sizeof(int));
            file.read((char*) &(rbranch), sizeof(int));
            nodes[i] = new TNode(key,data,unbit);
            ourid[count] = lbranch;
            ourid[count + 1] = rbranch;
            count += 2;
        }
        count = 0;
        int countnode = 0;
        while(countnode < size) {
            nodes[countnode]->branches[0] = nodes[ourid[count]];
            nodes[countnode]->branches[1] = nodes[ourid[count + 1]];
            count += 2;
            countnode++;
        }
        DeleteTrie(head);
        head = nodes[0];
        head->branches[1] = nullptr;
        delete [] nodes;
        delete [] ourid;
        file.close();
        return true;
    }    


    bool Delete(TKey*& ckey) {
        if (head == nullptr) {
            return false;
        }
        TNode* parent = head;
        TNode* del = head->branches[0];
        while(parent->unbit < del->unbit) {
            parent = del;
            del = parent->branches[DesiredBit(ckey,parent->unbit)];
        }
        if(!KeyCompare(del->key,ckey)) {
            return false;
        }
        //zero case
        if((del == head) && (del->branches[0] == head)) {
            delete head;
            head = nullptr;
            size--;
            return true;
        }
        //first case
        parent = SearchParent(del->key);
        if(del->branches[0] == del || del->branches[1] == del) {
            TNode* breakbranch;
            if(del->branches[0] == del) {
                breakbranch = del->branches[1];
            } else if(del->branches[1] == del) {
                breakbranch = del->branches[0];
            }
            if(parent->branches[0] == del) {
                parent->branches[0] = breakbranch;
            } else if(parent->branches[1] == del) {
                parent->branches[1] = breakbranch;
            }
            //maybe other situation: parent hasnot del in branches
            //del->~TNode();
            delete del;
            del = nullptr;
            size--;
            return true;
        }
        //second case
        TNode *p = del;
        TNode *q = SearchBackward(p->key); // element, which has back branch to p;
        TNode *r = SearchBackward(q->key); // element, which has back branch to q;
        TNode *qparent = SearchParent(q->key);
        // уник бит r относительно q то есть можно понять в каком узле(в левом(0) или правом(1)) у q находится r(если он есть)
        int runbit = DesiredBit(r->key,q->unbit);
        std::swap(p->key,q->key);
        std::swap(p->data,q->data);
        // проверка обратной ссылки r на удаляемый q и смена на p
        if(r->branches[0] == q) {
            r->branches[0] = p;
        } else if(r->branches[1] == q) {
            r->branches[1] = p;
        }
        // смещение r становится на место q. Также работает, если r = q.
        if(qparent->branches[0] == q) {
            if(runbit == 1) {
                qparent->branches[0] = q->branches[1];
            } else if(runbit == 0) {
                qparent->branches[0] = q->branches[0];
            }
        } else if(qparent->branches[1] == q) {
            if(runbit == 1) {
                qparent->branches[1] = q->branches[1];
            } else if(runbit == 0) {
                qparent->branches[1] = q->branches[0];
            }
        }
        delete q;
        q = nullptr;
        size--;
        return true;
    }


    ~TPatricia() {
        DeleteTrie(head);
    }
private:
/*
Так как сдвиг вправо (>>) дописывает слева нули, 
то для целых чисел операция равносильна целочисленному делению пополам, а сдвиг влево умножению на 2.
*/
    int LengthOfBits(TKey*& key) {
        int i = 0;
        while(key[i] != '\0') {
            i++;
        }
        return (i * 8);
    }


    int LengthOfByte(TKey*& key) {
        int i = 0;
        while(key[i] != '\0') {
            i++;
        }
        return i;
    }


    int DesiredBit(TKey*& key, int& dbit) {
        if(dbit >= LengthOfBits(key)) {
            return 0;
        }
        if(dbit < 0) {
            dbit = 0;
        }
        int rightchange = 7 - (dbit & 7);
        return ((key[dbit >> 3] >> rightchange) & 1);
    }


    TNode* SearchBackward(TKey*& ckey) {
        TNode* prevnode = head;
        TNode* currnode = head->branches[0];
        //search
        while(prevnode->unbit < currnode->unbit) {
            prevnode = currnode;
            currnode = prevnode->branches[DesiredBit(ckey,prevnode->unbit)];
        }
        return prevnode;
    }


    TNode* SearchParent(TKey*& ckey) {
        TNode* prevnode = head;
        TNode* currnode = head->branches[0];
        if(head->branches[0]->key == ckey) {
            return head;
        }
        while(prevnode->unbit < currnode->unbit) {
            prevnode = currnode;
            currnode = prevnode->branches[DesiredBit(ckey,prevnode->unbit)];
            if((prevnode->branches[0]->key == ckey) || (prevnode->branches[1]->key == ckey)) {
                return prevnode;
            }
        }
        return nullptr;
    }


    void GetNodes(TNode**& cnodes, int& id,  TNode*& cnode) {
        cnodes[id] = cnode;
        cnodes[id]->id = id;
        id++;
        if(cnode->unbit < cnode->branches[0]->unbit) {
            GetNodes(cnodes,id,cnode->branches[0]);
        }
        if((cnode->branches[1] != nullptr) && (cnode->unbit < cnode->branches[1]->unbit)) {
            GetNodes(cnodes,id,cnode->branches[1]);
        }
    }


    void DeleteTrie(TNode*& cnode) {
        if(cnode == nullptr) {
            return;
        }
        if((cnode->branches[1] != nullptr) && (cnode->unbit < cnode->branches[1]->unbit)) {
            DeleteTrie(cnode->branches[1]);
        }
        if((cnode->unbit < cnode->branches[0]->unbit) && (cnode->branches[0] != nullptr)) {
            DeleteTrie(cnode->branches[0]);
        }
        delete cnode;
        cnode = nullptr;
    }


    int DifferentBit(TKey*& firstkey, TKey*& secondkey) {
        int count = 0;
        int lbfirstkey = LengthOfByte(firstkey);
        int lbsecondkey = LengthOfByte(secondkey);
        int minlength = lbfirstkey > lbsecondkey ? lbsecondkey : lbfirstkey;
        int maxlength = lbfirstkey > lbsecondkey ? lbfirstkey : lbsecondkey;
        while((firstkey[count] == secondkey[count]) && (count < minlength)) {
            count++;
        }
        count = count * 8;
        while((DesiredBit(firstkey,count) == DesiredBit(secondkey,count)) && (count < (maxlength * 8))) {
            count++;
        }
        return count;     
    }


    bool KeyCompare(TKey*& key1, TKey*& key2) {
        if (key1 == key2) {
            return true;
        }

        int len = LengthOfBits(key1);
        if (len != LengthOfBits(key2)) {  // Ключи разной длинны и тогда не точно не совпадают
            return false;
        }

        if (DifferentBit(key1, key2) != len) {
            return false;
        }
        return true;
    }
};

#endif