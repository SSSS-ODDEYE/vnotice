<p align="center">
  <img src="https://api.onedrive.com/v1.0/shares/s!AnnswJMWKhhhljhu14hyg6TlxcPc/root/content" height="auto" width="auto" />
</p>

# vnotice

vnotice是一个简单易用的企业微信机器人消息推送脚本

## 特性
- 通过脚本在线/本地更新
- 事务通知
- 按需指定机器人

## 用法

### 安装
地址 [ [Release](https://github.com/Ohto-Ai/vnotice/releases) ]  
下载脚本后执行即可
```bash
chmod a+x vnotice
./vnotice
```

### 更新
如需安装最新版本，可直接执行`vnotice`指令来更新，如果要安装其他版本，可以将脚本下载后执行该脚本`./vnotice`

### 参数
- `-c {command}` 指定脚本执行的指令  
- `-u` 只显示指令输出  
- `-o` 在没有`-u`时显式打开脚本输出  
- `-h` 隐藏命令  
- `-r {robot_id}` 指定本次使用的机器人  
- `-v` 显示版本信息  
- `-help` 显示帮助  

### 样例
```bash
lunch-long-time-build-demo.sh; vnotice -u -c echo lunch finished, return $?
# 针对预期运行时间较长的脚本可以设置提醒

vnotice -c view-status-demo.sh && vnotice -u -c echo view success || vnotice -u -c echo view failed
# 可以使用 -c 直接执行指令，执行完毕会返回指令结果，并被后续指令继续使用

vnotice -c use-multiple-parameters-demo.sh a --b "c" -d
# -c 不限制后续参数
```

### 致谢

感谢以下作者为仓库作出的贡献  
<a href="https://github.com/Ohto-Ai">
    <img src="https://avatars.githubusercontent.com/Ohto-Ai" style="border-radius:50%" width="96px">
</a> 
<a href="https://github.com/beiklive">
    <img src="https://avatars.githubusercontent.com/beiklive" style="border-radius:50%" width="96px">
</a> 
