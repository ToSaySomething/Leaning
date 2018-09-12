# coding:utf-8
"""
basic_demo,py
"""
__author__ = "deng"

import unittest

class TestStringMethods(unittest.TestCase):
    def setUp(self):
        print 'init'

    def tearDown(self):
        print 'end'

    def test_upper(self):
        self.assertEqual('foo'.upper(), 'FOO')

    def test_isupper(self):
        self.assertTrue('FOO'.isupper())
        self.assertFalse('Foo'.isupper())
        self.assertTrue('Foo'.isupper())

    def test_split(self):
        s = "hello world"
        self.assertEqual(s.split(), ['hello', 'world'])
        with self.assertRaises(TypeError):
            s.split(2)

if __name__ == '__main__':
    #unittest.main()
    #load
    test_cases = unittest.TestLoader().loadTestsFromTestCase(TestStringMethods)
    #package
    test_suit = unittest.TestSuite()
    test_suit.addTest(test_cases)
    #run
    test_result = unittest.TextTestRunner(verbosity=2).run(test_suit)
    print("testsRun:%s" % test_result.testsRun)
    print("failures:%s" % len(test_result.failures))
    print("error:%s" % len(test_result.errors))
    print("skipped:%s" % len(test_result.skipped))