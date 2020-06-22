from collections import*
class Node:
    def __init__(self, data):
        self.data = data
        self.left = self.right = None
class BST:
    def __init__(self):
        self.root = None
    def insert(self, data):
        self.root = self._insert(self.root, data)
    def _insert(self, node, data):
        if node is None: node = Node(data)      #
        else:
            if data <= node.data:
                node.left = self._insert(node.left, data)
            else:
                node.right = self._insert(node.right, data)
        return node
    def find(self, key):
        return self._find(self.root, key)
    def _find(self, node, key):
        if node is None or node.data == key:
            return node is not None
        elif key < node.data:
            return self._find(node.left, key)
        else:
            return self._find(node.right, key)
    def delete(self, key):
        self.root, deleted = self._delete(self.root, key) #
        return deleted
    def _delete(self, node, key):
        if node is None: return node, False
        deleted = False
        if key == node.data:
            deleted = True
            if node.left and node.right:
                parent, child = node, node.right
                while child.left is not None:
                    parent, child = child, child.left
                child.left = node.left
                if parent != node:
                    parent.left = child.right
                    child.right = node.right
                node = child
            elif node.left or node.right:
                node = node.left or node.right
            else:
                node = None
        elif key < node.data:
            node.left, deleted = self._delete(node.left, key)   #
        else:
            node.right, deleted = self._delete(node.right, key)
        return node, deleted
    def preorder(self):
        def _preorder(node):
            if node is None: pass
            else:
                print(node.data, end=' ')
                _preorder(node.left)
                _preorder(node.right)
        _preorder(self.root)
    def levelorder(self):
        def _levelorder(node):
            q = deque([node])
            while q:
                node = q.popleft()
                if node is not None:
                    print(node.data, end=' ')
                    if node.left: q.append(node.left)
                    if node.right: q.append(node.right)
        _levelorder(self.root)
array = [40, 4, 34, 45, 14, 55, 48, 13, 15, 49, 47]

bst = BST()
for x in array:
    bst.insert(x)

# Find
print(bst.find(15)) # True
print(bst.find(17)) # False

# Delete
print(bst.delete(55)) # True
print(bst.delete(14)) # True
print(bst.delete(11)) # False
bst.preorder()
print()
bst.levelorder()

#출처
#http://ejklike.github.io/2018/01/09/traversing-a-binary-tree-1.html
#http://ejklike.github.io/2018/01/09/traversing-a-binary-tree-2.html
