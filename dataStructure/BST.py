from sys import*
from collections import*
setrecursionlimit(10**6)
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
        if node is None:
            node = Node(data)
        else:
            if data <= node.data:
                node.left = self._insert(node.left, data)
            else:
                node.right = self._insert(node.right, data)
        return node
    ''' 아래 find(), _find() 와 같은 구현
    def search(self, key):
        def _search(root):
            if root is None or key == root.data:
                return root is not None
            elif key < root.data:
                return _search(root.left)
            else:
                return _search(root.right)
        return _search(self.root)
    '''
    def find(self, key):
        return self._find(self.root, key)
    def _find(self, root, key):
        if root is None or root.data == key:
            return root is not None
        elif key < root.data:
            return self._find(root.left, key)
        else:
            return self._find(root.right, key)
    def delete(self, key):
        self.root, deleted = self._delete(self.root, key)
        return deleted
    def _delete(self, node, key):
        if node is None:
            return node, False
        deleted = False
        if key == node.data:
            deleted = True
            if node.left and node.right:
                parent, child = node, node.right
                while child.left is not None:
                    parent, child = node, node.left
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
            node.left, deleted = self._delete(node.left, key)
        else:
            node.right, deleted = self._delete(node.right, key)
        return node, deleted
    def preorder(self):
        def _preorder(root):
            if root is None: pass
            print(root.data, end=' ')
            _preorder(root.left)
            _preorder(root.right)
        _preorder(self.root)
    def inorder(self):
        def _inorder(root):
            if root is None: pass
            _inorder(root.left)
            print(root.data, end=' ')
            _inorder(root.right)
        _inorder(self.root)
    def postorder(self):
        def _postorder(root):
            if root is None: pass
            _postorder(root.left)
            _postorder(root.right)
            print(root.data, end=' ')
        _postorder(self.root)
    def levelorder(self):
        def _levelorder(root):
            q = deque([root])
            while q:
                root = q.popleft()
                if root is not None:
                    print(root.data, end=' ')
                    if root.left:
                        q.append(root.left)
                    if root.right:
                        q.append(root.right)
        _levelorder(self.root)
array = [40, 4, 34, 45, 14, 55, 48, 13, 15, 49, 47]
bst = BST()
for x in array:
    bst.insert(x)
bst.levelorder()
print()
bst.delete(40)
bst.levelorder()

#출처
#http://ejklike.github.io/2018/01/09/traversing-a-binary-tree-1.html
#http://ejklike.github.io/2018/01/09/traversing-a-binary-tree-2.html
