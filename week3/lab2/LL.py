# (c) L.Spiegelberg
# file for Linked List implementation
from doctest import run_docstring_examples as dtest
import numbers
import reprlib

class LL:
    """
    >>> A = LL()  
    >>> A[0]
    Traceback (most recent call last):
        ...
    IndexError: trying to index an empty LL
    >>> A.insert_front(1)
    >>> A[0]
    1
    >>> A.insert_back(2)
    >>> A[1]
    2
    >>> A
    LL([1,...])
    >>> myll = LL.from_components([1,2])
    >>> myll[1]
    1
    >>> len(myll)
    2
    >>> myll[2]
    Traceback (most recent call last):
        ...
    IndexError: LL index out of range
    >>> myll[0:1]
    Traceback (most recent call last):
        ...
    TypeError: LL indices must be integers
    """
    @classmethod
    def from_components(cls, components):
        inst = cls(components[0])
        for c in components[1:]:
            inst.insert_front(c)
        return inst
        
    def __init__(self, head=None):
        if head is None:
            self._headNode = None
        else:
            self._headNode = [head, None]
            
    def insert_front(self, element):
        new_node = [element, None]
        new_node[1] = self._headNode
        self._headNode = new_node
        
    def insert_back(self, element):
        new_node = [element, None]
        curr_ptr = self._headNode
        while curr_ptr[1] is not None:
            curr_ptr = curr_ptr[1]
        curr_ptr[1]= new_node
        
    def __repr__(self):
        class_name = type(self).__name__
        if len(self)==0:
            components=""
        else:
            components = reprlib.repr(self[0])
        return '{}([{},...])'.format(class_name,components)

    # a nice printing routine
    def __str__(self):
        res = ""
        curr_ptr = self._headNode
        if curr_ptr==None:
            msg = 'trying to index an empty {class_name}' 
            raise IndexError(msg.format(class_name=class_name))
        next_ptr = self._headNode[1]
        count = 0
        while 1:
            res = res + str(curr_ptr[0])+'->'
            if curr_ptr[1] is None:
                break
            curr_ptr = curr_ptr[1]
        return res + 'NULL'

    def __len__(self):
        curr_ptr = self._headNode
        count = 0
        if curr_ptr==None:
            return 0
        while 1:
            count = count + 1
            if curr_ptr[1] is None:
                break
            curr_ptr = curr_ptr[1]
        return count    
    
    def __getitem__(self, index):
        class_name = type(self).__name__
        if isinstance(index, numbers.Integral): 
            curr_ptr = self._headNode
            if curr_ptr==None:
                msg = 'trying to index an empty {class_name}' 
                raise IndexError(msg.format(class_name=class_name))
            next_ptr = self._headNode[1]
            count = 0
            while 1:
                if index == count:
                    return curr_ptr[0]
                if curr_ptr[1] is None:
                    msg = '{class_name} index out of range' 
                    raise IndexError(msg.format(class_name=class_name))       
                count += 1
                curr_ptr = curr_ptr[1]
        else:
            msg = '{class_name} indices must be integers' 
            raise TypeError(msg.format(class_name=class_name))

    def __setitem__(self, index, value):
        class_name = type(self).__name__
        if isinstance(index, numbers.Integral): 
            curr_ptr = self._headNode
            if curr_ptr==None:
                msg = 'trying to index an empty {class_name}' 
                raise IndexError(msg.format(class_name=class_name))
            next_ptr = self._headNode[1]
            count = 0
            while 1:
                if index == count:
                    curr_ptr[0] = value
                    break
                if curr_ptr[1] is None:
                    msg = '{class_name} index out of range' 
                    raise IndexError(msg.format(class_name=class_name))       
                count += 1
                curr_ptr = curr_ptr[1]
        else:
            msg = '{class_name} indices must be integers' 
            raise TypeError(msg.format(class_name=class_name))


# test code
ll = LL.from_components([1, 2, 3, 4, 5, 8])
# original list
print(ll)
# list after set item
ll[4] = 43
print(ll)

# this should give an exception
try:
    ll[6] = 5
    print('failed exception test...')
except:
    print('succeeded!')
