<p align="center">
  <img src="https://api.onedrive.com/v1.0/shares/s!AnnswJMWKhhhljhu14hyg6TlxcPc/root/content" height="auto" width="auto" />
</p>
# vnotice

[circleci]: https://app.circleci.com/pipelines/github/Ohto-Ai/vnotice
[issues]: https://github.com/Ohto-Ai/vnotice/issues
[stargazers]: https://github.com/Ohto-Ai/vnotice/stargazers
[pulls]: https://github.com/Ohto-Ai/vnotice/pulls
[commit-activity]: https://github.com/Ohto-Ai/vnotice/pulse
[contributors]: https://github.com/Ohto-Ai/vnotice/contributors
[use-this]: https://github.com/Ohto-Ai/vnotice/generate
[circleci:badge]: https://img.shields.io/circleci/project/github/Ohto-Ai/vnotice/master
[license:badge]: https://img.shields.io/github/license/Ohto-Ai/vnotice?style=for-the-badge&logo=github
[issues:badge]: https://img.shields.io/github/issues/Ohto-Ai/vnotice?style=for-the-badge&logo=github
[stargazers:badge]: https://img.shields.io/github/stars/Ohto-Ai/vnotice?style=for-the-badge&logo=github
[pulls:badge]: https://img.shields.io/github/issues-pr/Ohto-Ai/vnotice?logo=github&style=for-the-badge&color=0088ff
[contributors:badge]: https://img.shields.io/github/contributors/Ohto-Ai/vnotice?style=for-the-badge&logo=github
[commit-activity:badge]: https://img.shields.io/github/commit-activity/m/Ohto-Ai/vnotice?style=for-the-badge&logo=github
[repository]: https://github.com/Ohto-Ai/vnotice

[![License][license:badge]](/LICENSE)
[![Issues][issues:badge]][issues]  
[![Stargazers][stargazers:badge]][stargazers]
[![Pulls][pulls:badge]][pulls]  
[![Contributors][contributors:badge]][contributors]
[![Commit Activity][commit-activity:badge]][commit-activity]

vnotice是一个企业微信机器人消息推送脚本

## Features
- git方式更新
- 事务通知
- 按需指定机器人

## Installation
```bash
git clone git@github.com:Ohto-Ai/vnotice
make install
```

## Update
```bash
make update
```

## Usage
> 见`vnotice --help`

### examples
```bash
lunch-long-time-build-demo.sh; vnotice -u -c echo lunch finished, return $?
# 针对预期运行时间较长的脚本可以设置提醒

vnotice -c view-status-demo.sh && vnotice -u -c echo view success || vnotice -u -c echo view failed
# 可以使用 -c 直接执行指令，执行完毕会返回指令结果，并被后续指令继续使用

vnotice -c use-multiple-parameters-demo.sh a --b "c" -d
# -c 不限制后续参数

vnotice -m One, two, three
# -m 输出消息
```

## License

This project is licensed under the terms of the [MIT License](/LICENSE).

## FAQ

[![Email](https://img.shields.io/badge/mail-zhu.thatboy@outlook.com-blue.svg?&style=for-the-badge)](mailto:zhu.thatboy@outlook.com?subject=Feedback&body=This%20is%20a%20test%20feedback.)

## Special Thanks
<a href="https://github.com/Ohto-Ai">
    <img src="https://avatars.githubusercontent.com/Ohto-Ai" style="border-radius:50%" width="96px">
</a>
<a href="https://github.com/beiklive">
    <img src="https://avatars.githubusercontent.com/beiklive" style="border-radius:50%" width="96px">
</a>
