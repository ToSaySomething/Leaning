# 优化html报告

为了满足小伙伴的各种变态需求，为了装逼提示逼格，为了让报告更加高大上，测试报告做了以下优化：

- 测试报告中文显示，优化一些断言失败正文乱码问题
- 新增错误和失败截图，展示到html报告里
- 优化点击截图放大不清晰问题
- 增加饼图统计
- 失败后重试功能
- 兼容python2.x 和3.x

# 报告效果

1.生成的测试报告效果如下图，默认展示报错和异常的用例，失败重试的用例结果也会统计进去。

![image](http://note.youdao.com/yws/api/personal/file/E97A193B84B6450FA7CA7E148EE98FF8?method=download&shareKey=735b747a3614590f9c97aa765647c3a1)

2.点击显示截图，可以直接显示截取的图片，无需保存到本地
![image](http://note.youdao.com/yws/api/personal/file/FFC30301995F47B9AF7DD0F5D216C53C?method=download&shareKey=8c7ae911502c1f38e7b2ee541d13782d)

# table表格

1.修改表格的td后面内容，可以自定义表格名称

2.drawCircle这个后面是生成饼图功能

```html
<tr id='header_row'>
    <td>测试组/测试用例</td>
    <td>总数</td>
    <td>通过</td>
    <td>失败</td>
    <td>错误</td>
    <td>视图</td>
    <td>错误截图</td>
</tr>
%(test_list)s
<tr id='total_row'>
    <td>统计</td>
    <td>%(count)s</td>
    <td>%(Pass)s</td>
    <td>%(fail)s</td>
    <td>%(error)s</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
</table>
<script>
    drawCircle(%(Pass)s, %(fail)s, %(error)s)
</script>
```

# 异常截图

1.这个是用例跑失败后，会自动截图的，图片以base64方式存储到html报告里面，无需保存到本地

> driver.get_screenshot_as_base64()

```python
    def addError(self, test, err):
        self.error_count += 1
        self.status = 1
        TestResult.addError(self, test, err)
        _, _exc_str = self.errors[-1]
        output = self.complete_output()
        self.result.append((2, test, output, _exc_str))
        try:
            driver = getattr(test, "driver")
            test.img = driver.get_screenshot_as_base64()
        except AttributeError:
            test.img = ""
        if self.verbosity > 1:
            sys.stderr.write('E  ')
            sys.stderr.write(str(test))
            sys.stderr.write('\n')
        else:
            sys.stderr.write('E')
```
2.有一点必须要注意，必须要定义driver参数，如：

```
    @classmethod
    def setUpClass(cls):
        cls.driver = webdriver.Firefox()
```

# 失败重试

1.生成报告的参数里面加了一个参数retry=1,这个表示用例失败后，会重新跑一次。
```python
# coding:utf-8

import HTMLTestRunner_jpg
import unittest

if __name__ == "__main__":
    discover = unittest.defaultTestLoader.discover("case","test*.py")
    print(discover)
    
    run = HTMLTestRunner_jpg.HTMLTestRunner(title="可以装逼的测试报告",
                                            description="测试结果",
                                            stream=open("result.html","wb"),
                                            verbosity=2,
                                            retry=1)
    
    run.run(discover)
```
2.verbosity=2这个参数是控制台显示测试结果风格，如下这种：
```
E  test_01 (pject.test_jpg.Test1)
retesting... 1
E  test_01 (pject.test_jpg.Test1)
F  test_02 (pject.test_jpg.Test1)
retesting... 1
F  test_02 (pject.test_jpg.Test1)
ok test_03 (pject.test_jpg.Test1)
ok test_01 (pject.test_xxx.Test1)
ok test_02 (pject.test_xxx.Test1)

Time Elapsed: 0:00:17.892222
```
3.retesting就是代表重跑的用例

# 参考大神github

[大神github点这里](https://github.com/GoverSky/HTMLTestRunner)

这个是在大神的基础上稍微做了一点点图片显示的优化，之前的图片太小，显示模糊，放大了下，然后重新整理了下，采用批量执行用例的方式
