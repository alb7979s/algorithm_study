//���� �迭 ���Ҵ� 
if(size == capacity){
	int newCapacity = capacity + M;
	int* newArray = new int(newCapacity);
	for(int i=0; i<size; i++)
		newArray[i] = array[i];
	if(array) delete[] array;
	array = newArray;
	capacity = newCapacity;
}
array[size++] = newValue;
//m���� �ι辿 �÷��ָ� �Ҵ� ��������� O(1)����
