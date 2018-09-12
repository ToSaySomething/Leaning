from  BaseHTTPServer import HTTPServer,BaseHTTPRequestHandler
import urllib
 
class ServerHTTP(BaseHTTPRequestHandler):
    def do_GET(self):
        path = self.path
        print path
        #拆分url(也可根据拆分的url获取Get提交才数据),可以将不同的path和参数加载不同的html页面，或调用不同的方法返回不同的数据，来实现简单的网站或接口
        query = urllib.splitquery(path)
        print query
        self.send_response(200)
        self.send_header("Content-type","text/html")
        self.send_header("test","This is test!")
        self.end_headers()
        buf = '''<!DOCTYPE HTML>
                <html>
                <head><title>Get page</title></head>
                <body>
                
                <form action="post_page" method="post">
                  username: <input type="text" name="username" /><br />
                  password: <input type="text" name="password" /><br />
                  <input type="submit" value="POST" />
                </form>
                
                </body>
                </html>'''
        self.wfile.write(buf)
        
    def do_POST(self):
        path = self.path
        print path
        #获取post提交的数据
        datas = self.rfile.read(int(self.headers['content-length']))
        datas = urllib.unquote(datas).decode("utf-8", 'ignore')
        
        self.send_response(200)
        self.send_header("Content-type","text/html")
        self.send_header("test","This is test!")
        self.end_headers()
        buf = '''<!DOCTYPE HTML>
        <html>
            <head><title>Post page</title></head>
            <body>Post Data:%s  <br />Path:%s</body>
        </html>'''%(datas,self.path)
        self.wfile.write(buf)
        
def start_server(port):
    http_server = HTTPServer(('', int(port)), ServerHTTP)
    http_server.serve_forever() 
    
if __name__ == "__main__":
    start_server(8000)