
import requests
import unittest

class TestUserLogin(unittest.TestCase):

    def setUp(self):
        self.username = 'admin'
        self.password = 'admin'

    def test_login_successful(self):
        r = requests.post(url='http://10.129.0.102:8000/login',json={'username': self.username,'password': self.password})
        data = r.json()
        self.assertEqual(data['username'],'admin','expected user name is admin')
    
    def test_login_invalid_password(self):
        r = requests.post(url='http://10.129.0.102:8000/login',json={'username': self.username,'password': 'padasdasdasdas'})
        data = r.json()
        self.assertNotEqual(data['status'],0,'expected not zero status')

if __name__ == '__main__':
    unittest.main()