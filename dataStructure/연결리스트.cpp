struct ListNode{
    int element;
    ListNode *prev, *next;	//���� ���, ���� ��� ������
}
//�����ߴ� ���� �ǵ�����(undo)
//����
void delete(ListNode* node){
	node -> prev -> next = node -> next;
	node -> next -> prev = node -> prev;
}
//����
void recoverNode(ListNode* node){
    node -> prev -> next = node;
    node -> next -> prev = node;
}
