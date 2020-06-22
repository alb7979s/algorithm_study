struct ListNode{
    int element;
    ListNode *prev, *next;	//이전 노드, 다음 노드 포인터
}
//삭제했던 원소 되돌리기(undo)
//삭제
void delete(ListNode* node){
	node -> prev -> next = node -> next;
	node -> next -> prev = node -> prev;
}
//복구
void recoverNode(ListNode* node){
    node -> prev -> next = node;
    node -> next -> prev = node;
}
