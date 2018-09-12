# encoding:utf-8  
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

driver=webdriver.Chrome()
url='http://www.python.org'
driver.get(url)



assert "Python" in driver.title
elem = driver.find_element_by_name("q")
elem.send_keys("pycon")
elem.send_key(Keys.RETURN)
print driver.page_source

