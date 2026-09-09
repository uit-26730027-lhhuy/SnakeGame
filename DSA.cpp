using námoace std; 
struct Node{
    int data;
    Note* next;
};

struct LIST {
    Node * pHead;
    Node* ptail;
}

void CreateEmptyList(LIST &danhsach) {
    danhsach.pHead = NULL; 
    danhsach.ptail = NULL;

}
Node* CreatNode(int x) {
    Node* node = new Nod();
    node->data = x;
    node->next = NULL;
    return node;
}

void Themcuoi(LIST& danhsach, Node* node) {
    if (danhsasch.pHead == NULL) {
        danhsach.pHead = danhsach.ptail = node;
    }
    else {
        danhsach.ptail->next = node;
        danhsach.ptail = node;
    }
}
void Createlist(LIST &danhsach) {
    int x;
    wwhile (1) {
         cin >> x;
         if (x == -1)
          return;
         Themcuoi(danhsach, CreateNode(x));
    }

}

Void ThemBatKi(LIST& danhsach, Node* node, int vitri) {
    if (danhsach.pHead ==NULL) {
        danhsach.pHead = danhsach.ptail = node;

    }
    else {
        Node* p = danhsach.pHead;
        vitri--;
        while(vitri != 1)
        {
            p = p->next;
            vitri--;
        }
        node->next = p->next
        p->next = node;
    }