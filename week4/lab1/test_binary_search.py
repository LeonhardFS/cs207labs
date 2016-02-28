from binsearch import *
import unittest
import numpy as np

class MyTest(unittest.TestCase):
    
    def test_special_values(self):
        self.assertEqual(binary_search([1,2,np.inf], np.inf), 2)
        self.assertEqual(binary_search([-np.inf, 1, 2, np.inf], -np.inf), 0)
        self.assertEqual(binary_search([1,2,3,4,np.nan], np.nan), 4)
        self.assertEqual(binary_search([np.nan,2,3,4], np.nan), 0)
    
    def test_array_cases(self):
        self.assertEqual(binary_search([], 100), -1)
        self.assertEqual(binary_search([1], 100), -1)
        self.assertEqual(binary_search([2], 2), 0)
        self.assertEqual(binary_search([1, 2], 2), 1)
        
    def test_needle_cases(self):
        self.assertEqual(binary_search([1, 2, 3], 100), -1)
        self.assertEqual(binary_search([1, 2, 3], -100), -1)
        
        ii32 = np.iinfo(np.int32)
        self.assertEqual(binary_search([ii32.min, ii32.max], -100), -1)
        self.assertEqual(binary_search([ii32.min, ii32.max], ii32.min), 0)
        self.assertEqual(binary_search([ii32.min, ii32.max], ii32.max), 1)
        
        self.assertEqual(binary_search([ii32.min, np.nan, ii32.max], -100), -1)
        self.assertEqual(binary_search([ii32.min, np.nan, ii32.max], ii32.min), 0)
        self.assertEqual(binary_search([ii32.min, ii32.max, np.nan], ii32.max), 1)
        
        self.assertEqual(binary_search([-np.inf, ii32.min, ii32.max], -100), -1)
        self.assertEqual(binary_search([ii32.min, ii32.max, np.inf], ii32.min), 0)
        self.assertEqual(binary_search([-np.inf, ii32.min, ii32.max, np.inf], ii32.max), 1)
        
    def test_wrong_input(self):
        with self.assertRaises(TypeError):
            binary_search('Hello world!', -100)
        with self.assertRaises(TypeError):
            binary_search(None, -100)
        with self.assertRaises(TypeError):
            binary_search([1, 2, 60], 'Hello')


if __name__ == '__main__':
    unittest.main()