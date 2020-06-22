//동적 배열 재할당 
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
//m값을 두배씩 늘려주면 할당 평균적으로 O(1)나옴
