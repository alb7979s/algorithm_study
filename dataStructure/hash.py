#data,value 넣으면 해당 data에 대한 key를 찾아 table[key]에 value 저장
#value 없는경우는 data가 value가 되도록
class Hashtable:
    def __init__(self):
        self.table = [None for _ in range(SIZE)]
    def hash_func(self, data):
        return hash(data) % SIZE
    def _add(self, key, value):
        if self.table[key] is None:                    #맥주 있으면 그냥 추가
            self.table[key] = [[key, value]]
        else:
            for i in range(len(self.table[key])):
                if self.table[key][i][0] == key:
                    self.table[key][i][1] = value      #업데이트 될수도 있으니까
                    return
            self.table[key].append([key, value])       #같은 key 없으면 추가
    def save(self, data, value=''):
        if value == '': value=data
        key = self.hash_func(data)
        self._add(key, value)
        return key
    def get(self, data):
        key = self.hash_func(data)
        if self.table[key] is None: return None
        for i in range(len(self.table[key])):
            if self.table[key][i][0] == key: return self.table[key][i][1]
        return None
SIZE=2833       #그냥 대충 큰 소수
test = Hashtable()
test.save('kim', '1111')
test.save('lee', '2222')
test.save('park', '3333')
print(test.get('kim'))
print(test.get('sung'))
